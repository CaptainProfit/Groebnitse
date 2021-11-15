#include <iostream>
#include "solver.hpp"
int outputFormat = 0;
//0-output "for" human
//1-output for matlab
//2-output for tex

int main(){
    cEquation f1,f2,x3,y3,z3;
    cMonome a(_dim),b(_dim),c(_dim),ex(_dim),ey(_dim),ez(_dim);
    //1) monome created, equation created.
    a.coef=1;
    b.coef=1;
    c.coef=1;
    a.power[0]=1;
    b.power[1]=1;
    c.power[2]=1;
    f1+=a;
    f1+=b;
    f1+=c;
    a.power[0]=2;
    b.power[1]=2;
    c.power[2]=2;
    f2+=a;
    f2+=b;
    f2+=c;
    a.power[0]=3;
    b.power[1]=3;
    c.power[2]=3;
    /*ex.coef=2;
    ey.coef=3;
    ez.coef=5;*/
    ex.coef=-1;
    ey.coef=-1;
    ez.coef=-1;
    ex.power[3]=1;
    ey.power[4]=1;
    ez.power[5]=1;
    x3+=a;
    x3+=ex;
    y3+=b;
    y3+=ey;
    z3+=c;
    z3+=ez;
    //2) equation list done, system initialized, solver initialized.
    //std::vector<cEquation> initList({f1,f2,x3,y3,z3});
    std::list<cEquation> initList({f1,x3,y3,z3});
    //std::cout<<"end of equations"<<std::endl;
    cSystem system(initList,_dim);
    cSolver solver(system);
    std::vector<std::string> initialSystemString(solver.toString());
    for(int i=0;i<system.initialSystemSize;i++){
        std::cout<<initialSystemString[i]<<std::endl;
    }
    std::cout<<"-------"<<std::endl;
    
    //3) solver gonna mix
    bool isChangedInCycle=true;
    std::vector<std::vector<bool>> checkIn(solver.systemSize,std::vector<bool>(solver.systemSize,true));

    for(int t=0;(t<100)&&(isChangedInCycle);t++){
        isChangedInCycle=false;//reset
        int oldsize=solver.systemSize;
        int i=0;
        int j=1;
        for(int i=0;i<oldsize;i++){
            for(int j=i+1;j<oldsize;j++){
                if(checkIn[i][j]){
                    checkIn[i][j]=false;
                    bool isMixedLineInteresting=solver.mixLines(i,j);
                    isChangedInCycle|=isMixedLineInteresting;
                    if(isMixedLineInteresting){
                        //std::cout<<solver.lines[solver.lines.size()-1].toString()<<std::endl;
                        std::cout<<"eq"<< solver.systemSize <<"~="<<"N(R("<<"eq"<<i+1<<"—"<<"eq"<<j+1<<"))"<<std::endl;
                        for(int k=0;k<checkIn.size();k++)
                            checkIn[k].push_back(true);
                        checkIn.push_back(std::vector<bool>(true,solver.systemSize));
                    }
                }
            }
        } 
        /*for(int i=0;i<solver.systemSize;i++){
            std::cout<<solver.lines[i].toString()<<std::endl;
        }
        std::cout<<"-------"<<std::endl;*/
        if(t==99){
            std::cout<<"tries are out, system may be way too hard to continue"<<std::endl;
        }
    }
    std::cout<<"answer, Groebner basis: "<<std::endl;
    for(int i=0;i<solver.systemSize;i++){
        std::cout<<solver.lines[i].toString()<<std::endl;
    }
    std::cout<<"-------"<<std::endl;
    //3) solver gonna solve?
}