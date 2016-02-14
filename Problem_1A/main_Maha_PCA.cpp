//NAME: Amruta Kulkarni
//USC ID: 6914970827
//USC Email: arkulkar@usc.edu
//Submission date: 11 Oct 2015

//Problem 1A, part 1,2,3,5
//This code Performs binary classificication of straw and grass images by using Minimum Distance to class means classifier. It will first perform classification without feature reduction and then by using PCA for feature reduction
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <fstream>
#include <string>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

//Function to return the product of 2 kernals as a laws filter
void tensorProduct(const int (&kernel1)[5], const int (&kernel2)[5], int (&product)[5][5])

{
    for ( int j = 0; j < 5; j++)
    {
        for (int i = 0; i < 5; i++)
        {
            product[i][j] = (*(kernel1 + i)) * (*(kernel2 + j));
        }
    }
}



int main()
{
    char *argv[] =
    {
        "unknown_01.raw","unknown_02.raw","unknown_03.raw","unknown_04.raw","unknown_05.raw","unknown_06.raw","unknown_07.raw","unknown_08.raw","unknown_09.raw","unknown_10.raw","unknown_11.raw","unknown_12.raw","unknown_13.raw","unknown_14.raw","unknown_15.raw","unknown_16.raw","unknown_17.raw","unknown_18.raw","unknown_19.raw","unknown_20.raw","unknown_21.raw","unknown_22.raw","unknown_23.raw","unknown_24.raw",
        
        "grass_01.raw","grass_02.raw","grass_03.raw","grass_04.raw","grass_05.raw","grass_06.raw","grass_07.raw","grass_08.raw","grass_09.raw","grass_10.raw","grass_11.raw","grass_12.raw","grass_13.raw","grass_14.raw","grass_15.raw","grass_16.raw","grass_17.raw","grass_18.raw","grass_19.raw","grass_20.raw","grass_21.raw","grass_22.raw","grass_23.raw","grass_24.raw","grass_25.raw","grass_26.raw","grass_27.raw","grass_28.raw","grass_29.raw","grass_30.raw","grass_31.raw","grass_32.raw","grass_33.raw","grass_34.raw","grass_35.raw","grass_36.raw",
        
        "straw_01.raw","straw_02.raw","straw_03.raw","straw_04.raw","straw_05.raw","straw_06.raw","straw_07.raw","straw_08.raw","straw_09.raw","straw_10.raw","straw_11.raw","straw_12.raw","straw_13.raw","straw_14.raw","straw_15.raw","straw_16.raw","straw_17.raw","straw_18.raw","straw_19.raw","straw_20.raw","straw_21.raw","straw_22.raw","straw_23.raw","straw_24.raw","straw_25.raw","straw_26.raw","straw_27.raw","straw_28.raw","straw_29.raw","straw_30.raw","straw_31.raw","straw_32.raw","straw_33.raw","straw_34.raw","straw_35.raw","straw_36.raw"
        

    };

    FILE *file;
    double energy[96][25];
    for (int imageNumber = 0; imageNumber < 96; imageNumber++)
    {
    
    int width = 128;
    int height = 128;
    
    /* Allocate image data array */
    unsigned char imageData[height][width];
    
    /* Read image */
    if (!(file=fopen(argv[imageNumber],"rb")))
    {
		cout << "Cannot open file: " << argv[imageNumber] <<endl;
		exit(1);
	}
	fread(imageData, sizeof(unsigned char), height*width, file);
	fclose(file);
   
    /* Create extended image matrix */
    int N = 5;
    int extendedWidth = width + (N-1);
    int extendedHeight = height + (N-1);
    int halfLength = (N-1)/2;

    int extendedImageData[extendedWidth][extendedHeight];
    
    //central, top and bottom part
    for(int row = 0; row < height; row++)
    {
        for(int column = 0;column < width; column++)
            
        {
            extendedImageData[row+halfLength][column+halfLength] = imageData[row][column];//copy the red data in the central part of the extended image
            
            int countTop = 0;                                                 //Top part of extended
            for ( int emptyRow = 0; emptyRow < halfLength; emptyRow++)
            {
                extendedImageData[emptyRow][column+halfLength] = imageData[halfLength-countTop][column];
                countTop = countTop + 1;
            }
            
            int countBottom = 0;                                              //Bottom part of extended
            for ( int emptyrow = extendedHeight-1; emptyrow > ((height-1)+halfLength); emptyrow--)
            {
                extendedImageData[emptyrow][column+halfLength] = imageData[(height-1)-halfLength+countBottom][column];
                countBottom = countBottom + 1;
            }
        }
    }
    
    //left and right part
    for (int row = 0; row < extendedHeight; row++)
    {
        //FOR RED
        int countLeft = 0;                                                   //Left columns of extended
        for (int emptyColumn = 0; emptyColumn < halfLength; emptyColumn++)
        {
            extendedImageData[row][emptyColumn] = extendedImageData[row][(N-1)-countLeft];
            countLeft = countLeft + 1;
        }
        
        int countRight = 0;                                                 //Right columns of extended
        for (int emptyColumn = extendedWidth-1; emptyColumn > ((width-1)+halfLength); emptyColumn--)
        {
            extendedImageData[row][emptyColumn] = extendedImageData[row][(extendedWidth-1)-N+countRight];
            countRight = countRight + 1;
        }
    }
    
    /* Pre-Processing */
    double sumWindow;
    double meanWindow;
    int window[N][N];
    for (int row = halfLength; row < extendedHeight-halfLength; row++)
    {
        for (int column = halfLength; column < extendedWidth-halfLength; column++)
        {
            for ( int i = 0; i < N; i++)
            {
                for ( int j = 0; j < N; j++)
                {
                    window[i][j] = extendedImageData[row + (i - halfLength)][column + (j - halfLength)];
                }
            }
            
            //Calculate the mean for every window
            sumWindow = 0;
            for ( int i = 0; i < N; i++)
            {
                for ( int j = 0; j < N; j++)
                {
                    sumWindow = sumWindow + window[i][j];
                }
            }
            meanWindow = sumWindow / (N*N);
            
            //Subtract this mean value from the central pixel in the window
            
            extendedImageData[row][column] = extendedImageData[row][column] - meanWindow;
        }
    }

    
    /*  Create filter bank  and Apply 25 law filters */
    
    int filterBank[N][N][N*N];
    
    int level[5] = {1,4,6,4,1};
    int edge[5] = {-1,-2,0,2,1};
    int spot[5] = {-1,0,2,0,-1};
    int wave[5] = {-1,2,0,-2,1};
    int ripple[5] = {1,-4,6,-4,1};
    
    int kernelProduct1[5][5],kernelProduct2[5][5],kernelProduct3[5][5],
        kernelProduct4[5][5],kernelProduct5[5][5],kernelProduct6[5][5],
        kernelProduct7[5][5],kernelProduct8[5][5],kernelProduct9[5][5],
        kernelProduct10[5][5],kernelProduct11[5][5],kernelProduct12[5][5],
        kernelProduct13[5][5],kernelProduct14[5][5],kernelProduct15[5][5],
        kernelProduct16[5][5],kernelProduct17[5][5],kernelProduct18[5][5],
        kernelProduct19[5][5],kernelProduct20[5][5],kernelProduct21[5][5],
        kernelProduct22[5][5],kernelProduct23[5][5],kernelProduct24[5][5],
        kernelProduct25[5][5];
    
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            tensorProduct(level,level,kernelProduct1);
            filterBank[i][j][0] = kernelProduct1[i][j];
            
            tensorProduct(level,edge,kernelProduct2);
            filterBank[i][j][1] = kernelProduct2[i][j];
            
            tensorProduct(level,spot,kernelProduct3);
            filterBank[i][j][2] = kernelProduct3[i][j];
            
            tensorProduct(level,wave,kernelProduct4);
            filterBank[i][j][3] = kernelProduct4[i][j];
            
            tensorProduct(level,ripple,kernelProduct5);
            filterBank[i][j][4] = kernelProduct5[i][j];
            
            tensorProduct(edge,level,kernelProduct6);
            filterBank[i][j][5] = kernelProduct6[i][j];
            
            tensorProduct(edge,edge,kernelProduct7);
            filterBank[i][j][6] = kernelProduct7[i][j];
            
            tensorProduct(edge,spot,kernelProduct8);
            filterBank[i][j][7] = kernelProduct8[i][j];
            
            tensorProduct(edge,wave,kernelProduct9);
            filterBank[i][j][8] = kernelProduct9[i][j];
            
            tensorProduct(edge,ripple,kernelProduct10);
            filterBank[i][j][9] = kernelProduct10[i][j];
            
            tensorProduct(spot,level,kernelProduct11);
            filterBank[i][j][10] = kernelProduct11[i][j];
            
            tensorProduct(spot,edge,kernelProduct12);
            filterBank[i][j][11] = kernelProduct12[i][j];
            
            tensorProduct(spot,spot,kernelProduct13);
            filterBank[i][j][12] = kernelProduct13[i][j];
            
            tensorProduct(spot,wave,kernelProduct14);
            filterBank[i][j][13] = kernelProduct14[i][j];
            
            tensorProduct(spot,ripple,kernelProduct15);
            filterBank[i][j][14] = kernelProduct15[i][j];
            
            tensorProduct(wave,level,kernelProduct16);
            filterBank[i][j][15] = kernelProduct16[i][j];
            
            tensorProduct(wave,edge,kernelProduct17);
            filterBank[i][j][16] = kernelProduct17[i][j];
            
            tensorProduct(wave,spot,kernelProduct18);
            filterBank[i][j][17] = kernelProduct18[i][j];
            
            tensorProduct(wave,wave,kernelProduct19);
            filterBank[i][j][18] = kernelProduct19[i][j];
            
            tensorProduct(wave,ripple,kernelProduct20);
            filterBank[i][j][19] = kernelProduct20[i][j];
            
            tensorProduct(ripple,level,kernelProduct21);
            filterBank[i][j][20] = kernelProduct21[i][j];
            
            tensorProduct(ripple,edge,kernelProduct22);
            filterBank[i][j][21] = kernelProduct22[i][j];
            
            tensorProduct(ripple,spot,kernelProduct23);
            filterBank[i][j][22] = kernelProduct23[i][j];
            
            tensorProduct(ripple,wave,kernelProduct24);
            filterBank[i][j][23] = kernelProduct24[i][j];
            
            tensorProduct(ripple,ripple,kernelProduct25);
            filterBank[i][j][24] = kernelProduct25[i][j];
    
        }
    }
    
    /* Create 25 filtered images for every current Image */
    
    double filteredImages[extendedHeight][extendedWidth][N*N];
    
    /* Calculate 25 filtered output images */
    int imageWindow[N][N];
    double convolution;
    for (int fImageNumber = 0; fImageNumber < 25; fImageNumber++)
    {
        for (int row = halfLength; row < extendedHeight-halfLength; row++)
        {
            for (int column = halfLength; column < extendedWidth-halfLength; column++)
            {
                for (int i = 0; i < 5; i++)
                {
                    for (int j = 0; j < 5; j++)
                    {
                        imageWindow[i][j] = extendedImageData[row + (i - halfLength)][column + (j - halfLength)];
                    }
                }
                
                convolution = 0;
                for (int i = 0; i < 5; i++)
                {
                    for (int j = 0; j < 5; j++)
                    {
                        double product = imageWindow[i][j] * filterBank[i][j][fImageNumber];
                        convolution = convolution + product;
                    }
                }
                filteredImages[row][column][fImageNumber] = convolution;
            }
        }
    }
    
    /* Feature averaging */
    
    double energySum;
    for (int fImageNumber = 0; fImageNumber < 25; fImageNumber++)
    {
        energySum = 0;
        for (int row = halfLength; row < extendedHeight - halfLength; row++)//Get rid of image extensions
        {
            for (int column = halfLength; column < extendedWidth - halfLength; column++)
            {
                energySum = energySum + (abs(filteredImages[row][column][fImageNumber]) * abs(filteredImages[row][column][fImageNumber]));
            }
        }
        energy[imageNumber][fImageNumber] = energySum/(height * width);
    }
        
    }//Repeat For all 96 Images
    
    /* Feature Post-Processing */
    double min, max, difference;
    double copyFeature[72];
    int size = sizeof(copyFeature)/sizeof(copyFeature[0]);
    
    for (int featureNumber = 0; featureNumber < 25; featureNumber++)
    {
        for (int imageNumber = 24; imageNumber < 96; imageNumber++)
        {
            copyFeature[imageNumber-24] = energy[imageNumber][featureNumber];
        }
        sort (copyFeature, copyFeature + size);
        min = copyFeature[0];
        max = copyFeature[71];//Take min and max from training data and use the same for testing
        difference = max - min;
        for (int imageNumber = 0; imageNumber < 96; imageNumber++)
        {
            energy[imageNumber][featureNumber] = (energy[imageNumber][featureNumber] - min) / difference;//every feature will get normalised
            //cout << energy[imageNumber][featureNumber] << "\t";
        }
        //cout << endl;
        
    }
    
    
    /* Calculate mean and variance of both the classes */
    
    double sumMeanGrassClass;
    double sumVarianceGrassClass;
    double meanGrassClass[25];
    double varianceGrassClass[25];
    double differenceValueAndMeanGrass;
    for (int featureNumber = 0; featureNumber < 25; featureNumber++)
    {
        //calculate the mean of Grass class
        sumMeanGrassClass = 0;
        for (int imageNumber = 24; imageNumber < 60; imageNumber++)
        {
            sumMeanGrassClass = sumMeanGrassClass + energy[imageNumber][featureNumber];
        }
        meanGrassClass[featureNumber] = sumMeanGrassClass/36;
        //Calculate the variance of grass class
        sumVarianceGrassClass = 0;
        for (int imageNumber = 24; imageNumber < 60; imageNumber++)
        {
            differenceValueAndMeanGrass = (energy[imageNumber][featureNumber] - meanGrassClass[featureNumber])*(energy[imageNumber][featureNumber] - meanGrassClass[featureNumber]);
            sumVarianceGrassClass = sumVarianceGrassClass + differenceValueAndMeanGrass;
            
        }
        varianceGrassClass[featureNumber] = sumVarianceGrassClass/36;
        
    }
        
    double sumMeanStrawClass;
    double sumVarianceStrawClass;
    double meanStrawClass[25];
    double varianceStrawClass[25];
    double differenceValueAndMeanStraw;
    for (int featureNumber = 0; featureNumber < 25; featureNumber++)
    {
        //calculate the mean of straw class
        sumMeanStrawClass = 0;
        for (int imageNumber = 60; imageNumber < 96; imageNumber++)
        {
            sumMeanStrawClass = sumMeanStrawClass + energy[imageNumber][featureNumber];
        }
        meanStrawClass[featureNumber] = sumMeanStrawClass/36;
        //calculate the variance of straw class;
        sumVarianceStrawClass = 0;
        for (int imageNumber = 60; imageNumber < 96; imageNumber++)
        {
            differenceValueAndMeanStraw = (energy[imageNumber][featureNumber] - meanStrawClass[featureNumber])*(energy[imageNumber][featureNumber] - meanStrawClass[featureNumber]);
            sumVarianceStrawClass = sumVarianceStrawClass + differenceValueAndMeanStraw;
            
        }
        varianceStrawClass[featureNumber] = sumVarianceStrawClass/36;
    }
    
    /* Calculate the Mahalanobis distance of all the image features form both the class mean */
    double distanceFromGlassMean[96];
    double distanceFromStrawMean[96];
    double imageFeature[25];
    double differenceGrass = 0;
    double differenceStraw = 0;
    double sumGrass = 0;
    double sumStraw = 0;
    
    for (int imageNumber = 0; imageNumber < 96; imageNumber++)
    {
        for(int featureNumber = 0;featureNumber < 25;featureNumber++)
        {
            imageFeature[featureNumber] = energy[imageNumber][featureNumber];
        //cout << sample[i]<<endl;
        }
        sumGrass = 0;
        sumStraw = 0;
        for (int featureNumber = 0;featureNumber < 25;featureNumber++)
        {
            //from grass mean
            differenceGrass = (imageFeature[featureNumber] - meanGrassClass[featureNumber]) * (imageFeature[featureNumber] - meanGrassClass[featureNumber]);
            sumGrass = sumGrass + (differenceGrass / varianceGrassClass[featureNumber]);
            
            //from straw mean
            differenceStraw = (imageFeature[featureNumber] - meanStrawClass[featureNumber]) * (imageFeature[featureNumber] - meanStrawClass[featureNumber]);
            sumStraw = sumStraw + (differenceStraw / varianceStrawClass[featureNumber]);
         
        }
        distanceFromGlassMean[imageNumber] = sqrt(sumGrass);
        distanceFromStrawMean[imageNumber] = sqrt(sumStraw);
        //cout << distanceFromGlassMean[imageNumber] << "\t" << distanceFromStrawMean[imageNumber] << endl;
    }
    
    /* Minimum distance to class means classifier */
    
    int trueLabel[96];
    int classifierLabel[96];
    int correctlyTrained = 0;
    int correctlyTested = 0;
    float errorTraining = 0;
    float errorTesting = 0;
    
    for ( int imageNumber = 24; imageNumber < 60; imageNumber++)
        trueLabel[imageNumber] = 1; //Grass Images are from 24 to 59 and let the label for this class be 1
    
    for ( int imageNumber = 60; imageNumber < 96; imageNumber++)
        trueLabel[imageNumber] = 2; //Straw Images are from 60 to 95 and let the label for this class be 2
    
    //Assign truelabels to unknowns by looking at every image
    trueLabel[0] = 2; trueLabel[1] = 2; trueLabel[2] = 1; trueLabel[3] = 1; trueLabel[4] = 1; trueLabel[5] = 2; trueLabel[6] = 1; trueLabel[7] = 2;
    trueLabel[8] = 2; trueLabel[9] = 1; trueLabel[10] = 1; trueLabel[11] = 1; trueLabel[12] = 2; trueLabel[13] = 1; trueLabel[14] = 2; trueLabel[15] = 2;
    trueLabel[16] = 2; trueLabel[17] = 2; trueLabel[18] = 1; trueLabel[19] = 1; trueLabel[20] = 1; trueLabel[21] = 2; trueLabel[22] = 2; trueLabel[23] = 1;
    
    //UNCOMMENT THIS TO DISPLAY TRUE LABELS
    
    //for ( int imageNumber = 0; imageNumber < 96; imageNumber++)
        //cout << trueLabel[imageNumber] << endl;
    
    
    for (int imageNumber = 0; imageNumber < 96; imageNumber++)
    {
        if (distanceFromGlassMean[imageNumber] < distanceFromStrawMean[imageNumber])
        {
            classifierLabel[imageNumber] = 1; //Assign it to class 1 of grass
        }
        else
            classifierLabel[imageNumber] = 2; //Assign it to class 2 of straw
        
        //cout << trueLabel[imageNumber] << "\t" << classifierLabel[imageNumber] << endl;
    }
    
    
    //Error For training data
    
    for (int imageNumber = 24; imageNumber < 96; imageNumber++)
    {
        if (trueLabel[imageNumber] == classifierLabel[imageNumber])
        {
            correctlyTrained = correctlyTrained + 1;
        }
    }
    
    errorTraining = (double(72 - correctlyTrained) / double(72)) * 100; //total 72 training images
    
    //Error for Test data
    
    for (int imageNumber = 0; imageNumber < 24; imageNumber++)
    {
        if (trueLabel[imageNumber] == classifierLabel[imageNumber])
        {
            correctlyTested = correctlyTested + 1;
        }
    }
    
    errorTesting = (double(24 - correctlyTested) / double(24)) * 100; //Total 24 unknown images
    
    cout << "error for training data is : " << errorTraining << endl;
    cout << "error for testing data is : " << errorTesting << endl;
    
    /* Principal Component analysis */
    
    //Separate training and testing
    //UNCOMMENT THE NEXT 6 COMMENTS TO DISPLAY THE TRAINING AND TESTING DATA
    double training[72][25];
    int row = 0;
    //cout << "Training features are" << endl;
    for (int imageNumber = 24; imageNumber < 96; imageNumber++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            training[row][featureNumber] = energy[imageNumber][featureNumber];
            //cout << training[row][featureNumber] << "\t";
        }
        row = row + 1;
        //cout << endl;
    }
    //cout << "Testing features are" << endl;
    double testing[24][25];
    row = 0;
    for (int imageNumber = 0; imageNumber < 24; imageNumber++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            testing[row][featureNumber] = energy[imageNumber][featureNumber];
            //cout << testing[row][featureNumber] << "\t";
        }
        row = row + 1;
        //cout << endl;
    }

    //Start PCA
    Mat featuresTrainingPCA;
    featuresTrainingPCA = Mat(72,25,CV_64F,training);
    
    Mat featuresTestingPCA;
    featuresTestingPCA = Mat(24,25,CV_64F,testing);
    
    //Create pca class
    PCA pca(featuresTrainingPCA, Mat(), CV_PCA_DATA_AS_ROW, 1);
    
    //Create vector to hold 72*1 projected features of training
    Mat trainingProjected_PCA(72,1,CV_64F);
    pca.project(featuresTrainingPCA,trainingProjected_PCA);
    
    //Create vector to hold 24*1 projected features of testing
    Mat testingProjected_PCA(24,1,CV_64F);
    pca.project(featuresTestingPCA,testingProjected_PCA);
    
    Mat newTrainingFeatures_PCA;
    trainingProjected_PCA.convertTo(newTrainingFeatures_PCA, CV_64F);
    
    Mat newTestingFeatures_PCA;
    testingProjected_PCA.convertTo(newTestingFeatures_PCA, CV_64F);
    
    //for(int i=0; i<24; i++)
      //  cout << newTestingFeatures_PCA.at<double>(i,0) << "\t"<< endl;
    
    /* Mahalanobis Distance for PCA */
    
    double reducedTrainingGrass[36][1];
    double reducedTrainingStraw[36][1];
    double reducedData[96][1];
    
    //Two separate classes for mean and variance calculation
    for (int i = 0; i < 36; i++)//Grass
        reducedTrainingGrass[i][0] = newTrainingFeatures_PCA.at<double>(i,0);
    
    int index = 0;
    for (int i = 36; i < 72; i++)//Straw
    {
        reducedTrainingStraw[index][0] = newTrainingFeatures_PCA.at<double>(i,0);
        //cout << reducedTrainingStraw[index][0]<<endl;
        index = index + 1;
        
    }
    
    //All the reduced data i.e training and testing
    
    for (int i = 0; i < 24; i++)//Unlabelled testing
        reducedData[i][0] = newTestingFeatures_PCA.at<double>(i,0);
    
    index = 0;//grass
    for (int i = 24; i < 60; i++)
    {
        reducedData[i][0] = reducedTrainingGrass[index][0];
        index = index + 1;
    }
    
    index = 0;//straw
    for (int i = 60; i < 96; i++)
    {
        reducedData[i][0] = reducedTrainingStraw[index][0];
        index = index + 1;
    }
    
    
    //Calculate mean and variance for grass and straw
    double sum = 0;
    double meanGrass;
    double meanStraw;
    double varianceGrass;
    double varianceStraw;
    //GRASS
    for (int i = 0; i < 36; i++)
        sum = sum + reducedTrainingGrass[i][0];
    
    meanGrass = sum / 36;
    //cout << meanGrass<<endl;
    sum = 0;
    for (int i = 0; i < 36; i++)
    {
        difference = (reducedTrainingGrass[i][0] - meanGrass)*(reducedTrainingGrass[i][0] - meanGrass);
        sum = sum + difference;
    }
    varianceGrass = sum / 36;
    
    //STRAW
    sum = 0;
    for (int i = 0; i < 36; i++)
        sum = sum + reducedTrainingStraw[i][0];
    
    meanStraw = sum / 36;
    //cout << meanStraw << endl;
    sum = 0;
    for (int i = 0; i < 36; i++)
    {
        difference = (reducedTrainingStraw[i][0] - meanStraw)*(reducedTrainingStraw[i][0] - meanStraw);
        sum = sum + difference;
    }
    varianceStraw = sum / 36;
    
    //Calculate distance from both the class means
    
    double distanceFromGrass[96];
    double distanceFromStraw[96];
    int newLabelsPCA[96];
    for ( int i = 0; i < 96; i++)
    {
        difference = (reducedData[i][0] - meanGrass)*(reducedData[i][0] - meanGrass);
        distanceFromGrass[i] = sqrt(double(difference) / double(varianceGrass));
    }
    
    for ( int i = 0; i < 96; i++)
    {
        difference = (reducedData[i][0] - meanStraw)*(reducedData[i][0] - meanStraw);
        distanceFromStraw[i] = sqrt(double(difference) / double(varianceStraw));
    }
    
    for ( int i = 0; i < 96; i++)
    {
        if (distanceFromGrass[i] < distanceFromStraw[i])
        {
            newLabelsPCA[i] = 1;//Assign it to class 1 of grass
        }
        else
            newLabelsPCA[i] = 2;//Assign it to class 2 of straw
        
        //cout << newLabelsPCA[i] << endl;
    }
    
    //Error For training data
    correctlyTested = 0;
    correctlyTrained = 0;
    for (int imageNumber = 24; imageNumber < 96; imageNumber++)
    {
        if (trueLabel[imageNumber] == newLabelsPCA[imageNumber])
        {
            correctlyTrained = correctlyTrained + 1;
        }
    }
    
    errorTraining = (double(72 - correctlyTrained) / double(72)) * 100; //total 72 training images
    
    //Error for Test data
    
    for (int imageNumber = 0; imageNumber < 24; imageNumber++)
    {
        if (trueLabel[imageNumber] == newLabelsPCA[imageNumber])
        {
            correctlyTested = correctlyTested + 1;
        }
    }
    
    errorTesting = (double(24 - correctlyTested) / double(24)) * 100; //Total 24 unknown images
    
    cout << "error for training data using PCA is : " << errorTraining << endl;
    cout << "error for testing data using PCA is : " << errorTesting << endl;
    cout << "Please run the MATLAB code to get the training and testing error using LDA" << endl;
    
    
    

    return 0;
}