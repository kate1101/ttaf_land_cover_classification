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
    //coo.-s     rastX = (uint) ((x - minX) / 5);
    //           rastY = (uint) ((y - minY) / 5);

    const string fileName;                             //global point cloud info
    const string fileNameModel;
    const string fileNameClasses;
    long long int pointNum;                            //global point cloud info
    double minX, maxX, minY, maxY, minZ, maxZ;         //global point cloud info
    map<pair<uint,uint>, pair<bool, uint>> isLoaded;               //global point cloud info, true, when raster value is estimated
    int idx_actual , idx_max;

    multimap<pair<uint,uint>, LasPoint> points;        //<= 1m actual points reading sorted by coordinates - 0 < ui1 < (maxX-minX) / 5, 0 < ui2 < (maxY - minY) / 5
    vector<LasPoint> actualPoints;                     //actual points in a raster - max ~1000 points

    map<pair<uint,uint>, LandCoverParams> params;      //calculated data - key:coordinates - data:calculated params
    bool retVal;

    void searchActualPoints(uint x, uint y);
    void resetPointNum();
    void preprocPoints();

    bool readPoints();
    void calcParams();
    void classify();
    bool saveModel();
    bool saveClass();
/*
    bool setSizeParams();
    bool saveDefToLAZ();
    int  saveAlgsToLAZ();
*/

public:
    PointCloudData() : fileNameModel("lidar_models.txt"), fileNameClasses("lidar_classes.txt"){};
    PointCloudData(const string &fileName);
    bool showMaps(int clNum);
    bool processPoints();
    bool classFromModFile();
};


#endif //LASTEST_POINT
// CLOUDDATA_H
