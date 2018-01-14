#include "CassServer.h"

CassServ::CassServ(Container * container, char * hosts) : container_(container), hosts_(hosts) {
	uuid_gen_ = cass_uuid_gen_new();
	connect_future_ = NULL;
	cluster_ = cass_cluster_new();
	session_ = cass_session_new();
}

void print_error(CassFuture* future) {
	const char* message;
	size_t message_length;
	cass_future_error_message(future, &message, &message_length);
	fprintf(stderr, "Error: %.*s\n", (int)message_length, message);
}

//by copy -> copying const pointers with immutable data is safe.
auto execute_query = [=](CassSession* session, const char* query)
{
	CassError rc = CASS_OK;
	CassFuture* future = NULL;
	CassStatement* statement = cass_statement_new(query, 0);

	future = cass_session_execute(session, statement);
	cass_future_wait(future);

	rc = cass_future_error_code(future);
	if (rc != CASS_OK) {
		print_error(future);
	}

	cass_future_free(future);
	cass_statement_free(statement);

	return rc;
};

CassServ::~CassServ()
{
	if(uuid_gen_ != NULL) cass_uuid_gen_free(uuid_gen_);
	if (connect_future_ != NULL) {
		//rc_ = execute_query(session_, "DROP KEYSPACE examples;");
		cass_future_free(connect_future_);
	}
	if (cluster_ != NULL) cass_cluster_free(cluster_);
	if (session_ != NULL) cass_session_free(session_);
}


auto create_cluster = [=](CassCluster* cluster, const char* hosts) {
	CassError rc = CASS_OK;
	rc = cass_cluster_set_contact_points(cluster, hosts);
	return rc;
};

bool CassServ::prepareCassandra()
{
	bool preparation_gone_well = true;

	rc_ = create_cluster(cluster_, hosts_);
	if (rc_ != CASS_OK) {
		preparation_gone_well = false;
		return preparation_gone_well;
	}

	connect_future_ = cass_session_connect(session_, cluster_);

	cass_future_wait(connect_future_);
	rc_ = cass_future_error_code(connect_future_);

	if (rc_ != CASS_OK) { 
		preparation_gone_well = false;
		return preparation_gone_well; }

	rc_ = execute_query(session_,
		"CREATE KEYSPACE IF NOT EXISTS zpr WITH replication = { \
                'class': 'SimpleStrategy', 'replication_factor': '3' };");

	rc_ = execute_query(session_,
		"CREATE TABLE IF NOT EXISTS zpr.logs ( key text, time timeuuid, value text, \
                PRIMARY KEY (key,time));");
	rc_ = execute_query(session_,
		"TRUNCATE TABLE zpr.logs");
	rc_ = execute_query(session_,
		"CREATE TABLE IF NOT EXISTS zpr.names (key text, name text, \
                PRIMARY KEY (key))");
	rc_ = execute_query(session_,
		"TRUNCATE TABLE zpr.names");

	CassStatement* statement = cass_statement_new("INSERT INTO zpr.names (key, name) VALUES (?, ?);", 2);
	CassFuture* result_future = cass_session_execute(session_, statement);

	std::for_each(std::begin(container_->container_), std::end(container_->container_), [&](const auto& p)
	{
		cass_statement_bind_string(statement, 0, p.first.c_str());
		result_future = cass_session_execute(session_, statement);
		cass_future_wait(result_future);

		rc_ = cass_future_error_code(result_future);
		if (rc_ != CASS_OK) print_error(result_future);
	});
	
	cass_future_free(result_future);
	cass_statement_free(statement);

	return preparation_gone_well;
}

float CassServ::getUpdatePeriod() { 

	CassStatement* statement = cass_statement_new("SELECT * FROM timekeyspace.time", 0);
	CassFuture* result_future = cass_session_execute(session_, statement);

	if (cass_future_error_code(result_future) == CASS_OK) {
		/* Retrieve result set and get the first row */
		const CassResult* result = cass_future_get_result(result_future);
		const CassRow* row = cass_result_first_row(result);

		if (row) {
			const CassValue* value = cass_row_get_column_by_name(row, "seconds");
			//cass_value_get_string(value, &release_version, &release_version_length);
			cass_value_get_float(value, &updatePeriod);
		}

		cass_result_free(result);
	}
	else {
		/* Handle error */
		print_error(result_future);
		updatePeriod = 1.0;
	}
	return updatePeriod; }

template <typename Iter>
auto insert_into_logs = [=](CassSession* session, const char* key, CassUuidGen* uuid_gen, Iter iterBegin, Iter iterEnd)
{
	CassError rc = CASS_OK;
	CassFuture* future = NULL;
	CassStatement* statement = NULL;
	CassCollection* collection = NULL;

	CassUuid uuid;

	const char* query = "INSERT INTO zpr.logs (key, time, value) VALUES (?, ?, ?);";
	statement = cass_statement_new(query, 3);

	cass_uuid_gen_time(uuid_gen, &uuid);

	std::for_each(iterBegin, iterEnd, [&](const auto& p)
	{
		cass_statement_bind_string(statement, 0, p.first.c_str());
		cass_statement_bind_uuid(statement, 1, uuid);
		cass_statement_bind_string(statement, 2, p.second.c_str());
		future = cass_session_execute(session, statement);
		cass_future_wait(future);

		rc = cass_future_error_code(future);
		if (rc != CASS_OK) print_error(future);
	});

	cass_future_free(future);
	cass_statement_free(statement);

	return rc;
};

void CassServ::sendContainerData()
{
	using MapIter = typename std::map<std::string, std::string>::iterator;

	rc_ = insert_into_logs<MapIter>(session_, "test", uuid_gen_, std::begin(container_->container_), std::end(container_->container_));
}

//dOTESTU
void CassServ::tryExecuting()
{

	/* Add contact points */
	cass_cluster_set_contact_points(cluster_, hosts_);

	/* Provide the cluster object as configuration to connect the session */
	connect_future_ = cass_session_connect(session_, cluster_);

	if (cass_future_error_code(connect_future_) == CASS_OK) {
		CassFuture* close_future = NULL;

		/* Build statement and execute query */
		const char* query = "SELECT release_version FROM system.local";
		CassStatement* statement = cass_statement_new(query, 0);

		CassFuture* result_future = cass_session_execute(session_, statement);

		if (cass_future_error_code(result_future) == CASS_OK) {
			/* Retrieve result set and get the first row */
			const CassResult* result = cass_future_get_result(result_future);
			const CassRow* row = cass_result_first_row(result);

			if (row) {
				const CassValue* value = cass_row_get_column_by_name(row, "release_version");

				const char* release_version;
				size_t release_version_length;
				cass_value_get_string(value, &release_version, &release_version_length);
				printf("release_version: '%.*s'\n", (int)release_version_length, release_version);
			}

			cass_result_free(result);
		}
		else {
			/* Handle error */
			const char* message;
			size_t message_length;
			cass_future_error_message(result_future, &message, &message_length);
			fprintf(stderr, "Unable to run query: '%.*s'\n", (int)message_length, message);
			//return;
		}

		cass_statement_free(statement);
		cass_future_free(result_future);

		/* Close the session */
		close_future = cass_session_close(session_);
		cass_future_wait(close_future);
		cass_future_free(close_future);
	}
	else {
		/* Handle error */
		const char* message;
		size_t message_length;
		cass_future_error_message(connect_future_, &message, &message_length);
		fprintf(stderr, "Unable to connect: '%.*s'\n", (int)message_length, message);
		//return;
	}
}