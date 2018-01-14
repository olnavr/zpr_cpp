// ConsoleApplication6.cpp : main project file.

#include <stdio.h>
#include <algorithm>
#include <chrono>
#ifdef _WIN32
	#include <stdlib.h>
	#include <map>
	#include <assert.h>
	#include <iostream>
	#include <string>
	#include <sstream>
	#include <string.h>
	#include "stdafx.h"
	#include "Container.h"
	#include "CassServer.h"
#endif
#ifdef linux
	#include <cstdlib>
	#include <unistd.h>
	#include "SystemUnit.h"
	#include "CPU_Usage.h"
	#include "SystemModel.h"
	#include "Memory.h"
	#include "Container.h"
	#include "CPU_Temp.h"
	#include "OS.h"
#endif
//Initialization of crucial resources

auto update = [](CassServ* cass
#ifdef _WIN32
	,WindowsContainer^ contUpdater
#endif
#ifdef linux

#endif
	)
{
	auto period = cass->getUpdatePeriod();
	std::cout << "Period: " << period;
	auto now = std::chrono::system_clock::now();
	auto lastUpdateTime = std::chrono::system_clock::now();
	auto timepoint = std::chrono::seconds(static_cast<int>(period));
	auto sleepForInSeconds = static_cast<int>(period);

	cass->sendContainerData();
#ifdef _WIN32
	contUpdater->update();
#endif
	while (true)
	{
		now = std::chrono::system_clock::now();
		if ((now - lastUpdateTime) > timepoint)
		{
			cass->sendContainerData();
#ifdef _WIN32
			contUpdater->update(); //windows sensor information update
#endif
#ifdef linux

#endif
			lastUpdateTime = std::chrono::system_clock::now();
			//timepoint = std::chrono::seconds(static_cast<int>(cass->getUpdatePeriod()));
		}
#ifdef _WIN32
		System::Threading::Thread::Sleep(System::TimeSpan::FromSeconds(sleepForInSeconds)); //windows thread sleep
#endif
#ifdef linux

#endif
	}
};

void run()
{
	std::shared_ptr<Container> container = std::make_shared<Container>();

	#ifdef _WIN32
		OHMWrapper^ wrapper = gcnew OHMWrapper;
		WindowsContainer^ windowsContainer = gcnew WindowsContainer(container.get(), wrapper);
		windowsContainer->add();
	#endif

	#ifdef _DEBUG
		std::for_each(std::begin(container->container_), std::end(container->container_), [](auto& pair) {
			std::cout << pair.first << " " << pair.second << std::endl;
		});
	#endif

	CassServ cassServ(container.get(), "127.0.0.1");

	auto preparation_went_well = cassServ.prepareCassandra();
	if (!preparation_went_well) return;

	#ifdef _WIN32
		update(&cassServ, windowsContainer);
	#endif
	#ifdef linux
		//
	#endif
}

#ifdef _WIN32
int main(array<System::String ^> ^args)
{
#endif

#ifdef linux
	using namespace std;
int main(int argc, char** argv) {
	SystemModel s;
	ContainerPtr c(new Container);
	SystemUnitPrt u(new CPU_Usage);
	SystemUnitPrt z(new CPU_Temp);
	SystemUnitPrt x(new Memory);
	SystemUnitPrt q(new OS);
	s.addContener(c);
	s.addUnit(u);
	s.addUnit(z);
	s.addUnit(x);
	s.addUnit(q);
	s.update();
	cout << c->read("CPU_Usage") << endl;
	cout << c->read("CPU_Temp") << endl;
	cout << c->read("RAM_usage") << endl;
	cout << c->read("OS") << endl;
#endif

	run();

	return 0;
}
