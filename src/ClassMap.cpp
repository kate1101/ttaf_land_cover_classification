//
// Created by tekla on 2017.05.05..
//

#include "ClassMap.h"

enum DefLandCovType{
    NEVER_CLS,
    UNCLS,
    GROUND,
    LOW_V,
    MED_V,
    HIGH_V,
    BUILD,
    LOW_P,
    HIGH_P,
    WAT1
};

enum AlgLandCovType{
    OTH,
    WAT2,
    GRAV,
    SHORT_V,
    BARE_EA,
    YOUNG_P_F,
    INTER_P_F,
    MAT_P_F,
    MAT_N_F,
    YOUNG_N_F
};

void ClassMap::setColorDef(int def, Vec3b &tmpColor)
{

    const Vec3b black(0, 0, 0);
    const Vec3b yellow(0, 255, 255);
    const Vec3b light_green(150, 255, 200);
    const Vec3b med_green(0, 255, 0);
    const Vec3b dark_green(0, 100, 0);
    const Vec3b red(0, 0, 255);
    const Vec3b light_gray(180, 180, 180);
    const Vec3b dark_gray(50, 50, 50);
    const Vec3b blue(255, 50, 50);
    const Vec3b white(255, 255, 255);

    switch ((DefLandCovType)def)
    {
        case NEVER_CLS:
            tmpColor = black;
            defCls[0]++;
            break;
        case UNCLS:
            tmpColor = black;
            defCls[1]++;
            break;
        case GROUND:
            tmpColor = yellow;
            defCls[2]++;
            break;
        case LOW_V:
            tmpColor = light_green;
            defCls[3]++;
            break;
        case MED_V:
            tmpColor = med_green;
            defCls[4]++;
            break;
        case HIGH_V:
            tmpColor = dark_green;
            defCls[5]++;
            break;
        case BUILD:
            tmpColor = red;
            defCls[6]++;
            break;
        case LOW_P:
            tmpColor = light_gray;
            defCls[7]++;
            break;
        case HIGH_P:
            tmpColor = dark_gray;
            defCls[8]++;
            break;
        case WAT1:
            tmpColor = blue;
            defCls[9]++;
            break;
        default:
            tmpColor = white;
            defCls[10]++;
            break;
    }
}

void ClassMap::setColorAlg(int clas, Vec3b &tmpColor, int alg)
{

    const Vec3b white(255, 255, 255);
    const Vec3b blue(255, 50, 50);
    const Vec3b gray(128, 128, 128);
    const Vec3b light_yellow(122, 255, 255);
    const Vec3b yellow(0, 255, 255);
    const Vec3b orange(26, 140, 255);
    const Vec3b red(0, 0, 255);
    const Vec3b brown(0, 80, 120);
    const Vec3b dark_green(60, 120, 0);
    const Vec3b light_green(0, 215, 50);

    switch ((AlgLandCovType)clas)
    {
        case OTH:
            tmpColor = white;
            if (CLASS_ALG1 == alg) alg1Cls[0]++;
            if (CLASS_ALG2 == alg) alg2Cls[0]++;
            break;
        case WAT2:
            tmpColor = blue;
            if (CLASS_ALG1 == alg) alg1Cls[1]++;
            if (CLASS_ALG2 == alg) alg2Cls[1]++;
            break;
        case GRAV:
            tmpColor = gray;
            if (CLASS_ALG1 == alg) alg1Cls[2]++;
            if (CLASS_ALG2 == alg) alg2Cls[2]++;
            break;
        case SHORT_V:
            tmpColor = light_yellow;
            if (CLASS_ALG1 == alg) alg1Cls[3]++;
            if (CLASS_ALG2 == alg) alg2Cls[3]++;
            break;
        case BARE_EA:
            tmpColor = yellow;
            if (CLASS_ALG1 == alg) alg1Cls[4]++;
            if (CLASS_ALG2 == alg) alg2Cls[4]++;
            break;
        case YOUNG_P_F:
            tmpColor = orange;
            if (CLASS_ALG1 == alg) alg1Cls[5]++;
            if (CLASS_ALG2 == alg) alg2Cls[5]++;
            break;
        case INTER_P_F:
            tmpColor = red;
            if (CLASS_ALG1 == alg) alg1Cls[6]++;
            if (CLASS_ALG2 == alg) alg2Cls[6]++;
            break;
        case MAT_P_F:
            tmpColor = brown;
            if (CLASS_ALG1 == alg) alg1Cls[7]++;
            if (CLASS_ALG2 == alg) alg2Cls[7]++;
            break;
        case MAT_N_F:
            tmpColor = dark_green;
            if (CLASS_ALG1 == alg) alg1Cls[8]++;
            if (CLASS_ALG2 == alg) alg2Cls[8]++;
            break;
        case YOUNG_N_F:
            tmpColor = light_green;
            if (CLASS_ALG1 == alg) alg1Cls[9]++;
            if (CLASS_ALG2 == alg) alg2Cls[9]++;
            break;
        default:
            break;
    }
}


