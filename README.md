# ttaf_land_cover_classification
-----------------------------------------------------------------------------------------------
Corresponding source file: Any LAS/LAZ file with LiDAR pointcloud
-----------------------------------------------------------------------------------------------
Main program: LidarClassProcess.cpp

With this program we can calculate 8 surface models on LiDAR pointcloud data and classify every 5*5m^2 cell of terrain with 2 algorithms.
Based on: Antonarakis, A.S., Richards, K.S., Brasington, J.: Object-based land cover classification using airborne LiDAR, Remote Sensing of Environment, 112 (6), pp. 2988-2998, 2008.
(http://www.sciencedirect.com/science/article/pii/S0034425708000667)
-----------------------------------------------------------------------------------------------
With methods of PointCloudData can execute the following processes:
 
PointCloudData data(source_file); 	--> Use this constructor to load a LAS/LAZ file for create surface models, classify, and show maps
PointCloudData data; 				--> Use this constructor to load an existing file with surface models for classify, or just show maps
data.processPoints(); 				--> Create models and classify data
data.classFromModFile(); 			--> Classifiy data from existing model file
data.showMaps(CLASS_ALL/CLASS_DEF/CLASS_ALG1/CLASS_ALG2); --> Show all/selected map
-----------------------------------------------------------------------------------------------
Output files:

lidar_models.txt -->In every row (X;Y) coordinates and the 8 surface models result.
					At the endof the lines the classification result of original LiDAR classification.
					
lidar_classes.txt -->In 2. row: maximum (X;Y) coordinate values .
					 After then in every row (X;Y) coordinates, classification result of original LiDAR classification, 1. Algorithm and 2. Algorithm.

statData.txt --> Statistics about classification result.
				 At first every class of default LiDar classification with the number of points and the percentage distribution.
				 Then every class of implemented algorithms in two colums with the number of points and the percentage distribution.
				 
alg 0.png --> Color coded image about classification result of original LiDAR classification
alg 0.png --> Color coded image about classification result of the 1. implemented algorithm
alg 0.png --> Color coded image about classification result of the 2. implemented algorithm
-----------------------------------------------------------------------------------------------
Sample results: 
3 areas from public AHN3 pointcloud database (https://www.pdok.nl/nl/ahn3-downloads)

delf: 
Delftse Hout - Lake near Delft town surrounded by forest
http://gis.inf.elte.hu/files/public/ahn-samples/dl/ahn3_delftse_hout.laz [4km2, 367MB, 70 391 851 points, running: 5 min]

berg: 
Bergse Bos - Park in Rotterdam, there are forest areas mostly at the west 
http://gis.inf.elte.hu/files/public/ahn-samples/dl/ahn3_bergse_bos.laz [~8km2, 722MB, 142 914 525 points, running: 10 min]

meij: 
Meijendel - Beach north from Haga, National Park, there are forest areas away from the sea
http://gis.inf.elte.hu/files/public/ahn-samples/dl/ahn3_meijendel.laz  [27km2, 3811MB, 739 245 272 points, running: ~1h]