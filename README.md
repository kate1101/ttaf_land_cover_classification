# ttaf_land_cover_classification

Main program: LidarClassProcess.cpp

PointCloudData data(source_file); --> If you want create models, classify, and show maps
PointCloudData data; --> If you want load an existing model file for classify or just show maps
data.processPoints(); --> Create models, classify data
data.classFromModFile(); --> Classify from existing model file
data.showMaps(CLASS_ALL/CLASS_DEF/CLASS_ALG1/CLASS_ALG2); --> Show all/selected map

LibLAS and OpenCV is required