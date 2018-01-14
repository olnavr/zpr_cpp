#include "Element.h"

typedef OpenHardwareMonitor::Hardware::IHardware Hardware;
typedef OpenHardwareMonitor::Hardware::ISensor Sensor;

HElement::HElement(Hardware ^ h) : h_(h), sensors_(gcnew List<SElement^>) 
{
	if (h == nullptr) throw NullArgumentException(TEXT("HElement ctor"));
	for each(Sensor^ sensorIterated in h->Sensors) sensors_->Add(gcnew SElement(sensorIterated));
}

std::string HElement::getName() {
	StringConverter conv;
	return conv(h_->Name);
}

std::string HElement::getType()
{
	StringConverter conv;
	std::string str = conv(h_->HardwareType.ToString());
	return (str == "GpuATI" || str == "GpuNvidia") ? std::string("Graphics Card") : str;
}

List<SElement^>^ HElement::getSensors() { return sensors_; }

Hardware^ HElement::getHardware() { return h_; }

SElement::SElement(Sensor ^ h) : s_(h) 
{
	if (h == nullptr) throw NullArgumentException(TEXT("SElement ctor"));
}

std::string SElement::getName()
{
	StringConverter conv;
	return conv(s_->Name);
}

std::string SElement::getType()
{
	StringConverter conv;
	return conv(s_->SensorType.ToString());
}

//TODO: BETTER CHANGE TO INT
std::string SElement::getValue()
{
	StringConverter conv;
	return conv(s_->Value.ToString());
}


Sensor ^ SElement::getSensor() { return s_; }



/*namespace isFunctions {

	void isGpuATI(System::String ^& type_)
	{
		type_ = "Graphics Card";
	}
	void isTemperature(System::String ^& value_)
	{
		System::Double temp = System::Convert::ToDouble(value_);
		value_ = (temp.ToString("00.0") + " C");
	}

	void isClock(System::String ^& value_)
	{
		System::Double clockRate = System::Convert::ToDouble(value_);
		if (clockRate < 1000)
		{
			value_ = (clockRate.ToString("F1") + " MHZ");
		}
		else
		{
			clockRate = clockRate / 1000;
			value_ = (clockRate.ToString("F1") + " GHZ");
		}
	}
	void isControlOrLoad(System::String ^& value_)
	{
		System::Double percent = System::Convert::ToDouble(value_);
		value_ = (percent.ToString("F0") + " %");
	}
	void isPower(System::String ^& value_)
	{
		System::Double watts = System::Convert::ToDouble(value_);
		value_ = (watts.ToString("F3") + " W");
	}
	void isVoltage(System::String ^& value_)
	{
		System::Double voltage = System::Convert::ToDouble(value_);
		value_ = (voltage.ToString("F0") + " V");
	}

	void isFan(System::String ^& value_)
	{
		System::Double rpm = System::Convert::ToDouble(value_);
		value_ = (rpm.ToString("F0") + " RPM");
	}
}

System::String ^ whatType::operator()(System::String ^ a, System::String^ value)
{
	try {
		//typechange
		if (a->Equals("Temperature"))		isFunctions::isTemperature(value);
		else if (a->Equals("Clock"))		isFunctions::isClock(value);
		else if (a->Equals("Voltage"))		isFunctions::isVoltage(value);
		else if (a->Equals("Fan"))			isFunctions::isFan(value);
		else if (a->Equals("Power"))		isFunctions::isPower(value);

		else if (a->Equals("Control") || a->Equals("Load"))	isFunctions::isControlOrLoad(value);
		else;
		return value;
	}
	catch (System::FormatException^ e)
	{
		return e->ToString();
	}
	catch (System::OverflowException^ e)
	{
		return e->ToString();
	}
}*/
