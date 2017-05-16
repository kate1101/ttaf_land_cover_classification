//
// Created by tekla on 2017.04.25..
//

#include "LasPoint.h"


LasPoint::LasPoint(double x, double y, double z,
                   uint intensity, uint retNum, uint allRet, Classification classInfo) :
         x(x), y(y),  z(z),
         intensity(intensity),
         retNum(retNum), allRet(allRet)
{
    clsNum = classInfo.GetClass();
    clsName = classInfo.GetClassName();
    //alg1 = 0;
    //alg2 = 0;
}

LasPoint::~LasPoint() {

}

double LasPoint::getX() const {
    return x;
}

void LasPoint::setX(double x) {
    LasPoint::x = x;
}

double LasPoint::getY() const {
    return y;
}

void LasPoint::setY(double y) {
    LasPoint::y = y;
}

double LasPoint::getZ() const {
    return z;
}

void LasPoint::setZ(double z) {
    LasPoint::z = z;
}

uint LasPoint::getIntensity() const {
    return intensity;
}

void LasPoint::setIntensity(uint intensity) {
    LasPoint::intensity = intensity;
}

uint LasPoint::getRetNum() const {
    return retNum;
}

void LasPoint::setRetNum(uint retNum) {
    LasPoint::retNum = retNum;
}

uint LasPoint::getAllRet() const {
    return allRet;
}

void LasPoint::setAllRet(uint allRet) {
    LasPoint::allRet = allRet;
}

uint LasPoint::getClsNum() const {
    return clsNum;
}

void LasPoint::setClsNum(uint clsNum) {
    LasPoint::clsNum = clsNum;
}

const string &LasPoint::getClsName() const {
    return clsName;
}

void LasPoint::setClsName(const string &clsName) {
    LasPoint::clsName = clsName;
}


