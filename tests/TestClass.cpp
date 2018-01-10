#include "stdafx.h"
#include "TestClass.h"
#include "Ohm.h"
#include "WmiFunctor.h"
#include "../os-independent/Container.h"

#ifdef _DEBUG
#define BOOST_TEST_MODULE TestClass Test
#include <boost/test/unit_test.hpp>
#include <memory>

SElement ^ TestClass::testGetSensor()
{
	auto wrapperTested = gcnew OHMWrapper;
	auto hardwareList = wrapperTested->getHardware();
	auto sensorList = gcnew List<SElement^>;
	for each(auto h in hardwareList) //get first non 0 count sensorList
	{
		sensorList = h->getSensors();
		if (sensorList->Count != 0) break;
	}
	BOOST_REQUIRE(sensorList != nullptr);

	auto sensor = sensorList[0];
	BOOST_REQUIRE(sensor != nullptr);
	return sensor;
}

//TODO:divide test steps into seperate functions
BOOST_AUTO_TEST_SUITE(Element_test)
	BOOST_AUTO_TEST_CASE(Element_test_HElement_getName_1)
	{
		OHMWrapper^ wrapperTested = gcnew OHMWrapper;
		HElement^ hardware = wrapperTested->getHardware()[0];

		auto str = hardware->getName();
		BOOST_REQUIRE(str.size() != 0);
	}
	BOOST_AUTO_TEST_CASE(Element_test_HElement_getName_2)
	{
		OHMWrapper^ wrapperTested = gcnew OHMWrapper;
		HElement^ hardware = wrapperTested->getHardware()[0];
		StringConverter conv;
		auto str = hardware->getName();
		auto ihardware = hardware->getHardware();
		BOOST_REQUIRE(conv(ihardware->Name) == str);
	}
	BOOST_AUTO_TEST_CASE(Element_test_HElement_getType)
	{
		OHMWrapper^ wrapperTested = gcnew OHMWrapper;
		HElement^ hardware = wrapperTested->getHardware()[0];
		StringConverter conv;
		auto str = hardware->getType();
		auto ihardware = hardware->getHardware();
		BOOST_CHECK(conv(ihardware->HardwareType.ToString()) == str); //
	}
	BOOST_AUTO_TEST_CASE(Element_test_HElement_getSensors)
	{
		auto wrapperTested = gcnew OHMWrapper;
		auto hardwareList = wrapperTested->getHardware();
		auto sensorList = gcnew List<SElement^>;
		for each(auto h in hardwareList) //get first non 0 count sensorList
		{
			sensorList = h->getSensors();
			if (sensorList->Count != 0) break;
		}
		BOOST_REQUIRE(sensorList != nullptr);

		auto sensor = sensorList[0];
		BOOST_REQUIRE(sensor != nullptr);
	}
	BOOST_AUTO_TEST_CASE(Element_test_SElement_getName)
	{
		SElement^ sensor = TestClass::testGetSensor();
		auto str = sensor->getName();
		BOOST_REQUIRE(str.size() != 0);
	}
	BOOST_AUTO_TEST_CASE(Element_test_SElement_getValue)
	{
		SElement^ sensor = TestClass::testGetSensor();
		auto isensor = sensor->getSensor();
		auto str = sensor->getValue();
		BOOST_TEST_MESSAGE("SElement Value: ", str);
		BOOST_TEST_MESSAGE("Sensor Value: ", conv(isensor->Value.ToString()));
	}
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(OHMWrapper_test)
	BOOST_AUTO_TEST_CASE(OHMWrapper_test_getHardware) //<TEST: GETHARDWARE
	{
		bool isGood = false;
		OHMWrapper^ wrapperTested = gcnew OHMWrapper;
		auto hlist = wrapperTested->getHardware();
		BOOST_REQUIRE(hlist != nullptr);
		for each(HElement^ helement in hlist)
		{
			if ((helement->getType().compare("Graphics Card") == 0) || 
				(helement->getType().compare("GpuNvidia") == 0)) isGood = true; //check if any of the hardware is a graphics card
		}
		BOOST_REQUIRE(isGood);
	}
	BOOST_AUTO_TEST_CASE(OHMWrapper_test_addHardware)  //<TEST: ADDHARDWARE
	{
		OHMWrapper^ wrapperTested = gcnew OHMWrapper;
		int size = wrapperTested->getHardware()->Count;
		wrapperTested->addHardware((wrapperTested->getHardware())[0]->getHardware()); //take first element of the HElement List just to test that addHardware works
		BOOST_REQUIRE(wrapperTested->getHardware()->Count > size);
	}
	BOOST_AUTO_TEST_CASE(OHMWrapper_test_clear)
	{
		OHMWrapper^ wrapperTested = gcnew OHMWrapper;
		wrapperTested->clear(); //TEST: CLEAR
		auto size = wrapperTested->getHardware()->Count;
		BOOST_REQUIRE(size == 0);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(UpdateVisitor_test)
	BOOST_AUTO_TEST_CASE(UpdateVisitor_test)
	{
		auto updater = gcnew OHMUpdateVisitor;
		auto wrapperTested = gcnew OHMWrapper;
		auto hardwareList = wrapperTested->getHardware();

		auto strVectorBeforeUpdate = std::vector<std::string>();
		auto strVectorAfterUpdate = std::vector<std::string>();
		StringConverter conv;
	
		for each(auto hardware in hardwareList)
		{
			auto sensorList = hardware->getSensors();
			for each(auto sensor in sensorList)
				strVectorBeforeUpdate.push_back(conv(sensor->getSensor()->Value.ToString()));
		}

		wrapperTested->update(updater);

		for each(auto hardware in hardwareList)
		{
			auto sensorList = hardware->getSensors();
			for each(auto sensor in sensorList)
				strVectorAfterUpdate.push_back(conv(sensor->getSensor()->Value.ToString()));
		}

		BOOST_CHECK(strVectorAfterUpdate != strVectorBeforeUpdate);
		strVectorAfterUpdate.clear();
		strVectorBeforeUpdate.clear();
		for each(auto hardware in hardwareList)
		{
			auto sensorList = hardware->getSensors();
			for each(auto sensor in sensorList)
				strVectorBeforeUpdate.push_back(sensor->getValue());
		}

		wrapperTested->update(updater);

		for each(auto hardware in hardwareList)
		{
			auto sensorList = hardware->getSensors();
			for each(auto sensor in sensorList)
				strVectorAfterUpdate.push_back(sensor->getValue());
		}
		BOOST_CHECK(strVectorAfterUpdate != strVectorBeforeUpdate);
	}
BOOST_AUTO_TEST_SUITE_END()
//TODO: change of format of the process list
BOOST_AUTO_TEST_SUITE(Container_test)

	BOOST_AUTO_TEST_CASE(Container_test)
	{
	BOOST_TEST_MESSAGE("Container Test...");
		Container container;
		WindowsContainer windowsContainer(container);
		OHMWrapper^ wrapper = gcnew OHMWrapper;
		windowsContainer.add(wrapper);
		
		std::string str = "";
		std::string value = "";
		std::string key = "GPU CoreClock";

		value = container.read(key);
		BOOST_TEST_MESSAGE("Value: ", value, "for key: ", key);
		BOOST_CHECK(value != str);
	}
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_CASE(ProcessList_test)
{
	auto enumeratorTested = WTSEnumerateProcessesFunctor();
	BOOST_REQUIRE(enumeratorTested() != nullptr);
}

BOOST_AUTO_TEST_CASE(Event_test)
{
}
#endif

TestClass::TestClass()
{
}


TestClass::~TestClass()
{
}

