// ConsoleApplication6.cpp : main project file.

#include <stdio.h>
#include <algorithm>
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
void run()
{
	std::unique_ptr<Container> container = std::make_unique<Container>();

	#ifdef _WIN32
		OHMWrapper^ wrapper = gcnew OHMWrapper;
		WindowsContainer windowsContainer(container.get(), wrapper);
		windowsContainer.add();
	#endif

	#ifdef _DEBUG
		std::for_each(std::begin(container->container_), std::end(container->container_), [](auto& pair) {
			std::cout << pair.first << " " << pair.second << std::endl;
		});
	#endif

	CassServ cassServ(container.get(), "127.0.0.1");

	auto preparation_went_well = cassServ.prepareCassandra();
	if (!preparation_went_well) return;

	int i = 100;
	while (i-- > 0) {
		cassServ.sendContainerData();
		#ifdef _WIN32
			windowsContainer.update();
		#endif
	}
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
