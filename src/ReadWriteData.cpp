//
// Created by tekla on 2017.04.26..
//

#include "ReadWriteData.h"

bool ReadWriteData::readDefData(const string &fileName, const string& fileNameModel, const string& fileNameClasses,
                                long long int &pointNum, double &minX, double &maxX, double &minY,
                                double &maxY, double &minZ, double &maxZ)
{
    try
    {
        ifstream ifs;
        ifs.open(fileName, ios::in | ios::binary);
        ReaderFactory f;
        Reader reader = f.CreateWithStream(ifs);
        Header const& header = reader.GetHeader();

        pointNum = header.GetPointRecordsCount();
        minX = header.GetMinX();
        maxX = header.GetMaxX();
        minY = header.GetMinY();
        maxY = header.GetMaxY();
        minZ = header.GetMinZ();
        maxZ = header.GetMaxZ();

        ofstream ofsMod(fileNameModel);
        if (ofsMod.is_open())
        {
            ofsMod << "Lidar pointcloud - Surface Models - Row data info: X, Y, CSM, TM, VHM, IM, IDM, SkM, KrM, SkMc, KrMc, PCM, Def" << endl;
            ofsMod.close();
        }

        ofstream ofsCls(fileNameClasses);
        if (ofsCls.is_open())
        {
            ofsCls << "Lidar pointcloud - Land Cover Classification - Row data info : X, Y, Def, Alg1, Alg2" << endl;
            ofsCls << "MaxXY " << (uint)((maxX-minX)/5)+1 << " " << (uint)((maxY-minY)/5)+1 << endl;
            ofsCls.close();
        }
        retVal = true;
    }
    catch (exception const &e)
    {
        cerr << "Error : " << e.what() << endl;
        retVal = false;
    }
    return retVal;

}

bool ReadWriteData::readData(const string &fileName, multimap<pair<uint, uint>, LasPoint> &points, int &idx_actual,
                             const int idx_max, map<pair<uint,uint>, pair<bool, uint>>& isLoaded)
{
    try
    {
        ifstream ifs;
        ifs.open(fileName, ios::in | ios::binary);
        ReaderFactory f;
        Reader reader = f.CreateWithStream(ifs);
        Header const& header = reader.GetHeader();
        double minX = header.GetMinX();
        double minY = header.GetMinY();

        points.clear();

        reader.Seek((size_t) idx_actual);
        while (reader.ReadNextPoint() && idx_actual!=idx_max)
        {
            Point const &p = reader.GetPoint();
            LasPoint actPoint(p.GetX(),
                              p.GetY(),
                              p.GetZ(),
                              p.GetIntensity(),
                              p.GetReturnNumber(),
                              p.GetNumberOfReturns(),
                              p.GetClassification());
            uint x = (uint) ((actPoint.getX() - minX) / 5);
            uint y = (uint) (actPoint.getY() - minY) / 5;
            if (!isLoaded.at(make_pair(x, y)).first ||
                (isLoaded.at(make_pair(x, y)).first && isLoaded.at(make_pair(x, y)).second != 0)) {
                points.insert(pair<pair<uint, uint>, LasPoint>(make_pair(x, y), actPoint));
                isLoaded.at(make_pair(x, y)).first = true;
                isLoaded.at(make_pair(x, y)).second++;
            }
            idx_actual++;
        }
        retVal = true;
    }
    catch (exception const &e)
    {
        cerr << "Error : " << e.what() << endl;
        retVal = false;
    }
    return retVal;
}

