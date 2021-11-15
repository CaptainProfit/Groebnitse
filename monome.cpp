#include "monome.hpp"

int gcd(const int & a,const int &  b){
    return b==0?a:gcd(b,a%b);
}
cMonome gcd(cMonome &a, cMonome &b){
    if(a.dim!=b.dim){
        std::cout<<"something going wrong in calcCoefs"<<std::endl;
    }
    if((a.power.size()!=b.power.size()) ||(a.power.size()==0)){
        std::cout<<"DAMN this"<<std::endl;
        return a;
    }
    cMonome result(a.dim);
    result.coef=gcd(std::abs(a.coef),std::abs(b.coef));
    for(int i=0;i<a.dim;i++){
        result.power[i]=(a.power[i]>b.power[i])?b.power[i]:a.power[i];
    }
    return result;
}

cMonome::cMonome(int newDim){
    //std::cout<<"cMonome+"<<std::endl;
    dim=newDim;
    power.resize(dim);
    coef=0;
    for(int i=0;i<dim;i++){
        power[i]=0;
    }
}

cMonome & cMonome::operator*=(const int &that){
    coef*=that;
    return *this;
}
cMonome & cMonome::operator*=(const cMonome &that){
    if(dim==that.dim){
        coef*=that.coef;
        for(int i=0;i<dim;i++){
            power[i]+=that.power[i];
        }
    }
    else
        std::cout<<"something wrong while monome multiplication - not matched dimensions"<<std::endl;
    return *this;
}
cMonome & cMonome::operator+=(const cMonome &that){
    if((dim==that.dim)&&(this->compareWith(that)==eEqual)){
        coef+=that.coef;        
    }
    else{
        std::cout<<"something wrong while monome addition"<<std::endl;
        std::cout<<"dimensions:"<<dim<<" "<<that.dim<<std::endl;
        std::cout<<"powers are"<<compareWith(that)<<std::endl;
    }    
    return *this;
}

bool operator==(const cMonome& mon1,const cMonome& mon2){
    if(monomeOrder(mon1.power,mon2.power)==eEqual)
        return true;
    return false;
}
bool operator>(const cMonome& mon1,const cMonome& mon2){
    if(monomeOrder(mon1.power,mon2.power)==eBigger)
        return true;    
    return false;
}
bool operator<(const cMonome& mon1,const cMonome& mon2){
    if(monomeOrder(mon1.power,mon2.power)==eLess)
        return true;    
    return false;
}
std::string cMonome::toString( bool isSigned){
    std::string result;
    result="";
    int acoef=std::abs(coef);
    //1)if zero not used, but present
    if(coef==0)
        return "0";
    //2)sign
    if(isSigned){
        if(coef>0)
            result+="+";
        else
            result+="-";
    }
    //3)if constant
    if(isConstant()){
        result+=std::to_string(acoef);
        return result;
    }    
    //3)not constant now, not unity coef
    if(acoef!=1){
        result+=std::to_string(acoef);
        if(outputFormat==1)
            result+="*";
    }
    //4)power
    bool isPrevious=false;
    for(int i=0;i<dim;i++){
        if(power[i]!=0){
            //isPlaceOperand
            if(isPrevious&&(outputFormat==1)){
                result+="*";
                
            }
            isPrevious=true;
            result+=var(i); 
            if(power[i]!=1){
                if((power[i]>=10) && (outputFormat==2)){
                    result+="^{"+std::to_string(power[i])+"}";
                }
                else 
                    result+="^"+std::to_string(power[i]);
            }
        }
    }
    return result;
}