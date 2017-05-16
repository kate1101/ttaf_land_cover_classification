//
// Created by tekla on 2017.04.26..
//

#include "CalcParams.h"

void  CalcParams::calcCSMs(vector<LasPoint>& points, LandCoverParams& param)
{
    param.setCSM(points[0].getZ());

    for (const auto& point : points)
    {
        if( param.getCSM() < point.getZ())
        {
            param.setCSM(point.getZ());
        }
    }
}

void  CalcParams::calcTMs(vector<LasPoint>& points, LandCoverParams& param)
{
    param.setTM(points[0].getZ());

    for (const auto& point : points)
    {
        if( param.getTM() > point.getZ() )
        {
            param.setTM(point.getZ());
        }
    }
}

void  CalcParams::calcVHMs( LandCoverParams& param)
{
    param.setVHM( param.getCSM() - param.getTM() );
}

void  CalcParams::calcIMs(vector<LasPoint>& points,LandCoverParams& param)
{
    int sumIntVal = 0, allPoints = 0;

    for (const auto& point : points)
    {
        if( point.getRetNum() == 1)
        {
            allPoints++;
            sumIntVal += point.getIntensity();
        }

        if ( point.getRetNum() == point.getAllRet())
        {
            allPoints++;
            sumIntVal += point.getIntensity();
        }
    }

    if (allPoints > 0 )
    {
        param.setIM( double(sumIntVal / allPoints));
    }
    else
    {
        param.setIM( -1 );
    }

}


void  CalcParams::calcIDMs(vector<LasPoint>& points, LandCoverParams& param)
{
    int minInt = 1000, maxInt = 0;

    for (const auto& point : points)
    {
        if( minInt > point.getIntensity() && point.getRetNum() == point.getAllRet())
        {
            minInt = point.getIntensity();
        }

        if( maxInt < point.getIntensity() && point.getRetNum() == 1)
        {
            maxInt = point.getIntensity();
        }
    }
    if( maxInt - minInt < 0)
    {
        param.setIDM(-1);
    }
    else
    {
        param.setIDM( maxInt - minInt );
    }

}


void  CalcParams::calcSkMs(vector<LasPoint>& points, LandCoverParams& param)
{
    long double pow2sum = 0, pow3sum = 0;
    unsigned long pointNum = points.size();
    long double zsum = 0;

    param.setSkM(-100);

    for (const auto& point : points)
    {
        zsum += point.getZ();
    }

    if (pointNum > 0)
    {
        zsum /= (double)pointNum;

        for (const auto &point : points) {
            pow3sum += pow(point.getZ() - zsum, 3.0);
            pow2sum += pow(point.getZ() - zsum, 2.0);
        }

        pow3sum /= (double)pointNum;
        pow2sum /= (double)pointNum;

        if (pow2sum > 0) {
            double sk = (double) (pow3sum / pow(sqrt(pow2sum), 3.0));
            param.setSkM(sk);
        }
    }
}


void  CalcParams::calcKrMs(vector<LasPoint>& points, LandCoverParams& param)
{
    long double pow2sum = 0, pow4sum = 0;
    unsigned long pointNum = points.size();
    long double zsum = 0;

    param.setKrM(100);

    for (const auto &point : points) {
        zsum += point.getZ();
    }

    if (pointNum > 0) {
        zsum /= (double)pointNum;

        for (const auto &point : points) {
            pow4sum += pow(point.getZ() - zsum, 4.0);
            pow2sum += pow(point.getZ() - zsum, 2.0);
        }

        pow4sum /= (double)pointNum;
        pow2sum /= (double)pointNum;

        if (pow2sum > 0) {
            double sk = (double) (pow4sum / pow(pow2sum, 2.0));
            param.setKrM(sk);
        }
    }
}


void  CalcParams::calcSkMcs(vector<LasPoint>& points, LandCoverParams& param)
{
    double  sk = param.getSkM();
    unsigned long size = points.size();
    sk = (sqrt(size*(size-1)) / (double)(size-2)) * sk;
    param.setSkMc(sk);
}


void  CalcParams::calcKrMcs(vector<LasPoint>& points, LandCoverParams& param)
{
    double  kr = param.getKrM() + 3;
    unsigned long size = points.size();
    kr = ((size -1)/(double)((size-2)*(size-3))) * ((size+1)*kr - 3*(size-1));
    param.setKrMc(kr);
}


void  CalcParams::calcPCMs(vector<LasPoint>& points, LandCoverParams& param)
{
    int canopyPoints = 0;
    unsigned long allPoints = points.size();
    param.setPCM(-1);

    for (const auto& point : points)
    {
        if(point.getRetNum() == 1 && point.getAllRet() != 1)
        {
            canopyPoints++;
        }
    }

    if (allPoints > 0)
    {
        param.setPCM((canopyPoints/(double)allPoints));
    }
}

void CalcParams::calcClassDef(vector<LasPoint> &points, LandCoverParams &param)
{
    vector<uint> cls;

    for(const auto& point : points)
    {
        cls.push_back(point.getClsNum());
    }

    sort(cls.begin(), cls.end());
    param.setClassDef((int)cls[cls.size()/2]);
}
