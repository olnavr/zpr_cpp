#pragma once
#include "stdafx.h"
#include "Exception.h"
#include <Wtsapi32.h>
#pragma comment(lib,"Wtsapi32")

class WTSEnumerateProcessesFunctor //<Functor(command) containing list of current processes and returning the list by operator()
{
	WTS_PROCESS_INFO* pWPIs;
public:
	WTSEnumerateProcessesFunctor();
	WTS_PROCESS_INFO* operator()();
	//virtual HRESULT checkForException() override { if (FAILED(hr)) throw WmiFunctorException(TEXT("WTSEnumerateProcesses")); return hr; }
	~WTSEnumerateProcessesFunctor();
};