#include "line.hpp"
#pragma once

class cSystem{
    public:
    int dimension=-1;
    int initialSystemSize=0;
    int systemSize=0;
    cEquation eUnitConstant;
    cMonome mUnitConstant=cMonome(_dim );    
    std::vector<cLine> lines;
    cSystem(std::list<cEquation> &startList,int dim);
    std::vector<std::string> toString(){
        std::vector<std::string> result;
        result.reserve(systemSize);
        int i=0;
        for(std::vector<cLine>::iterator it=lines.begin();it!=lines.end();it++){
            result.push_back(it->toString());
        }
        return result;
    }
 };