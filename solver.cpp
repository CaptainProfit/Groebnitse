#include "solver.hpp"
#include <cmath> 

extern cLine operator*(cLine line, const cMonome& mon);
extern cLine operator+(cLine lline, cLine& rline);
extern int gcd(const int & a,const int &  b);
extern cMonome gcd(cMonome &a, cMonome &b); //extern ?


std::pair<cMonome,cMonome> cSolver::calcCoefs(cMonome &mon1, cMonome &mon2, bool &isMixInteresting){
    std::pair<cMonome,cMonome> result(cMonome(mon1.dim),cMonome(mon2.dim));
    cMonome mgcd(gcd(mon1,mon2));
    if(mgcd.isConstant())
        isMixInteresting=false;
    else 
        isMixInteresting=true;
    if(mgcd.coef ==0){
        std::cout<<"ошибка, НОД = 0"<<std::endl;
    }
    result.first.coef=mon2.coef/mgcd.coef;
    result.second.coef=-mon1.coef/mgcd.coef;
    if(mon1.dim!=mon2.dim){
        std::cout<<"something going wrong in solver::calcCoefs"<<std::endl;
    }
    for(int i=0;i<mon1.dim;i++){
        result.first.power[i]=mon2.power[i]-mgcd.power[i];
        result.second.power[i]=mon1.power[i]-mgcd.power[i];
    }
    return result;
}
void check(cMonome &a, cMonome &b){
    if( (a.power.size()!=b.power.size()) 
        ||(a.power.size()==0)
        ||(a.dim!=b.dim)
        ||(a.dim!=a.power.size())
    ){
        std::cout<<"DAMN IT!"<<std::endl;        
    }
}
bool cSolver::mixLines(int i, int j){
    bool isMixInteresting = false;
    
    //1) строю множители.
    // std::cout<<"mixing lines:"<<std::endl;
    lines[i].equation.updateHighest();
    lines[j].equation.updateHighest();
    check(*lines[i].equation.highestTerm,*lines[j].equation.highestTerm);
    std::pair<cMonome,cMonome> muls=calcCoefs(*lines[i].equation.highestTerm,*lines[j].equation.highestTerm, isMixInteresting);
    //1.2)проверяю, что зацепление присутствует, иначе не имеет смысла проверять эту смесь.
    //gcd(lines[i].equation.highestTerm->power, lines[j].equation.highestTerm->power).isConstant() <=> нет
    if(!isMixInteresting){
        return false;
    }
    cLine mix((lines[i]*muls.first)+(lines[j]*muls.second));
    mix.id=systemSize+1;
    mix.removeRedundantTerms();
    mix.updateHighest();
    //std::cout<<mix.toString()<<std::endl;

    //2) редукция
    //std::cout<<"reduce mix:"<<std::endl;
    for(int k=0;(k<systemSize)&&(mix.equation.nonZero());k++){
        mix.updateHighest();
        lines[k].equation.updateHighest();
        cMonome h = *(lines[k].equation.highestTerm);
        check(*mix.equation.highestTerm,h);
        std::pair<cMonome,cMonome> muls=calcCoefs(*mix.equation.highestTerm,h);
        //std::cout<<k<<":{"<<muls.first.toString() <<","<<muls.second.toString() <<"}"<<std::endl;        
        if(muls.first.isConstant()){
            //muls.first must be == coef only 
            //std::cout<<"reducing"<<std::endl;
            mix*=muls.first;
            cLine b(lines[k]*muls.second);
            mix+= b;
            k=-1;            
            //std::cout<<mix.id<<"<-"<<(k+1)<<"::"<<mix.toString()<<std::endl;
            //std::cout<<mix.toString()<<std::endl;
        }
    }    
    //std::cout<<mix.toString()<<std::endl;

    //3) нормализация

    //std::cout<<"normalize mix:"<<std::endl;
    //то же самое, но теперь смотрим и редуцируем все термы микса, не только высший.
    for(int k=0;k<systemSize;k++){
            cMonome h = *(lines[k].equation.highestTerm);
        for(std::list<cMonome>::iterator it=mix.equation.terms.begin();it!=mix.equation.terms.end();it++){            
            check(*it,h);
            std::pair<cMonome,cMonome> muls=calcCoefs(*it,h);
            if(muls.first.isConstant()){
                //muls.first must be == coef only 
                mix*=muls.first;
                cLine b(lines[k]*muls.second);
                mix+= b;
                //snova po novoi;
                k=-1;
                break;
            }
        }
    }
    //std::cout<<mix.toString()<<std::endl; 
    
    //4) если не ноль - дописываю в систему.   
    mix.removeRedundantTerms();
    mix.updateHighest();
    if(mix.equation.nonZero()){
        mix.removeRedundantTerms();
        lines.push_back(mix);
        systemSize++;
        lines[systemSize-1].updateHighest();
        //новые не нужны. 
        /*for(int i=0;i<systemSize;i++){
            lines[i].multipliers.push_back(cEquation());
            lines[i].multipliers[systemSize-1].updateHighest();
        }*/
        return true;
    }
    //std::cout<<mix.toString()<<std::endl;
    return false;
}