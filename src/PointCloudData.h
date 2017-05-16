//
// Created by tekla on 2017.04.25..
//

#ifndef LASTEST_POINTCLOUDDATA_H
#define LASTEST_POINTCLOUDDATA_H

#include "LasPoint.h"
#include "LandCoverParams.h"
#include "ReadWriteData.h"
#include "CalcParams.h"
#include "ClassMap.h"

#define MIN_POINT_PER_RAST 10

class PointCloudData {
private:

    const string fileName;
    const string fileNameModel;
    const string fileNameClasses;
    long long int pointNum;
    double minX, maxX, minY, maxY, minZ, maxZ;
    map<pair<uint,uint>, pair<bool, uint>> isLoaded;
    int idx_actual, idx_max;

    multimap<pair<uint,uint>, LasPoint> points;
    vector<LasPoint> actualPoints;

    map<pair<uint,uint>, LandCoverParams> params;
    bool retVal;

    void searchActualPoints(uint x, uint y);
    void resetPointNum();
    void preprocPoints();
    bool readPoints();
    void calcParams();
    void classify();
    void saveModel();
    void saveClass();

public:
    PointCloudData() : fileNameModel("lidar_models.txt"), fileNameClasses("lidar_classes.txt"){};
    PointCloudData(const string &fileName);
    void showMaps(int clNum);
    bool processPoints();
    bool classFromModFile();
};


#endif //LASTEST_POINT
// CLOUDDATA_H
