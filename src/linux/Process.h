/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Process.h
 * Author: usr5558
 *
 * Created on 11 грудня 2017, 2:21
 */

#ifndef PROCESS_H
#define PROCESS_H

#include "SystemUnit.h"

struct  Process: public SystemUnit {
     public:
        Process(){name = "Process";};
        std::string getUsage(void);
    private:
        const std::string path = ""; //todo
};

#endif /* PROCESS_H */

