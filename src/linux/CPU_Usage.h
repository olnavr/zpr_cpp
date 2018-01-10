/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CPU.h
 * Author: usr5558
 *
 */

#ifndef CPU_H
#define CPU_H

#include "SystemUnit.h"
#include <array>

class CPU_Usage: public SystemUnit {
    public:
        CPU_Usage(){name = "CPU_Usage";}
        std::string getUsage();
    private:
        const std::string path = "/proc/stat";
	std::vector<std::array<float,4> > u_prev;
};

#endif /* CPU_H */

