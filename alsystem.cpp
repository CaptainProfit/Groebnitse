#include "alsystem.hpp"
//extern cLine operator*(cLine line, const cMonome& mon);
cEquation operator+(cEquation leq, cEquation& req){        
    return leq+=req;
}
cEquation operator*(cEquation leq, cEquation& req){        
    return leq*=req;
}
cEquation operator+(cEquation leq, cMonome& rmon){        
    return leq+=rmon;
}
cEquation operator*(cEquation leq, cMonome& rmon){        
    return leq*=rmon;
}

cSystem::cSystem(std::list<cEquation> &startList,int dim){
    dimension=dim;
    initialSystemSize=startList.size();
    systemSize=initialSystemSize;
    lines.resize(startList.size());
    int id=0;
    for(std::list<cEquation>::iterator it=startList.begin();it!=startList.end();it++){
        lines[id].init(*it, id+1, dimension,initialSystemSize);
        id++;
    }
    
    mUnitConstant.coef=1;
    mUnitConstant.dim=dimension;
    mUnitConstant.power.resize(dimension);
    for(int i=0;i<mUnitConstant.dim;i++){
        mUnitConstant.power[i]=0;
    }
    for(int i=0;i<initialSystemSize;i++){
        lines[i].multipliers[i]+=(mUnitConstant);
    }

    for(int i=0;i<initialSystemSize;i++){
        for(int j=0;j<lines[i].multipliers.size();j++)
            lines[i].multipliers[j].updateHighest();
        lines[i].equation.updateHighest();
    }

    eUnitConstant+=mUnitConstant;
    std::cout<<"created system from list.\ndimension = "<<dimension<<std::endl;
    std::cout<<"size = "<<systemSize<<std::endl;
}