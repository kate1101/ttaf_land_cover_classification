//
// Created by tekla on 2017.05.05..
//

#include "ClassMap.h"


void ClassMap::setColorDef(int def, Vec3b &tmpColor)
{
    /*
     * Land cover types:
     *
     * 0 Never classified
     * 1 Unclassified
     * 2 Ground
     * 3 Low Vegetation
     * 4 Medium Vegetation
     * 5 High Vegetation
     * 6 Building
     * 7 Low Point ("low noise")
     * 8 High Point ("high noise")
     * 9 Water
     * 10+ Other
     */
    //                (B,  G,  R)
    const Vec3b color0(0, 0, 0);        //black
    const Vec3b color1(0, 0, 0);        //black
    const Vec3b color2(0, 255, 255);    //yellow
    const Vec3b color3(150, 255, 200);  //light green-yellow
    const Vec3b color4(0, 255, 0);      //mid green
    const Vec3b color5(0, 100, 0);      //dark green
    const Vec3b color6(0, 0, 255);      //red
    const Vec3b color7(180, 180, 180);  //light grey
    const Vec3b color8(50, 50, 50);     //dark grey
    const Vec3b color9(255, 50, 50);    //blue
    const Vec3b color10(255, 255, 255); //while

    switch (def) {
        case 0:
            tmpColor = color0;
            defCls[0]++;
            break;
        case 1:
            tmpColor = color1;
            defCls[1]++;
            break;
        case 2:
            tmpColor = color2;
            defCls[2]++;
            break;
        case 3:
            tmpColor = color3;
            defCls[3]++;
            break;
        case 4:
            tmpColor = color4;
            defCls[4]++;
            break;
        case 5:
            tmpColor = color5;
            defCls[5]++;
            break;
        case 6:
            tmpColor = color6;
            defCls[6]++;
            break;
        case 7:
            tmpColor = color7;
            defCls[7]++;
            break;
        case 8:
            tmpColor = color8;
            defCls[8]++;
            break;
        case 9:
            tmpColor = color9;
            defCls[9]++;
            break;
        default:
            tmpColor = color10;
            defCls[10]++;
            break;
    }
}

void ClassMap::setColorAlg(int clas, Vec3b &tmpColor, int alg)
{
    /*
    * Land cover types:
    *
    * 0 Other
    * 1 Water
    * 2 Gravel
    * 3 ShortVeg
    * 4 BareEarth
    * 5 Young Planted Forest
    * 6 Inter. Planted Forest
    * 7 Mature Planted Forest
    * 8 Mater Natural Forest
    * 9 Young Natural Forest
    */
    //                 (B,  G,  R)
    const Vec3b color0(255, 255, 255);  //white
    const Vec3b color1(255, 50, 50);    //blue
    const Vec3b color2(128, 128, 128);  //gray
    const Vec3b color3(122, 255, 255);  //light yellow
    const Vec3b color4(0, 255, 255);    //yellow
    const Vec3b color5(26, 140, 255);   // orange//(150, 255, 150);  //light green
    const Vec3b color6(0, 0, 255);      // red //(0, 255, 0);      //mid green
    const Vec3b color7(0, 80, 120);     //dark brown
    const Vec3b color8(60, 120, 0);     //dark green
    const Vec3b color9(0, 215, 50);     //light green- yellow

    switch (clas)
    {
        case 0:
            tmpColor = color0;
            if (CLASS_ALG1 == alg) alg1Cls[0]++;
            if (CLASS_ALG2 == alg) alg2Cls[0]++;
            break;
        case 1:
            tmpColor = color1;
            if (CLASS_ALG1 == alg) alg1Cls[1]++;
            if (CLASS_ALG2 == alg) alg2Cls[1]++;
            break;
        case 2:
            tmpColor = color2;
            if (CLASS_ALG1 == alg) alg1Cls[2]++;
            if (CLASS_ALG2 == alg) alg2Cls[2]++;
            break;
        case 3:
            tmpColor = color3;
            if (CLASS_ALG1 == alg) alg1Cls[3]++;
            if (CLASS_ALG2 == alg) alg2Cls[3]++;
            break;
        case 4:
            tmpColor = color4;
            if (CLASS_ALG1 == alg) alg1Cls[4]++;
            if (CLASS_ALG2 == alg) alg2Cls[4]++;
            break;
        case 5:
            tmpColor = color5;
            if (CLASS_ALG1 == alg) alg1Cls[5]++;
            if (CLASS_ALG2 == alg) alg2Cls[5]++;
            break;
        case 6:
            tmpColor = color6;
            if (CLASS_ALG1 == alg) alg1Cls[6]++;
            if (CLASS_ALG2 == alg) alg2Cls[6]++;
            break;
        case 7:
            tmpColor = color7;
            if (CLASS_ALG1 == alg) alg1Cls[7]++;
            if (CLASS_ALG2 == alg) alg2Cls[7]++;
            break;
        case 8:
            tmpColor = color8;
            if (CLASS_ALG1 == alg) alg1Cls[8]++;
            if (CLASS_ALG2 == alg) alg2Cls[8]++;
            break;
        case 9:
            tmpColor = color9;
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
    stringstream stream;
    ifstream File(fileName);

    if(File.is_open())
    {
        getline(File, tmpLine);
        cout<< "Reading:" << tmpLine << endl;

        getline(File, tmpLine);
        stream << tmpLine;
        stream >> tmpParam;
        stream >> tmpParam;
        sizeX = stoi(tmpParam);
        stream >> tmpParam;
        sizeY = stoi(tmpParam);
        stream.str(string());
        stream.clear();

        imgSrc = Mat(Size(sizeX, sizeY), CV_8UC3, Scalar(0,0,0));
        imgAlg1 = Mat(Size(sizeX, sizeY), CV_8UC3, Scalar(0,0,0));
        imgAlg2 = Mat(Size(sizeX, sizeY), CV_8UC3, Scalar(0,0,0));

        while (getline(File, tmpLine))
        {
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
            imgSrc.at<Vec3b>(sizeY-y-1,x)[0] = tmpColor[0];
            imgSrc.at<Vec3b>(sizeY-y-1,x)[1] = tmpColor[1];
            imgSrc.at<Vec3b>(sizeY-y-1,x)[2] = tmpColor[2];

            setColorAlg(alg1, tmpColor, CLASS_ALG1);
            imgAlg1.at<Vec3b>(sizeY-y-1,x)[0] = tmpColor[0];
            imgAlg1.at<Vec3b>(sizeY-y-1,x)[1] = tmpColor[1];
            imgAlg1.at<Vec3b>(sizeY-y-1,x)[2] = tmpColor[2];

            setColorAlg(alg2,tmpColor, CLASS_ALG2);
            imgAlg2.at<Vec3b>(sizeY-y-1,x)[0] = tmpColor[0];
            imgAlg2.at<Vec3b>(sizeY-y-1,x)[1] = tmpColor[1];
            imgAlg2.at<Vec3b>(sizeY-y-1,x)[2] = tmpColor[2];
        }
    }

    ReadWriteData writer;
    writer.writeClassStat("statData.txt", defCls, alg1Cls, alg2Cls);
}


void ClassMap::show(int clNum) {

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

    newCol *= scale;
    newRow *= scale;
    Size size((int)newCol, (int)newRow);
    resize(img, img2, size);
    cv::imshow("OutAlg", img2);
    cv::waitKey(0);
    imwrite("alg" + outName + ".png", img2);
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

