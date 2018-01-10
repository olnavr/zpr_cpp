#include "stdafx.h"
#include "WmiFunctor.h"


WTSEnumerateProcessesFunctor::WTSEnumerateProcessesFunctor()
{
	pWPIs = NULL;
	DWORD dwProcCount = 0;
	if (WTSEnumerateProcesses(WTS_CURRENT_SERVER_HANDLE, NULL, 1, &pWPIs, &dwProcCount))
	{
		//Go through all processes retrieved
		for (DWORD i = 0; i < dwProcCount; i++)
		{
#ifdef _DEBUG
			System::Console::WriteLine(gcnew System::String(pWPIs[i].pProcessName));// = process file name only, no path!
			System::Console::WriteLine(pWPIs[i].ProcessId.ToString());// = process ID
			System::Console::WriteLine(pWPIs[i].SessionId.ToString());// = session ID, if you need to limit it to the logged in user processes
			System::Console::WriteLine(pWPIs[i].pUserSid); //= user SID that started the process
#endif
		}
	}
}

WTS_PROCESS_INFO* WTSEnumerateProcessesFunctor::operator()() {
	DWORD dwProcCount = 0;
	if (WTSEnumerateProcesses(WTS_CURRENT_SERVER_HANDLE, NULL, 1, &pWPIs, &dwProcCount)) return pWPIs;
	else throw NullArgumentException(TEXT("WTSEnumerateProcessesFunctor::operator()"));
}

WTSEnumerateProcessesFunctor::~WTSEnumerateProcessesFunctor()
{
	if (pWPIs)
	{
		WTSFreeMemory(pWPIs);
		pWPIs = NULL;
	}
}































































/*CoInitializeExFunctor::CoInitializeExFunctor()
{
	hr = CoInitializeEx(0, COINIT_MULTITHREADED);
		/*if (FAILED(hr)) {
			throw std::exception("CoInitializeEx ");
		}
}
CoInitializeExFunctor::~CoInitializeExFunctor() {}

CoInitializeSecurityFunctor::CoInitializeSecurityFunctor()
{
	hr = CoInitializeSecurity(
		NULL,                        // Security descriptor    
		-1,                          // COM negotiates authentication service
		NULL,                        // Authentication services
		NULL,                        // Reserved
		RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication level for proxies
		RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation level for proxies
		NULL,                        // Authentication info
		EOAC_NONE,                   // Additional capabilities of the client or server
		NULL);
}


CoInitializeSecurityFunctor::~CoInitializeSecurityFunctor()
{
	CoUninitialize();
}
CoCreateInstanceFunctor::CoCreateInstanceFunctor(IWbemLocator*& pLoc) : pLoc_(pLoc)
{
	hr = CoCreateInstance(CLSID_WbemLocator, 0,
		CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID *)&pLoc);
}


CoCreateInstanceFunctor::~CoCreateInstanceFunctor()
{
	if (pLoc_ != NULL) pLoc_->Release();
}

ConnectServerFunctor::ConnectServerFunctor(IWbemLocator* pLoc, IWbemServices*& pSvc) : pSvc_(pSvc)
{
	hr = pLoc->ConnectServer(
		BSTR(L"root\\OpenHardwareMonitor"),  //namespace <--dozmiany
		NULL,       // User name 
		NULL,       // User password
		0,         // Locale 
		NULL,     // Security flags
		0,         // Authority 
		0,        // Context object 
		&pSvc);   // IWbemServices proxy
}
ConnectServerFunctor::~ConnectServerFunctor()
{
	if (pSvc_ != NULL) pSvc_->Release();
}

CoSetProxyBlanketFunctor::CoSetProxyBlanketFunctor(IWbemServices* pSvc)
{
	hr = CoSetProxyBlanket(pSvc,
		RPC_C_AUTHN_WINNT,
		RPC_C_AUTHZ_NONE,
		NULL,
		RPC_C_AUTHN_LEVEL_CALL,
		RPC_C_IMP_LEVEL_IMPERSONATE,
		NULL,
		EOAC_NONE);
}
CoSetProxyBlanketFunctor::~CoSetProxyBlanketFunctor()
{

}
ExecQueryFunctor::ExecQueryFunctor(IWbemServices* pSvc, IEnumWbemClassObject*& pEnum) : pEnum_(pEnum)//"Select from..."
{
	hr = pSvc->ExecQuery(bstr_t("WQL"),
		bstr_t("SELECT * FROM Hardware"), //<------------!!!
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnum);
}
ExecQueryFunctor::~ExecQueryFunctor()
{
	if (pEnum_ != NULL) pEnum_->Release();
	//if...
}
/*
while (pEnum)
{
	hr = pEnum->Next(WBEM_INFINITE, 1,
		&pclsObj, &uReturn);
	if (FAILED(hr)) {
		CoUninitialize();
		pSvc->Release();
		pLoc->Release();
		pEnum->Release();
		pclsObj->Release();
		throw std::exception("Get the data from the query in step 6 ");
	}
	if (0 == uReturn)
	{
		break;
	}
	VARIANT vtProp;
	VariantInit(&vtProp);
	// Get the value of the Name property
	hr = pclsObj->Get(L"__CLASS", 0, &vtProp, 0, 0);
	if (FAILED(hr)) {
		CoUninitialize();
		pSvc->Release();
		pLoc->Release();
		pEnum->Release();
		pclsObj->Release();
		throw std::exception("pclsObj->Get ");
	}
	std::cout << "__CLASS: " << std::endl;
	assert(vtProp.bstrVal != nullptr);
	std::wstring ws(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
	printf("%S", vtProp.bstrVal);
	std::cout << std::endl;
	VariantClear(&vtProp);
	pclsObj->Release(); //!!!!
}


EnumerateFunctor::EnumerateFunctor(IWbemServices* pSvc, IEnumWbemClassObject* pEnum)
{
	ULONG uReturn = 0;
	notBroke = false;
	while (pEnum)
	{
		hr = pEnum->Next(WBEM_INFINITE, 1,
			&pclsObj, &uReturn);
		if (0 == uReturn)
		{
			hr = 0;
			break;
		}
		notBroke = true;
		VARIANT vtProp;
		VariantInit(&vtProp);
		// Get the value of the Name property
		hr = pclsObj->Get(L"__CLASS", 0, &vtProp, 0, 0);
		assert(vtProp.bstrVal != nullptr);
		std::wstring ws(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
		printf("%S", vtProp.bstrVal);
		VariantClear(&vtProp);
	}
}

EnumerateFunctor::~EnumerateFunctor() { if (pclsObj != NULL && notBroke) pclsObj->Release(); }*/
