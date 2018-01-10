/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Display.h
 * Author: usr5558
 *
 * Created on 11 грудня 2017, 3:02
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "Container.h"

class Interface {
public:
    std::string read(std::string);
private:
    ContainerPtr container;
};

#endif /* DISPLAY_H */

