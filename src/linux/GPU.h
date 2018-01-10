/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GPU.h
 * Author: usr5558
 *
 * Created on 11 грудня 2017, 2:06
 */

#ifndef GPU_H
#define GPU_H

#include "SystemUnit.h"

struct GPU: public SystemUnit {
    public:
        std::string getUsage();
    private:
        std::string usage;
        const std::string path = ""; //todo 
        const std::string name = "GPU";
};

#endif /* GPU_H */

