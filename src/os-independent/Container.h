#ifndef _CONTAINER_H
#define _CONTAINER_H
#include "stdafx.h"
#include "Ohm.h"
#include <map>
#ifdef _WIN32
#include <functional>
#endif
class Container
{
public:
	void write(std::string& name, std::string& val);
	void update(std::string& name, std::string& val);
	std::string read(std::string& name);
//private:
	std::map<std::string, std::string> container_;
};

#ifdef _WIN32
ref class WindowsContainer
{
	OHMWrapper^ ohm_;
	Container* cont_;
public:
	WindowsContainer(Container* cont, OHMWrapper^ ohm) : cont_(cont), ohm_(ohm) {}
	void add();
	void update();
};
#endif
#endif