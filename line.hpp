#include "equation.hpp"
#pragma once

class cLine{ 
    //static cEquation;
    public:
    int id;
    cEquation equation;
    std::vector<cEquation> multipliers;
    void init(cEquation &equation,int id, int dimension,int systemSize);
    std::string toString();
    cLine operator*=(const cMonome& mon);
    cLine operator+=(const cLine& rline);
    void removeRedundantTerms();
    void updateHighest();
};