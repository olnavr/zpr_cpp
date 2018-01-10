#ifdef _WIN32
#ifndef _VISITOR_H
#define _VISITOR_H

#include "stdafx.h"
#include "Exception.h"
ref class OHMWrapper;

typedef OpenHardwareMonitor::Hardware::IComputer  Computer;
typedef OpenHardwareMonitor::Hardware::IHardware  Hardware;
typedef OpenHardwareMonitor::Hardware::ISensor    Sensor;
typedef OpenHardwareMonitor::Hardware::IParameter Parameter;

ref class OHMUpdateVisitor : public OpenHardwareMonitor::Hardware::IVisitor //Visitor calling update on every IHardware object -> calling update on every ihardware is the only way of getting correct, updated values on sensors
{
public:
	OHMUpdateVisitor() {}
	virtual void __clrcall VisitComputer(Computer^ computer) sealed;
	virtual void __clrcall VisitHardware(Hardware^ hardware) sealed;
	virtual void __clrcall VisitSensor(Sensor^ sensor) sealed;
	virtual void __clrcall VisitParameter(Parameter^ parameter) sealed;
};

ref class OHMPrintVisitor : public OpenHardwareMonitor::Hardware::IVisitor //Visitor - its function is to provide OHMWrapper with handles to instantiated IHardware/ISensor in OpenHardwareMonitorLib.dll
{
	OHMWrapper^ wrap_; //handle to OHMWrapper initialize list of HElements
	//System::String^ str_;
	Hardware^ h_; //< helping handle to OHM::Hardawre class for easy adding SElements to member list of HElement
public:
	explicit OHMPrintVisitor(OHMWrapper^ wrap) : wrap_(wrap) {} // str_(gcnew System::String(TEXT(""))) {}// cont_(cont) {} //str_(gcnew System::String(TEXT(""))) {}

	virtual void __clrcall VisitComputer(Computer^ computer) sealed;
	virtual void __clrcall VisitHardware(Hardware^ hardware) sealed;
	virtual void __clrcall VisitSensor(Sensor^ sensor) sealed;
	virtual void __clrcall VisitParameter(Parameter^ parameter) sealed;
	virtual System::String^ __clrcall print(System::String^, System::String^) sealed;
	virtual System::String^ __clrcall print(Hardware^) sealed;
	virtual System::String^ __clrcall print(Sensor^)  sealed;
	void update()
	{
	}
	void clear();
	//System::String^ getString() { return str_; }
};
//virtual System::Int32 CompareTo(OHMItem^ item);

#endif // !_OHM_H
#endif