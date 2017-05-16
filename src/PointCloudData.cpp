//
// Created by tekla on 2017.04.25..
//

#include "PointCloudData.h"

PointCloudData::PointCloudData(const string &fileName) : fileName(fileName), retVal(false), idx_actual(0), fileNameModel("lidar_models.txt"), fileNameClasses("lidar_classes.txt")
{
    ReadWriteData reader;
    reader.readDefData(fileName, fileNameModel, fileNameClasses, pointNum, minX,maxX, minY, maxY, minZ, maxZ);

    for(auto row = 0; row <= (uint)(maxX-minX)/5; row++)
    {
        for(auto col = 0; col <= (uint)(maxY-minY)/5; col++)
        {
            isLoaded.insert(pair<pair<uint,uint>, pair<bool, uint>>(make_pair(row,col), make_pair(false, 0)));
        }
    }

    if (pointNum > READ_MAX)
    {
        idx_max = READ_MAX;
    }
    else
    {
        idx_max = (int)pointNum;
    }
}

void PointCloudData::searchActualPoints(uint x, uint y)
{
    actualPoints.clear();

    std::pair< map<pair<uint,uint>, LasPoint> :: iterator , map<pair<uint,uint>, LasPoint> :: iterator > range = points.equal_range(make_pair(x,y));
    for (auto it = range.first; it != range.second; ++it)
    {
        actualPoints.push_back(it->second);
    }
}

bool PointCloudData::processPoints()
{
    cout <<  endl << "********************** Process lidar points **********************" << endl << endl;
    while ( idx_actual < pointNum )
    {
        if (readPoints()) {
            preprocPoints();
            calcParams();
            classify();
            saveModel();
            saveClass();
            resetPointNum();
            actualPoints.clear();
            points.clear();
            params.clear();

            cout << idx_actual << endl;
        }
        else
        {
            idx_actual = pointNum;
        }
    }
    cout << "******************** Processing done! ********************" << endl;
}



bool PointCloudData::readPoints()
{
    ReadWriteData reader;
    retVal = reader.readData(fileName, points, idx_actual, idx_max, isLoaded);
    cout << " -- " << idx_actual << " points loaded" << endl;
    if( READ_MAX > (pointNum-idx_actual))
    {
        idx_max = READ_MAX;
    }
    else
    {
        idx_max += READ_MAX;
    }
    return retVal;
}


void PointCloudData::preprocPoints()
{
    for (map<pair<uint,uint>, pair<bool, uint>>::iterator it=isLoaded.begin(); it!=isLoaded.end(); ++it)
    {
        if ( it->second.first && it->second.second < MIN_POINT_PER_RAST  && it->second.second > 0)
        {
            uint x = it->first.first;
            uint y = it->first.second;
            points.erase(make_pair(x,y));
            it->second.first = false;
            it->second.second = 0;
        }
    }
}

void PointCloudData::calcParams()
{
    cout <<  endl << "Create surface models..." << endl;

    for (map<pair<uint,uint>, pair<bool, uint>>::iterator it=isLoaded.begin(); it!=isLoaded.end(); ++it)
    {
        if ( it->second.first && it->second.second > MIN_POINT_PER_RAST )
        {
            uint x = it->first.first;
            uint y = it->first.second;
            searchActualPoints(x,y);
            LandCoverParams tempParam;
            CalcParams calc;
            calc.calcCSMs(actualPoints, tempParam);
            calc.calcTMs(actualPoints, tempParam);
            calc.calcVHMs(tempParam);
            calc.calcIMs(actualPoints, tempParam);
            calc.calcIDMs(actualPoints, tempParam);
            calc.calcSkMs(actualPoints, tempParam);
            calc.calcKrMs(actualPoints, tempParam);
            calc.calcSkMcs(actualPoints, tempParam);
            calc.calcKrMcs(actualPoints, tempParam);
            calc.calcPCMs(actualPoints, tempParam);
            calc.calcClassDef(actualPoints, tempParam);
            params.insert(pair<pair<uint,uint>,LandCoverParams>(make_pair(x,y), tempParam));
        }
    }
    cout << "Done!" << endl;
}

void PointCloudData::classify()
{
    cout <<  endl << "Classify data..." << endl;

    for (map<pair<uint,uint>,LandCoverParams>::iterator it=params.begin(); it!=params.end(); ++it)
    {
        it->second.calcAlg1();
        it->second.calcAlg2();
    }
    cout << "Done!" << endl;
}

void PointCloudData::resetPointNum()
{
    for (map<pair<uint,uint>, pair<bool, uint>>::iterator it=isLoaded.begin(); it!=isLoaded.end(); ++it)
    {
        it->second.second = 0;
    }
}


void PointCloudData::saveModel()
{
    cout <<  endl << "Save surface models..." << endl;
    ReadWriteData writer;
    retVal = writer.writeModelData(fileNameModel, params);
    if (retVal)
    {
        cout << "Done!" << endl;
    }
    else
    {
        cerr << "Error : Cannot save the surface model!" << endl;
    }
}


void PointCloudData::saveClass()
{
    cout <<  endl << "Save classification data..." << endl;

    ReadWriteData writer;
    retVal = writer.writeClassData(fileNameClasses, params);

    if (retVal)
    {
        cout << "Done!" << endl;
    }
    else
    {
        cerr << "Error : Cannot save new classification data!" << endl;
    }
}

void PointCloudData::showMaps(int clNum )
{
    string fileName = fileNameClasses;
    ClassMap maps(fileName);

    if (CLASS_ALL == clNum)
    {
        maps.show(CLASS_DEF);
        maps.show(CLASS_ALG1);
        maps.show(CLASS_ALG2);
    }
    else
    {
        maps.show(clNum);
    }
}

bool PointCloudData::classFromModFile()
{
    cout <<  endl << "********************** Read and classify lidar points **********************" << endl << endl;
    ReadWriteData loader;
    retVal = loader.readModelData(fileNameModel, params);
    if (retVal)
    {
        for (map<pair<uint, uint>, LandCoverParams>::iterator it = params.begin(); it != params.end(); ++it) {
            it->second.calcAlg1();
            it->second.calcAlg2();
        }
        saveClass();
        cout << endl << "********************** Processing done! **********************" << endl << endl;
    }
    else
    {
        cerr << "Error : Cannot read model data" << endl;
    }
}

