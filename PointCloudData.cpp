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
    while ( idx_actual < pointNum ) //while all points processed
    {
        readPoints();       //read max 1m point
        preprocPoints();    //delete spaces with to few points
        calcParams();       //calculate parameters
        classify();       //classify data
        saveModel();      //save model params
        saveClass();      //save class prams

        //saveDefToLAZ();
        //saveAlgsToLAZ();

        resetPointNum();    //0 all pointnum into isLoaded
        actualPoints.clear();
        points.clear();
        params.clear();

        cout << idx_actual << endl;
    }
    cout << "******************** Processing done! ********************" << endl;
}



bool PointCloudData::readPoints()
{//Read .las/.laz file
    ReadWriteData reader;
    reader.readData(fileName, points, idx_actual, idx_max, isLoaded);
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
        uint x = it->first.first;
        uint y = it->first.second;
        std::pair< map<pair<uint,uint>, LasPoint> :: iterator , map<pair<uint,uint>, LasPoint> :: iterator > range = points.equal_range(make_pair(x,y));
        for (auto it2 = range.first; it2 != range.second; ++it2)
        {
            it2->second.setAlg1((uint) it->second.getClassAlg1());
            it2->second.setAlg2((uint) it->second.getClassAlg2());
        }
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


bool PointCloudData::saveModel()
{
    cout <<  endl << "Save surface models..." << endl;
    ReadWriteData writer;
    retVal = writer.writeModelData(fileNameModel, params);
    if (retVal) cout << "Done!" << endl;
    else  cerr << "Error : Cannot save the surface model!" << endl;
    return retVal;
}


bool PointCloudData::saveClass() // modify lidarfile to classification ?
{
    cout <<  endl << "Save classification data..." << endl;
    ReadWriteData writer;
    retVal = writer.writeClassData(fileNameClasses, params);
    if (retVal) cout << "Done!" << endl;
    else cerr << "Error : Cannot save new classification data!" << endl;
    return retVal;
}

bool PointCloudData::showMaps(int clNum )
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
    loader.readModelData(fileNameModel, params);
    for (map<pair<uint,uint>,LandCoverParams>::iterator it=params.begin(); it!=params.end(); ++it)
    {
        it->second.calcAlg1();
        it->second.calcAlg2();
    }
    saveClass();
    cout <<  endl << "********************** Processing done! **********************" << endl << endl;
}

/*
bool PointCloudData::saveDefToLAZ() {

    cout <<  endl << "Save default class data to .laz file..." << endl;
    ReadWriteData writer;
    string defName = fileName.substr(0,fileName.size() - 4);
    defName += "_def.laz";
    retVal = writer.writeClassDefault(fileName, defName, points);
    if (retVal) cout << "Done!" << endl;
    else cerr << "Cannot save the default classes to laz file" << endl;
    return retVal;
}

int PointCloudData::saveAlgsToLAZ() {

    cout <<  endl << "Save alg1 and alg2 data to .laz file..." << endl;
    ReadWriteData writer;
    string alg1Name = fileName.substr(0,fileName.size() - 4);
    string alg2Name = alg1Name;
    alg1Name += "_alg1.laz";
    alg2Name += "_alg2.laz";
    int retNum = 0;
    retVal = writer.writeClassAlg(fileName, alg1Name, points, true);
    if (retVal) retNum++;
    retVal = writer.writeClassAlg(fileName, alg2Name, points, false);
    if (retVal) retNum+=2;
    switch (retNum)
    {
        case 0:
            cout << "Done!" << endl;
            break;
        case 1:
            cerr << "Error : Cannot save the alg1 classes to laz file" << endl;
            break;
        case 2:
            cerr << "Error : Cannot save the alg2 classes to laz file" << endl;
            break;
        case 3:
            cerr << "Error : Cannot save the alg1 and alg 2 classes to laz file" << endl;
            break;
        default:
            cerr << "Error : Invalid return" << endl;
            break;
    }
    return retNum;
}

 */

