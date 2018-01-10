/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CPU_Temp.h
 * Author: usr5558
 *
 */

#ifndef CPU_TEMP_H
#define CPU_TEMP_H

#include "SystemUnit.h"

class CPU_Temp: public SystemUnit {
public:
    CPU_Temp(){name = "CPU_Temp";}
    std::string getUsage();
private:
    const std::string path = "/sys/class/hwmon/hwmon1/temp1_input";
};

#endif /* CPU_TEMP_H */

