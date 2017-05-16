//
// Created by tekla on 2017.04.25..
//

#ifndef LASTEST_LANDCOVERPARAMS_H
#define LASTEST_LANDCOVERPARAMS_H

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

#define OTHER 0
#define WATER 1
#define GRAVEL 2
#define SHORT_VEG 3
#define BARE_EARTH 4
#define YOUNG_PLANTED_FOREST 5
#define INTER_PLANTED_FOREST 6
#define MATURE_PLANTED_FOREST 7
#define MATURE_NAT_FOREST 8
#define YOUNG_NAT_FOREST 9

class LandCoverParams {
private:
    double CSM,     //Canopy Surface Model
            TM,     //Terrain Model
            VHM,    //Vegetation Height Model
            IM,     //Intensity Model
            IDM,    //Intensity Difference Model
            SkM,    //Skewness Model - Ground-on
            KrM,    //Kurtosis Model - Ground-on
            SkMc,   //Skewness Model - Ground-off
            KrMc,   //Kurtosis Model - Ground-off
            PCM;    //Percentage Canopy Model

    int classDef,   //Median of lidar class points
        classAlg1,  //Result of Algorithm 1. - Without canopy data
        classAlg2;  //Result of Algorithm 2. - With canopy constraints

    void nearTerr(bool alg1);
    void planted(bool alg1);
    void natural(bool alg1);

public:

    double getCSM() const;

    void setCSM(double CSM);

    double getTM() const;

    void setTM(double TM);

    double getVHM() const;

    void setVHM(double VHM);

    double getIM() const;

    void setIM(double IM);

    double getIDM() const;

    void setIDM(double IDM);

    double getSkM() const;

    void setSkM(double SkM);

    double getKrM() const;

    void setKrM(double KrM);

    double getSkMc() const;

    void setSkMc(double SkMc);

    double getKrMc() const;

    void setKrMc(double KrMc);

    double getPCM() const;

    void setPCM(double PCM);

    void calcAlg1();

    int getClassAlg1() const;

    void calcAlg2();

    int getClassAlg2() const;

    int getClassDef() const;

    void setClassDef(int classDef);

};


#endif //LASTEST_LANDCOVERPARAMS_H
