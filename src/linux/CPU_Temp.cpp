/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CPU_Temp.cpp
 * Author: usr5558
 * 
 */

#include "CPU_Temp.h"

std::string CPU_Temp::getUsage(){
    float t;
    std::string usage;
    std::string temp;
    this->file.open(this->path);
    std::getline(file,temp);
    std::istringstream scan(temp);
    scan>>t;
    t = t/1000;
    usage = std::to_string(t);
    this->file.close();
    return usage;
}

