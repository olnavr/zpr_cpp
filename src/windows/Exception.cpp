#include "stdafx.h"
#include "Exception.h"


IException::IException()
{
}


IException::~IException()
{
}


TCHAR * NullArgumentException::accept(ExceptionVisitor & v) { return v.visit(*this); }

TCHAR * NullArgumentException::message() { return errString_; }

TCHAR *  WmiFunctorException::accept(ExceptionVisitor & v) { return v.visit(*this); }

TCHAR *  WmiFunctorException::message() { return errString_; }

TCHAR *  NonOverloadedException::accept(ExceptionVisitor & v) { return v.visit(*this); }

TCHAR *  NonOverloadedException::message() { return errString_; }

















//TCHAR * CoInitializeException::accept(ExceptionVisitor & v) { return v.visit(*this); }

//TCHAR * CoInitializeException::message() { return TEXT("CoInitializeException"); }

/*TCHAR* ConnectServerException::accept(ExceptionVisitor & v){ return v.visit(*this); }

TCHAR * ConnectServerException::message() { return TEXT("ConnectServerException"); }

TCHAR * CoSetProxyBlanketException::accept(ExceptionVisitor & v) { return v.visit(*this); }

TCHAR * CoSetProxyBlanketException::message() { return TEXT("CoSetProxyBlanketException"); }

TCHAR * CoCreateInstanceException::accept(ExceptionVisitor & v) { return v.visit(*this); }

TCHAR * CoCreateInstanceException::message() { return TEXT("CoCreateInstanceException"); }

TCHAR * ExecQueryException::accept(ExceptionVisitor & v) { return v.visit(*this); }

TCHAR * ExecQueryException::message() { return TEXT("ExecQueryException"); }

TCHAR * CoInitializeSecurityException::accept(ExceptionVisitor & v){ return  v.visit(*this); }

TCHAR * CoInitializeSecurityException::message() { return TEXT("CoInitializeSecurityException"); }



TCHAR * EnumerateException::accept(ExceptionVisitor & v) { return v.visit(*this); }

TCHAR * EnumerateException::message() { return TEXT("EnumerateException"); }*/


