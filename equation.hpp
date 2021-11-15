#include "monome.hpp"
#include <list>
#pragma once

class cEquation{
    public:
    //static cMonome mUnit((int)3);
    std::list<cMonome> terms;
    std::list<cMonome>::iterator highestTerm;
    
    bool nonZero();
    void copyFrom(const cEquation &eq);
    cEquation & operator+=(const cMonome& mon){
        terms.push_back(mon);
        removeRedundantTerms();
        updateHighest();     
        return *this;
    }
    cEquation & operator+=(const cEquation& eq){
        for(std::list<cMonome>::const_iterator it=eq.terms.begin();it!=eq.terms.end();it++){
            terms.push_back(*it);
        }
        removeRedundantTerms();    
        updateHighest();   
        return *this;
    }
    cEquation & operator*=(const cMonome& mon){
        for(std::list<cMonome>::iterator it=terms.begin();it!=terms.end();it++){
            (*it)*=mon;
        }  
        return *this;
    }
    cEquation & operator*=(const cEquation& eq){
        cEquation result;
        for(std::list<cMonome>::const_iterator it=eq.terms.begin();it!=eq.terms.end();it++){
            cEquation result2(*this);
            result+=result2;
        }
        removeRedundantTerms();
        updateHighest();
        this->copyFrom(result); 
        return *this;
    }
    void removeRedundantTerms();//OK
    void updateHighest();//OK
    std::string toString();
    //cEquation(int a,int x,ffloat d){}
};