bool ReadWriteData::writeModelData(const string& fileName, map<pair<uint,uint>, LandCoverParams>& params)
{
    try
    {
        ofstream  FileModel;
        FileModel.open(fileName, std::ios_base::app);

        if(FileModel.is_open())
        {
            for (map<pair<uint,uint>,LandCoverParams>::iterator it=params.begin(); it!=params.end(); ++it)
            {
                FileModel << static_cast<ostringstream*>( &(ostringstream() << it->first.first))->str() << "\t";
                FileModel << static_cast<ostringstream*>( &(ostringstream() << it->first.second))->str() << "\t";
                FileModel << static_cast<ostringstream*>( &(ostringstream() << it->second.getCSM()))->str() << "\t";
                FileModel << static_cast<ostringstream*>( &(ostringstream() << it->second.getTM()))->str() << "\t";
                FileModel << static_cast<ostringstream*>( &(ostringstream() << it->second.getVHM()))->str() << "\t";
                FileModel << static_cast<ostringstream*>( &(ostringstream() << it->second.getIM()))->str() << "\t";
                FileModel << static_cast<ostringstream*>( &(ostringstream() << it->second.getIDM()))->str() << "\t";
                FileModel << static_cast<ostringstream*>( &(ostringstream() << it->second.getSkM()))->str() << "\t";
                FileModel << static_cast<ostringstream*>( &(ostringstream() << it->second.getKrM()))->str() << "\t";
                FileModel << static_cast<ostringstream*>( &(ostringstream() << it->second.getSkMc()))->str() << "\t";
                FileModel << static_cast<ostringstream*>( &(ostringstream() << it->second.getKrMc()))->str() << "\t";
                FileModel << static_cast<ostringstream*>( &(ostringstream() << it->second.getPCM()))->str() << "\t";
                FileModel << static_cast<ostringstream*>( &(ostringstream() << it->second.getClassDef()))->str() << endl;
            }
        }
        retVal = true;
    }
    catch (exception const& e)
    {
        cerr << "Error: " << e.what() << endl;
        retVal = false;
    }
    return  retVal;
}

bool ReadWriteData::writeClassData(const string& fileName, map<pair<uint,uint>, LandCoverParams>& params)
{
    try
    {
        ofstream FileClass;
        FileClass.open(fileName, std::ios_base::app);

        if(FileClass.is_open())
        {
            for (map<pair<uint,uint>,LandCoverParams>::iterator it=params.begin(); it!=params.end(); ++it)
            {
                FileClass << static_cast<ostringstream*>( &(ostringstream() << it->first.first))->str() << " ";
                FileClass << static_cast<ostringstream*>( &(ostringstream() << it->first.second))->str() << " ";
                FileClass << static_cast<ostringstream*>( &(ostringstream() << it->second.getClassDef()))->str() << " ";
                FileClass << static_cast<ostringstream*>( &(ostringstream() << it->second.getClassAlg1()))->str() << " ";
                FileClass << static_cast<ostringstream*>( &(ostringstream() << it->second.getClassAlg2()))->str() << endl;
            }
        }
        retVal = true;
    }
    catch (exception const& e)
    {
        cerr << "Error: " << e.what() << endl;
        retVal = false;
    }
    return  retVal;
}

bool ReadWriteData::readModelData(const string &fileName, map<pair<uint, uint>, LandCoverParams>& params)
{
    try
    {
        string tmpLine, tmpParam;
        uint x, y;
        params.clear();

        stringstream stream;
        ifstream File(fileName);

        if(File.is_open())
        {
            getline(File, tmpLine);
            cout << "Reading:" << tmpLine << endl;

            while (getline(File, tmpLine))
            {//X, Y, CSM, TM, VHM, IM, IDM, SkM, KrM, SkMc, KrMc, PCM, Def
                LandCoverParams tmpModel;
                stream << tmpLine;

                stream >> tmpParam;
                x = (uint) stoi(tmpParam);
                stream >> tmpParam;
                y = (uint) stoi(tmpParam);

                stream >> tmpParam;
                tmpModel.setCSM(stod(tmpParam));
                stream >> tmpParam;
                tmpModel.setTM(stod(tmpParam));
                stream >> tmpParam;
                tmpModel.setVHM(stod(tmpParam));
                stream >> tmpParam;
                tmpModel.setIM(stod(tmpParam));
                stream >> tmpParam;
                tmpModel.setIDM(stod(tmpParam));
                stream >> tmpParam;
                tmpModel.setSkM(stod(tmpParam));
                stream >> tmpParam;
                tmpModel.setKrM(stod(tmpParam));
                stream >> tmpParam;
                tmpModel.setSkMc(stod(tmpParam));
                stream >> tmpParam;
                tmpModel.setKrMc(stod(tmpParam));
                stream >> tmpParam;
                tmpModel.setPCM(stod(tmpParam));
                stream >> tmpParam;
                tmpModel.setClassDef(stoi(tmpParam));

                stream.str(string());
                stream.clear();

                params.insert(pair<pair<uint, uint>, LandCoverParams>(make_pair(x,y), tmpModel));
            }
        }
        retVal = true;
    }
    catch (exception const& e)
    {
        cerr << "Error: " << e.what() << endl;
        retVal = false;
    }
    return  retVal;
    }

