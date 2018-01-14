#include "Container.h"

void Container::write(std::string & name, std::string & val)
{
	container_.emplace(name, val);
}

void Container::update(std::string & name, std::string & val)
{
	auto pair = container_.find(name);
	if (pair != container_.end())
		pair->second = val;
	else
		throw std::exception("container_ update -> map reached end iterator after update -> key(name) not found");
}

std::string Container::read(std::string & name)
{
	auto pair = container_.find(name);
	if (pair != container_.end())
		return pair->second;
	else
		return "container_ read => map reached end iterator after read => key(name) not found";
}

#ifdef _WIN32
using namespace std::placeholders;
using FuncPtr = std::function<void(std::string&, std::string&)>;

template <typename TFuncPtr>
auto execFuncOnSensorList = [&](OHMWrapper^ ohm, TFuncPtr& f)
{
	auto hlist = ohm->getHardware();
	for each (auto helement in hlist)
	{
		auto sensorList = helement->getSensors();
		for each(auto selement in sensorList)
		{
			f(selement->getName() + 
#ifdef _WIN32
				" " +
#endif
				selement->getType(), selement->getValue());
		}
	}
};
void WindowsContainer::add()
{
	FuncPtr f;
	f = std::bind(&Container::write, std::ref(*cont_), _1, _2);
	execFuncOnSensorList<FuncPtr>(ohm_, f);
}
void WindowsContainer::update()
{
	FuncPtr f;
	f = std::bind(&Container::update, std::ref(*cont_), _1, _2);
	ohm_->update();
	execFuncOnSensorList<FuncPtr>(ohm_, f);
}
#endif