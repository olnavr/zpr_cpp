/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Memory.cpp
 * Author: usr5558
 * 
 * Created on 11 грудня 2017, 1:51
 */

#include "Memory.h"


std::string Memory::getUsage(){
    const int N = 5;
    std::string temp;
    std::string usage;
    this->file.open(path);
    for(int i=0;i<N;++i){
        std::getline(file,temp);
        usage+=temp+"\n";
    }
    this->file.close();    
    return usage;
};
