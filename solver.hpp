#include "alsystem.hpp"
#pragma once

class cSolver: public cSystem{
    public:
    //для класса "cLine" не существует конструктор по умолчанию
    //cLine acc;
    cSolver(cSystem sys):cSystem(sys){};
    std::pair<cMonome,cMonome> calcCoefs(cMonome &mon1, cMonome &mon2){
        bool flagStub;
        return calcCoefs(mon1, mon2, flagStub);
    }
    std::pair<cMonome,cMonome> calcCoefs(cMonome &mon1, cMonome &mon2, bool &isMixInteresting);
    bool mixLines(int i, int j);

    /*bool decideCandidate();
    void simplifyCandidate(cLine &line);
    void reduceBy(cSystem sys);*/
};