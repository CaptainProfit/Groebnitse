#include "monome.hpp"

eCompare lexOrder(const std::vector<int> &pow1, const std::vector<int> &pow2);
eCompare grLexOrder(const std::vector<int> &pow1, const std::vector<int> &pow2);
//здесь подставить нужный порядок.
eCompare monomeOrder(const std::vector<int> &pow1, const std::vector<int> &pow2){
    return lexOrder(pow1,pow2); 
}

//здесь настроить название переменных.
char cMonome::var(int i){
    switch(i){
        case 0: return 'x';
        case 1: return 'y';
        case 2: return 'z';
        case 3: return 'a';
        case 4: return 'b';
        case 5: return 'c';
        default:return 't';
    }
}
//здесь различные порядки
//лексикографический порядок
eCompare lexOrder(const std::vector<int> &pow1, const std::vector<int> &pow2){
    //x>>y>>z>>a>>b>>c...
    for(int i=0;(i<pow1.size())&&(i<pow2.size());i++){
        if(pow1[i]>pow2[i])
            return eBigger;
        if(pow1[i]<pow2[i])
            return eLess;
    }
    if(pow1.size()>pow2.size()){
        for(int i=0;i<pow1.size();i++)
            if(pow1[i]>0)
                return eBigger;
    }
    if(pow1.size()<pow2.size()){
        for(int i=0;i<pow2.size();i++)
            if(pow2[i]>0)
                return eLess;
    }        
    return eEqual;
}

//Степенно-словарный порядок
eCompare grLexOrder(const std::vector<int> &pow1, const std::vector<int> &pow2){
    //summary power
        // x>>y>>z>>a>>b>>c...
    int sum1=0,sum2=0;
    for(int i=0;i<pow1.size();i++)
        sum1+=pow1[i];
    for(int i=0;i<pow2.size();i++)
        sum2+=pow2[i];
    if(sum1>sum2)
        return eBigger;
    if(sum1<sum2)
        return eLess;
    return lexOrder(pow1,pow2);
}