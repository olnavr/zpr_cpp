/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OS.h
 * Author: usr5558
 *
 * Created on 11 грудня 2017, 2:18
 */

#ifndef OS_H
#define OS_H

#include "SystemUnit.h"


class OS: public SystemUnit {
    public:
        OS(){name = "OS";};
        std::string getUsage(void);
    private:
        const std::string path = "/proc/version";
};

#endif /* OS_H */

