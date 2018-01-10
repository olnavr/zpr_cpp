#ifdef _WIN32
#ifndef _EXCEPTION_H
#define _EXCEPTION_H
#include "stdafx.h"

//class IVisitor;
class ExceptionVisitor;
/*! Exception interface */
class IException : public std::exception 
{
public:
	IException();
	virtual TCHAR* message() = 0;
	virtual TCHAR* accept(ExceptionVisitor&) = 0;
	virtual ~IException();
};
/*! exception class thrown when some function return null argument but shouldnt */
class NullArgumentException : public IException 
{
	TCHAR* errString_;
	NullArgumentException() : errString_(TEXT("")) {}
public:
	NullArgumentException(TCHAR* err) : errString_(err) {}
	virtual TCHAR* accept(ExceptionVisitor& v);
	virtual TCHAR* message() override;
	virtual ~NullArgumentException() {}
};

/*! exception class thrown by wmifunctors */
class WmiFunctorException : public IException
{
	TCHAR* errString_;
	WmiFunctorException() : errString_(TEXT("")) {}
public:
	WmiFunctorException(TCHAR* err) : errString_(err) {}
	virtual TCHAR* accept(ExceptionVisitor& v);
	virtual TCHAR* message() override;
	virtual ~WmiFunctorException() {}
};

/*!exception class thrown when virtual function overloaded only to use an interface is called*/
class NonOverloadedException : public IException
{
	TCHAR* errString_;
	NonOverloadedException() : errString_(TEXT("")) {}
public:
	NonOverloadedException(TCHAR* err) : errString_(err) {}
	virtual TCHAR* accept(ExceptionVisitor& v);
	virtual TCHAR* message() override;
	virtual ~NonOverloadedException() {}
};
/*!Native visitor interface*/
/*class IVisitor
{
public:
	IVisitor() {}
	virtual TCHAR* visit(IException&) = 0;
	virtual ~IVisitor() {}
};*/

/*! Exception visitor, visits IException objects to get the message associated to the exception*/
class ExceptionVisitor// : public IVisitor
{
public:
	ExceptionVisitor() {}
	TCHAR* visit(IException& e) //< visits Exception; returns error message for e.g. debug
	{ 
		return e.message(); }
	virtual ~ExceptionVisitor() {}
};
#endif
#endif