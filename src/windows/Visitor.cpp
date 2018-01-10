#include "stdafx.h"
#include "Ohm.h"


void __clrcall OHMPrintVisitor::VisitComputer(Computer^ icomputer)
{
	if (icomputer == nullptr) throw NullArgumentException(TEXT("OHMPrintVisitor VisitComputer"));
	clear();
	icomputer->Traverse(this);
}

void __clrcall OHMPrintVisitor::VisitHardware(Hardware^ ihardware)
{
	if (ihardware == nullptr) throw NullArgumentException(TEXT("OHMPrintVisitor VisitHardware"));
	ihardware->Update();
	wrap_->addHardware(ihardware);
	h_ = ihardware;
#ifdef _DEBUG
	//System::Console::Write(str_);
#endif
	//ihardware->Traverse(this);
}
void __clrcall OHMPrintVisitor::VisitSensor(Sensor^ isensor)
{
	//throw NonOverloadedException(TEXT("OHMPrintVisitor VisitSensor"));
	//System::String^ str = print(isensor);
#ifdef _DEBUG
		//System::Console::Write(str_);
#endif
}
void __clrcall OHMPrintVisitor::VisitParameter(Parameter^ iparam)
{
	//throw NonOverloadedException(TEXT("OHMPrintVisitor VisitParam"));
}


void OHMPrintVisitor::clear()
{
	wrap_->clear();
}


System::String ^ OHMPrintVisitor::print(System::String ^ name, System::String ^ type)
{
	System::String ^ str = TEXT("");
	str += TEXT("Name: ") + name + TEXT("\r\n");
	str += TEXT("Type: ") + type + TEXT("\r\n");
	return str;
}

System::String ^ OHMPrintVisitor::print(Hardware ^ ihardware) 
{
	auto typetemp = System::String::Copy(ihardware->HardwareType.ToString());
	System::String ^ value = TEXT("");
	return print(ihardware->Name, typetemp);
}

System::String ^ OHMPrintVisitor::print(Sensor ^ isensor) 
{
	auto nametemp = System::String::Copy(isensor->Name);
	auto typetemp = System::String::Copy(isensor->SensorType.ToString());
	auto valuetemp = System::String::Copy(isensor->Value.ToString());
#ifdef _DEBUG
	System::String ^ str = TEXT("");
	str += TEXT("       Name: ") + nametemp + TEXT("\r\n");
	str += TEXT("       Type: ") + typetemp + TEXT("\r\n");
	str += TEXT("       Value: ") + valuetemp + TEXT("\r\n");
#else
	System::String^ str = print(nametemp, typetemp);
	str += TEXT("Value: ") + valuetemp + TEXT("\r\n");
#endif _DEBUG

	return str;
}



//TODO: test correctness of reaction to null argument
void __clrcall OHMUpdateVisitor::VisitComputer(Computer^ icomputer)
{
	if (icomputer == nullptr) throw NullArgumentException(TEXT("OHMUpdateVisitor VisitComputer"));
	icomputer->Traverse(this);
}

void __clrcall OHMUpdateVisitor::VisitHardware(Hardware^ ihardware)
{
	if (ihardware == nullptr) throw NullArgumentException(TEXT("OHMUpdateVisitor VisitHardware"));
	ihardware->Update();
	//System::Console::WriteLine(TEXT("UPDATEVISITOR"));
	for each (Hardware^ i in ihardware->SubHardware)
	{
		i->Accept(this);
	}
	//ihardware->Traverse(this);
}
void __clrcall OHMUpdateVisitor::VisitSensor(Sensor^ isensor)
{
	//throw NonOverloadedException(TEXT("OHMUpdateVisitor VisitSensor"));
}

void __clrcall OHMUpdateVisitor::VisitParameter(Parameter^ iparam)
{
	//throw NonOverloadedException(TEXT("OHMUpdateVisitor VisitParam"));
}