/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SystemModel.cpp
 * Author: usr5558
 * 
 */

#include "SystemModel.h"

void SystemModel::addUnit(SystemUnitPrt& un){
    this->systemUnits.emplace(un->name,un);
}

void SystemModel::addContener(ContainerPtr& c){
    this->container_ = c;
};

void SystemModel::update(){
    for(auto elem: systemUnits){
        
        container_->write(elem.first,elem.second->getUsage() );
   
    }
}

