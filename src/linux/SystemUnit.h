/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SystemUnit.h
 * Author: usr5558
 *
 */

#ifndef SYSTEMUNIT_H
#define SYSTEMUNIT_H

#include "Container.h"

#include <memory>
#include <iostream>
#include <fstream> 
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <array>


class SystemUnit {
public:
    friend class SystemModel;
    virtual std::string getUsage(void);
    std::string name;
protected:
    const std::string path;
    std::ifstream file;
};

typedef std::shared_ptr<SystemUnit> SystemUnitPrt;
typedef std::map<std::string,SystemUnitPrt> UnitMap;

#endif /* SYSTEMUNIT_H */

