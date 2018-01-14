#ifdef _WIN32
#ifndef _ELEMENT_H
#define _ELEMENT_H
#include "stdafx.h"
#include "Exception.h"
#include "stdafx.h"
#include <msclr\marshal_cppstd.h>
using namespace System::Collections::Generic;

ref class SElement//< Sensor Element - OpenHardwareMonitor::Hardware::ISensor wrapper
{
	typedef OpenHardwareMonitor::Hardware::ISensor Sensor;
	Sensor^ s_; //<Handle to OHM Sensor
public:
	explicit SElement(Sensor^ h);
	std::string getName();
	std::string getType();
	std::string getValue(); //TODO: BETTER CHANGE TO INT
	Sensor^ getSensor();
};

ref class HElement//< Hardware Element - OpenHardwareMonitor::Hardware::IHardware wrapper
{
	typedef OpenHardwareMonitor::Hardware::IHardware Hardware;

	Hardware^ h_;//<Handle to OHM Hardware

	/** List of SElements (Sensor Elements).
	*  Filled by OHMPrintVisitor
	*/
	List<SElement^>^ sensors_;
public:
	explicit HElement(Hardware^ h);
	std::string getName();
	std::string getType();
	List<SElement^>^ getSensors();
	Hardware^ getHardware();
};

class StringConverter //functor converting system string to stD::string
{
public:
	StringConverter() {}
	std::string operator()(System::String^ str)
	{
		return msclr::interop::marshal_as<std::string>(str);
	}
};

#endif
#endif

/*struct whatType //<helping functor to change values from e.g. value before: 36.76532 to 36.7 C (for temperature sensor)
{
	whatType() {}
	System::String ^ operator()(System::String^, System::String^);
};

*/
