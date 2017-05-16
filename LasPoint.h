//
// Created by tekla on 2017.04.25..
//

#ifndef LASTEST_LASPOINT_H
#define LASTEST_LASPOINT_H

#include <string>
#include <zconf.h>
#include <liblas/liblas.hpp>

using namespace std;
using namespace liblas;

class LasPoint {
private:
    double x, y, z;
    uint intensity,
        retNum,
        allRet,
        clsNum,
        alg1,
        alg2;
    string clsName;

public:

    uint getAlg1() const;

    void setAlg1(uint alg1);

    uint getAlg2() const;

    void setAlg2(uint alg2);

    LasPoint(double x, double y, double z, uint intensity, uint retNum, uint allRet, Classification classInfo);

    virtual ~LasPoint();

    double getX() const;

    void setX(double x);

    double getY() const;

    void setY(double y);

    double getZ() const;

    void setZ(double z);

    uint getIntensity() const;

    void setIntensity(uint intensity);

    uint getRetNum() const;

    void setRetNum(uint retNum);

    uint getAllRet() const;

    void setAllRet(uint allRet);

    uint getClsNum() const;

    void setClsNum(uint clsNum);

    const string &getClsName() const;

    void setClsName(const string &clsName);

};


#endif //LASTEST_LASPOINT_H
