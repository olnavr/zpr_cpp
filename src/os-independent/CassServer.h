#ifndef _CASSSERVER_H
#define _CASSSERVER_H
#include "stdafx.h"
#include "Container.h"
#include "cassandra.h"
#include <map>
#include <memory>
#include <algorithm>
#ifdef _WIN32
#include <functional>
#endif
class CassServ
{
	template<typename T> using Ptr = std::unique_ptr<T>;
public:
	CassServ(Container* container, char* hosts);
	void tryExecuting();
	void sendContainerData();

	bool prepareCassandra();

	~CassServ();
private:
	char* hosts_;
	CassUuidGen* uuid_gen_;
	CassFuture* connect_future_;
	CassCluster* cluster_;
	CassSession* session_;
	CassError rc_;

	Container* container_;

};
#endif