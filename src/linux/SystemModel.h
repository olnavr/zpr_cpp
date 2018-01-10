/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SystemModel.h
 * Author: usr5558
 */

#ifndef SYSTEMCONTROL_H
#define SYSTEMCONTROL_H

#include "SystemUnit.h"
#include "Container.h"

class SystemModel{

public:
    void addUnit(SystemUnitPrt&);
    void addContener(ContainerPtr&);
    void update(void);
private:
    UnitMap systemUnits;
    ContainerPtr container_;
    
};

#endif /* SYSTEMCONTROL_H */

