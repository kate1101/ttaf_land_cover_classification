//
// Created by tekla on 2017.04.26..
//

#ifndef LASTEST_READWRITEDATA_H
#define LASTEST_READWRITEDATA_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "LasPoint.h"
#include "LandCoverParams.h"

#define READ_MAX 1000000

class ReadWriteData {
private:
    bool retVal;
public:
    bool readDefData(const string& fileName, const string& fileNameModel, const string& fileNameClasses, long long int& pointNum, double& minX,double& maxX,double& minY,double& maxY,double& minZ,double& maxZ);
    bool readData(const string& fileName, multimap<pair<uint,uint>, LasPoint>& points, int& idx_actual , const int idx_max, map<pair<uint,uint>, pair<bool, uint>>& isLoaded);
    bool writeModelData(const string& fileName, map<pair<uint,uint>, LandCoverParams>& params);
    bool writeClassData(const string& fileName, map<pair<uint,uint>, LandCoverParams>& params);
    bool writeClassStat(const string& fileNameStat, vector<uint>& defCls, vector<uint>& alg1Cls, vector<uint>& alg2Cls);
    bool readModelData(const string& fileName, map<pair<uint,uint>, LandCoverParams>& params);
};


#endif //LASTEST_READWRITEDATA_H
