#ifdef _WIN32
#ifndef _OHM_H
#define _OHM_H

#include "stdafx.h"
#include "Exception.h"
#include "Visitor.h"
#include "Element.h"
using namespace System::Collections::Generic;

/*! Wrapper for OpenHardwareMonitorLib.dll */
ref class OHMWrapper //
{
	using Computer = OpenHardwareMonitor::Hardware::Computer  ;
	using Hardware = OpenHardwareMonitor::Hardware::IHardware ;
	using Sensor   = OpenHardwareMonitor::Hardware::ISensor	 ;

	/** Handle to OpenHardwareMonitor::Hardware::Computer.
	*	This wrapper is responsible for the lifetime of this object 
	*	This class contains all information provided by OpenHardwareMonitorLib
	*/
	Computer^ comp_;
	/** List of HElements (Hardware Elements).
	*  Filled by OHMPrintVisitor
	*/
	List<HElement^>^ hardware_;

	/** Handle to OHMPrintVisitor.
	*  This wrapper is responsible for the lifetime of this member object
	*	
	*/
	OHMPrintVisitor^ printVisitor_;
public:
	OHMWrapper();
	~OHMWrapper();
	void clear();
	void addHardware(Hardware^); //add Hardware to the list ->function called by OHMPrintVisitor
	void update();
	void setFlags();

	auto getHardware() { return hardware_; }
	auto getSensors(HElement^ h) { return h->getSensors(); }
};

#endif // !_OHM_H
#endif