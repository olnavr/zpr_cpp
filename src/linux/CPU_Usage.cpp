/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CPU.cpp
 * Author: usr5558
 * 
 */

#include "CPU_Usage.h"




//todo 
std::string CPU_Usage::getUsage(){
    std::string usage;
    std::array<float,4> u;
    std::vector<float> res;
    unsigned int i = 0;
    std::string cr;
    std::string coreName;
    this->file.open(this->path);

    while(1){
        float a,b;
        std::getline(file,cr);
        if(u_prev.size()<=i){
            u_prev.push_back(u);
        }
        else u_prev[i] = u;
        u_prev[i] = u;
        ++i;
        if(cr.compare(0,3,"cpu"))
            break;
        std::istringstream scan(cr);
        scan>>coreName>>u[0]>>u[1]>>u[2]>>u[3];
        a = u[0] + u[1] + u[2] - (u_prev[i][0] + u_prev[i][1] + u_prev[i][2]);
        b = u[0] + u[1] + u[2] + u[3] - (u_prev[i][0] + u_prev[i][1] + u_prev[i][2]+ u_prev[i][3]);
        res.push_back(a/b*100);
        
    };
    for(auto el: res){
        usage += std::to_string(el);
        usage += ' ';
    }
    this->file.close();
    return usage;
}
