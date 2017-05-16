#include "PointCloudData.h"

#define MODE_ALL 0 //Read points, create models, calculate classification, and show the result
#define MODE_CL_SH 1 //Calculate classification from model file, and show result
#define MODE_SHOW 2 //Show classification result

int main()
{
    const string source_file = "holland.LAZ";
    const int mode = MODE_ALL;

    if(MODE_ALL == mode)
    {
        PointCloudData data(source_file);
        if (data.processPoints())
        {
            data.showMaps(CLASS_ALL);
            //data.showMaps(CLASS_DEF);
            //data.showMaps(CLASS_ALG1);
            //data.showMaps(CLASS_ALG2);
        }
    }
    else{
        PointCloudData data;
        if( (MODE_CL_SH == mode && data.classFromModFile())
            || MODE_SHOW == mode )
        {
            data.showMaps(CLASS_ALL);
        }
    }

    return 0;
}