ClassMap::ClassMap(string& fileName) : fileName(fileName)
{
    defCls.resize(11, 0);
    alg1Cls.resize(10, 0);
    alg2Cls.resize(10, 0);

    string tmpLine, tmpParam;
    Vec3b tmpColor(0,0,0);
    int x = 0, y = 0, def = 0, alg1 = 0, alg2 = 0;

    try
    {
        stringstream stream;
        ifstream File(fileName);

        if (File.is_open()) {
            getline(File, tmpLine);
            cout << "Reading:" << tmpLine << endl;

            getline(File, tmpLine);
            stream << tmpLine;
            stream >> tmpParam;
            stream >> tmpParam;
            sizeX = stoi(tmpParam);
            stream >> tmpParam;
            sizeY = stoi(tmpParam);
            stream.str(string());
            stream.clear();

            imgSrc = Mat(Size(sizeX, sizeY), CV_8UC3, Scalar(0, 0, 0));
            imgAlg1 = Mat(Size(sizeX, sizeY), CV_8UC3, Scalar(0, 0, 0));
            imgAlg2 = Mat(Size(sizeX, sizeY), CV_8UC3, Scalar(0, 0, 0));

            while (getline(File, tmpLine)) {
                stream << tmpLine;
                stream >> tmpParam;
                x = stoi(tmpParam);
                stream >> tmpParam;
                y = stoi(tmpParam);
                stream >> tmpParam;
                def = stoi(tmpParam);
                stream >> tmpParam;
                alg1 = stoi(tmpParam);
                stream >> tmpParam;
                alg2 = stoi(tmpParam);
                stream.str(string());
                stream.clear();

                setColorDef(def, tmpColor);
                imgSrc.at<Vec3b>(sizeY - y - 1, x)[0] = tmpColor[0];
                imgSrc.at<Vec3b>(sizeY - y - 1, x)[1] = tmpColor[1];
                imgSrc.at<Vec3b>(sizeY - y - 1, x)[2] = tmpColor[2];

                setColorAlg(alg1, tmpColor, CLASS_ALG1);
                imgAlg1.at<Vec3b>(sizeY - y - 1, x)[0] = tmpColor[0];
                imgAlg1.at<Vec3b>(sizeY - y - 1, x)[1] = tmpColor[1];
                imgAlg1.at<Vec3b>(sizeY - y - 1, x)[2] = tmpColor[2];

                setColorAlg(alg2, tmpColor, CLASS_ALG2);
                imgAlg2.at<Vec3b>(sizeY - y - 1, x)[0] = tmpColor[0];
                imgAlg2.at<Vec3b>(sizeY - y - 1, x)[1] = tmpColor[1];
                imgAlg2.at<Vec3b>(sizeY - y - 1, x)[2] = tmpColor[2];
            }
        }

        ReadWriteData writer;
        writer.writeClassStat("statData.txt", defCls, alg1Cls, alg2Cls);

        isReaded = true;
    }
    catch(exception const& e)
    {
        cerr << "Error: " << e.what() << endl;
        isReaded = false;
    }
}

void ClassMap::show(int clNum) {

    if(isReaded)
    {
        Mat img, img2;
        string outName;

        if (clNum == CLASS_ALG1)
        {
            img = imgAlg1.clone();
            outName = CLASS_ALG1_S;
        }
        else if (clNum == CLASS_ALG2)
        {
            img = imgAlg2.clone();
            outName = CLASS_ALG2_S;
        }
        else if (clNum == CLASS_DEF)
        {
            img = imgSrc.clone();
            outName = CLASS_DEF_S;
        }

        double newCol = img.cols;
        double newRow = img.rows;
        double scale;

        if (newCol > newRow) //1920 x 1080
        {
            scale = 1600/newCol;
        }
        else
        {
            scale = 850/newRow;
        }

        if(scale > 1)
        {
            newCol *= scale;
            newRow *= scale;
        }
        Size size((int)newCol, (int)newRow);
        resize(img, img2, size);
        cv::imshow("OutAlg", img2);
        cv::waitKey(0);
        imwrite("alg" + outName + ".png", img2);
    }
    else
    {
        cerr << "Error : Unable show maps!" << endl;
    }
}

ClassMap ClassMap::operator=(const ClassMap &map) {
    this->imgSrc = map.imgSrc;
    this->imgAlg1 = map.imgAlg1;
    this->imgAlg2 = map.imgAlg2;
    this->sizeX = map.sizeX;
    this->sizeY = map.sizeY;
    this->fileName = map.fileName;
    return *this;
}
