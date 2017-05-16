//
// Created by tekla on 2017.04.25..
//

#include "LandCoverParams.h"
#include <algorithm>

double LandCoverParams::getCSM() const {
    return CSM;
}

void LandCoverParams::setCSM(double CSM) {
    LandCoverParams::CSM = CSM;
}

double LandCoverParams::getTM() const {
    return TM;
}

void LandCoverParams::setTM(double TM) {
    LandCoverParams::TM = TM;
}

double LandCoverParams::getVHM() const {
    return VHM;
}

void LandCoverParams::setVHM(double VHM) {
    LandCoverParams::VHM = VHM;
}

double LandCoverParams::getIM() const {
    return IM;
}

void LandCoverParams::setIM(double IM) {
    LandCoverParams::IM = IM;
}

double LandCoverParams::getIDM() const {
    return IDM;
}

void LandCoverParams::setIDM(double IDM) {
    LandCoverParams::IDM = IDM;
}

double LandCoverParams::getSkM() const {
    return SkM;
}

void LandCoverParams::setSkM(double SkM) {
    LandCoverParams::SkM = SkM;
}

double LandCoverParams::getKrM() const {
    return KrM;
}

void LandCoverParams::setKrM(double KrM) {
    LandCoverParams::KrM = KrM;
}

double LandCoverParams::getSkMc() const {
    return SkMc;
}

void LandCoverParams::setSkMc(double SkMc) {
    LandCoverParams::SkMc = SkMc;
}

double LandCoverParams::getKrMc() const {
    return KrMc;
}

void LandCoverParams::setKrMc(double KrMc) {
    LandCoverParams::KrMc = KrMc;
}

double LandCoverParams::getPCM() const {
    return PCM;
}

void LandCoverParams::setPCM(double PCM) {
    LandCoverParams::PCM = PCM;
}

void LandCoverParams::nearTerr(bool alg1) {
    if ( VHM < 0.5 && IM >= 55 &&
            IM < 75 && IDM < 30)
    {//Gravel
        if (alg1) classAlg1 = GRAVEL;
        else classAlg2 = GRAVEL;
    }
    else if(IM >= 90)
    {//Short Veg
        if (alg1) classAlg1 = SHORT_VEG;
        else classAlg2 = SHORT_VEG;
    }
    else if(IM < 90 && IM >= 75)
    {//Bare Earth
        if (alg1) classAlg1 = BARE_EARTH;
        else classAlg2 = BARE_EARTH;
    }
}

void LandCoverParams::planted(bool alg1) {
    if (VHM < 10)
    {//Young Planted
        if (alg1) classAlg1 = YOUNG_PLANTED_FOREST;
        else classAlg2 = YOUNG_PLANTED_FOREST;
    }
    else if ( VHM >= 10 && VHM < 18)
    {//Inter. Planted
        if (alg1) classAlg1 = INTER_PLANTED_FOREST;
        else classAlg2 = INTER_PLANTED_FOREST;
    }
    else
    {//Mature Planted
        if (alg1) classAlg1 = MATURE_PLANTED_FOREST;
        else classAlg2 = MATURE_PLANTED_FOREST;
    }
}

void LandCoverParams::natural(bool alg1) {
    if ( VHM >= 10)
    {//Mature Natural
        if (alg1) classAlg1 = MATURE_NAT_FOREST;
        else classAlg2 = MATURE_NAT_FOREST;
    }
    else
    {//Young  Natural
        if (alg1) classAlg1 = YOUNG_NAT_FOREST;
        else classAlg2 = YOUNG_NAT_FOREST;
    }
}

void LandCoverParams::calcAlg1()
{
    classAlg1 = OTHER;

    if (IM >= 0 && IM < 55 && VHM < 0.5)
    {//Water
        classAlg1 = WATER;
    }
    else if (VHM < 3.5)
    {//Near Terrain Features
        nearTerr(true);
    }
    else
    {//Tall Vegetation
        if(abs(SkM) >= 1.3 && abs(KrM) >= 1.7)
        {//Planted Forest
            planted(true);
        }
        else if (abs(SkM) < 1.3 && abs(KrM) < 1.7)
        {//Natural Forest
           natural(true);
        }
    }
}

void LandCoverParams::calcAlg2()
{
    classAlg2 = OTHER;

    if (IM >= 0 && IM < 55 && VHM < 0.5)
    {//Water
        classAlg2 = WATER;
    }
    else if (VHM < 3.5)
    {//Near Terrain Features
        nearTerr(false);
    }
    else
    {//Tall Vegetation
        if(abs(SkMc) >= 0.8 && abs(KrMc) >= 2.0 && PCM < 0.2 )
        {//Planted Forest
            planted(false);
        }
        else if (abs(SkMc) < 0.8 && abs(KrMc) < 2.0 && PCM >= 0.2)
        {//Natural Forest
            natural(false);
        }
    }
}

int LandCoverParams::getClassAlg1() const {
    return classAlg1;
}

int LandCoverParams::getClassAlg2() const {
    return classAlg2;
}

int LandCoverParams::getClassDef() const {
    return classDef;
}

void LandCoverParams::setClassDef(int classDef) {
    LandCoverParams::classDef = classDef;
}
