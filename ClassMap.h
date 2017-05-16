//
// Created by tekla on 2017.05.05..
//

#ifndef LASTEST_CLASSMAP_H
#define LASTEST_CLASSMAP_H

#include <stdio.h>
#include "LandCoverParams.h"
#include "ReadWriteData.h"
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#define CLASS_DEF 0
#define CLASS_ALG1 1
#define CLASS_ALG2 2
#define CLASS_ALL 3
#define CLASS_DEF_S "0"
#define CLASS_ALG1_S "1"
#define CLASS_ALG2_S "2"
class ClassMap {
private:
    string fileName;
    int sizeX, sizeY;
    Mat imgSrc;
    Mat imgAlg1;
    Mat imgAlg2;
    vector<uint> defCls, alg1Cls, alg2Cls;
    void setColorDef(int def, Vec3b& tmpColor);
    void setColorAlg(int clas, Vec3b& tmpColor, int alg);
public:
    ClassMap() = default;
    ClassMap(string& fileName);
    void show(int clNum);
    ClassMap operator=(const ClassMap& map);
};


#endif //LASTEST_CLASSMAP_H