bool ReadWriteData::writeClassStat(const string& fileNameStat, vector<uint>& defCls, vector<uint>& alg1Cls, vector<uint>& alg2Cls)
{
    try
    {
        ofstream FileStat;
        FileStat.open(fileNameStat, std::ios_base::app);

        uint defSum = 0, alg1Sum = 0, alg2Sum =0;
        double tmpPerc;

       vector<string> defNames = {"Never clsassified:",
                                  "Unclassified:     ",
                                  "Ground:           ",
                                  "Low vegetation:   ",
                                  "Medium vegetation:",
                                  "High vegetation:  ",
                                  "Buildung:         ",
                                  "Low point:        ",
                                  "High point:       ",
                                  "Water:            ",
                                  "Other:           "};

        vector<string> algNames = {"Other:           ",
                                   "Water:           ",
                                   "Gravel:          ",
                                   "ShortVeg:        ",
                                   "BareEarth:       ",
                                   "Young Plant. F.: ",
                                   "Inter. Plant. F.:",
                                   "Mature Plant. F.:",
                                   "Mater Nat. F.:   ",
                                   "Young Nat. F.:   "};

        for(const auto& cls: defCls)
        {
            defSum += cls;
        }

        for(const auto& cls: alg1Cls)
        {
            alg1Sum += cls;
        }

        for(const auto& cls: alg2Cls)
        {
            alg2Sum += cls;
        }

        if(FileStat.is_open())
        {
            FileStat << " ----- Default Classification -----" << endl;
            for (auto idx = 0; idx < defCls.size(); idx++)
            {
                FileStat << static_cast<ostringstream*>( &(ostringstream() << idx))->str() << ". " << defNames[idx]<<"\t\t";
                FileStat << static_cast<ostringstream*>( &(ostringstream() << defCls[idx]))->str() << " (";
                tmpPerc = defCls[idx]/(double)defSum *100;
                FileStat << static_cast<ostringstream*>( &(ostringstream() << tmpPerc))->str() << " %)" << endl;

            }

            FileStat << endl << " ----- Alg1 and Alg2 Classification -----" << endl;
            for (auto idx = 0; idx < alg1Cls.size(); idx++)
            {
                FileStat << static_cast<ostringstream*>( &(ostringstream() << idx))->str() << ". " << algNames[idx]<<"\t\t";
                FileStat << static_cast<ostringstream*>( &(ostringstream() << alg1Cls[idx]))->str() << " (";
                tmpPerc = alg1Cls[idx]/(double)alg1Sum * 100;
                FileStat << static_cast<ostringstream*>( &(ostringstream() << tmpPerc))->str() << "%)\t";
                FileStat << static_cast<ostringstream*>( &(ostringstream() << alg2Cls[idx]))->str() << " (";
                tmpPerc = alg2Cls[idx]/(double)alg2Sum * 100;
                FileStat << static_cast<ostringstream*>( &(ostringstream() << tmpPerc))->str() << " %)" << endl;
            }
        }
        retVal = true;
    }
    catch (exception const& e)
    {
        cerr << "Error: " << e.what() << endl;
        retVal = false;
    }
    return  retVal;
}




