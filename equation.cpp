#include "equation.hpp"
#include <algorithm>


bool cEquation::nonZero(){ return terms.size()!=0;}
void cEquation::copyFrom(const cEquation &g){
    terms=g.terms;
    updateHighest();
    //std::cout<<"new copied equation"<<std::endl;
}

void cEquation::removeRedundantTerms(){    
    terms.sort([](cMonome &a, cMonome &b) {return a.compareWith(b)==eBigger;});
    int counter=0;
    for(std::list<cMonome>::iterator it1=terms.begin();it1!=terms.end();it1++){
        std::list<cMonome>::iterator it2=it1;
        for(++it2;
        (it2!=terms.end())&&
        (it1->compareWith(it2)==eEqual);
        it2++){
            (*it1)+=(*it2);
            terms.erase(it2);
            it2=it1;
        }
    }
    terms.remove_if([](cMonome &x){return x.coef==0;});
}
void cEquation::updateHighest(){
    terms.sort([](cMonome &a, cMonome &b) {return a.compareWith(b)==eBigger;});
    highestTerm=terms.begin();
    for(std::list<cMonome>::iterator it=terms.begin();it!=terms.end();it++){
        if(it->compareWith(highestTerm)==eBigger){
            highestTerm=it;
        }
    }
}

std::string cEquation::toString(){
    if(!nonZero()){
        return "0";
    }
    std::string result="";
    for(std::list<cMonome>::iterator it=terms.begin();it!=terms.end();it++){
        result+= it->toString(
                    (it!=terms.begin())
                    ||(it->coef<0)
                );
    }
    return result;
}