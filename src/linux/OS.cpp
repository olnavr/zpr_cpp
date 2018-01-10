/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OS.cpp
 * Author: usr5558
 * 
 * Created on 11 грудня 2017, 2:18
 */

#include "OS.h"


std::string OS::getUsage(void){
    std::string usage;
    this->file.open(this->path);
    std::getline(file,usage);
    usage+="\n";
    this->file.close();
    return usage;
};
