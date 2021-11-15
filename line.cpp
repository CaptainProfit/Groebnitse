#include "line.hpp"

cLine operator*(cLine line, const cMonome& mon){        
        line.id=-1;
        return line*=mon;
}
cLine operator+(cLine lline, cLine& rline){        
    lline.id=-2;
    return lline+=rline;
}

void cLine::init(cEquation &equation,int id, int dimension,int systemSize){
    this->id=id;
    this->equation.copyFrom(equation);
    multipliers.resize(systemSize);
}
std::string cLine::toString(){
    std::string result;
    result="eq";
    result+=std::to_string(id)+":";
    if(outputFormat==2)
        result+="&&"; //for TEX only
    result+=equation.toString()+"|";
    if(outputFormat==2)
        result+="&";  //for TEX only
    /*if(multipliers.size()!=0)
        result+=multipliers[0].toString();   */
    for(int j=0;j<multipliers.size();j++){
        if(j!=0)
            result+=";";
        result+=multipliers[j].toString();                
    }
    result+=";";
    return result;
}
cLine cLine::operator*=(const cMonome& mon){        
    equation*=mon;
    for(int i=0;i<multipliers.size();i++)
        multipliers[i]*=mon;
    removeRedundantTerms();
    updateHighest();
    return *this;
}
cLine cLine::operator+=(const cLine& rline){  
    equation+=rline.equation;    
    for(int i=0;i<multipliers.size();i++)
        multipliers[i]+=rline.multipliers[i];        
    removeRedundantTerms();
    updateHighest();
    return *this;
}    
//стоп, этих двух функций вообще не должно быть...
void cLine::removeRedundantTerms(){
    equation.removeRedundantTerms();
    for(int j=0;j<multipliers.size();j++)
        multipliers[j].removeRedundantTerms();
}
void cLine::updateHighest(){
    equation.updateHighest();
    for(int j=0;j<multipliers.size();j++)
        multipliers[j].updateHighest();
}