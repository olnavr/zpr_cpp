#include "stdafx.h"
#include "Ohm.h"

void OHMWrapper::setFlags()
{
	comp_->MainboardEnabled = true;
	comp_->FanControllerEnabled = true;
	comp_->CPUEnabled = true;
	comp_->GPUEnabled = true;
	comp_->RAMEnabled = true;
	comp_->HDDEnabled = true;
}
OHMWrapper::OHMWrapper()
{
	comp_ = gcnew Computer;
	hardware_ = gcnew List<HElement^>;
	printVisitor_ = gcnew OHMPrintVisitor(this);
	comp_->Open();
	setFlags();
	printVisitor_->VisitComputer(comp_);
}
void OHMWrapper::update()
{
	printVisitor_->VisitComputer(comp_);
}

OHMWrapper::~OHMWrapper()
{
	comp_->Close();
}

void OHMWrapper::clear() { hardware_->Clear();}

void OHMWrapper::addHardware(Hardware ^ hardware) { hardware_->Add(gcnew HElement(hardware)); }

