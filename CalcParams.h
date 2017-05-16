//
// Created by tekla on 2017.04.26..
//

#ifndef LASTEST_CALCPARAMS_H
#define LASTEST_CALCPARAMS_H

#include <iostream>
#include <vector>
#include <string>
#include <liblas/liblas.hpp>
#include "LasPoint.h"
#include "LandCoverParams.h"

using namespace std;

class CalcParams {

public:

    void calcCSMs(vector<LasPoint>& points, LandCoverParams& param);
    void calcTMs(vector<LasPoint>& points, LandCoverParams& param);
    void calcVHMs(LandCoverParams& param);
    void calcIMs(vector<LasPoint>& points, LandCoverParams& param);
    void calcIDMs(vector<LasPoint>& points, LandCoverParams& param);
    void calcSkMs(vector<LasPoint>& points, LandCoverParams& param);
    void calcKrMs(vector<LasPoint>& points, LandCoverParams& param);
    void calcSkMcs(vector<LasPoint>& points, LandCoverParams& param);
    void calcKrMcs(vector<LasPoint>& points, LandCoverParams& param);
    void calcPCMs(vector<LasPoint>& points, LandCoverParams& param);
    void calcClassDef(vector<LasPoint>& points, LandCoverParams& param);
};


#endif //LASTEST_CALCPARAMS_H
