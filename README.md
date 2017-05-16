# ttaf_land_cover_classification

Main program: LidarClassProcess.cpp
PointCloudData data(source_file); 	--> Load LAS/LAZ file for create surface models, classify, and show maps
PointCloudData data; 				--> Load an existing file with surface models for classify, or just show maps
data.processPoints(); 				--> Create models, classify data
data.classFromModFile(); 			--> Classify from existing model file
data.showMaps(CLASS_ALL/CLASS_DEF/CLASS_ALG1/CLASS_ALG2); --> Show all/selected map
