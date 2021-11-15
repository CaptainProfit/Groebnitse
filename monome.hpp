#include <iostream>
#include <list>
#include <string>
#include "order.hpp"
#pragma once
extern int outputFormat;

class cMonome{    
    public:
    std::vector<int> power;
    int dim=0;
    int coef=1;
    cMonome(int n);
    bool isConstant(){
        for(int i=0;i<power.size();i++)
            if(power[i]!=0)
                return false;
        return true;
    }
    //compareWith - функция в которой задается порядок.
    eCompare compareWith(const cMonome &that){
        return monomeOrder(this->power, that.power);
    }
    eCompare compareWith(std::list<cMonome>::iterator it){
        return monomeOrder(this->power, it->power);        
    }  
    cMonome & operator*=(const int &that);
    cMonome & operator*=(const cMonome &that);
    cMonome & operator+=(const cMonome &that);
    char var(int i);
    std::string toString(bool isSigned=true);
};