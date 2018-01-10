/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Memory.h
 * Author: usr5558
 *
 */

#ifndef MEMORY_H
#define MEMORY_H

#include "SystemUnit.h"

class Memory: public SystemUnit {
    public:
        Memory(){name = "RAM_usage";};
        std::string getUsage();
    private:
        std::string usage;
        const std::string path = "/proc/meminfo";
};

#endif /* MEMORY_H */

