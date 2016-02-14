//NAME: Amruta Kulkarni
//USC ID: 6914970827
//USC Email: arkulkar@usc.edu
//Submission date: 11 Oct 2015

//Problem 1B, part 1,2
//This code performs multi-class classification by using one-vs-all method. It classifies grass, straw, leather and sand images using the minimum distance to class means classifier.
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
    char *argv[] = //For all 192 images
    {
    
"grass_01.raw","grass_02.raw","grass_03.raw","grass_04.raw","grass_05.raw","grass_06.raw","grass_07.raw",
"grass_08.raw","grass_09.raw","grass_10.raw","grass_11.raw","grass_12.raw","grass_13.raw","grass_14.raw",
"grass_15.raw","grass_16.raw","grass_17.raw","grass_18.raw","grass_19.raw","grass_20.raw","grass_21.raw",
"grass_22.raw","grass_23.raw","grass_24.raw","grass_25.raw","grass_26.raw","grass_27.raw","grass_28.raw",
"grass_29.raw","grass_30.raw","grass_31.raw","grass_32.raw","grass_33.raw","grass_34.raw","grass_35.raw",
"grass_36.raw","grass_37.raw","grass_38.raw","grass_39.raw","grass_40.raw","grass_41.raw","grass_42.raw",
"grass_43.raw","grass_44.raw","grass_45.raw","grass_46.raw","grass_47.raw","grass_48.raw",
        
        
"straw_01.raw","straw_02.raw","straw_03.raw","straw_04.raw","straw_05.raw","straw_06.raw","straw_07.raw",
"straw_08.raw","straw_09.raw","straw_10.raw","straw_11.raw","straw_12.raw","straw_13.raw","straw_14.raw",
"straw_15.raw","straw_16.raw","straw_17.raw","straw_18.raw","straw_19.raw","straw_20.raw","straw_21.raw",
"straw_22.raw","straw_23.raw","straw_24.raw","straw_25.raw","straw_26.raw","straw_27.raw","straw_28.raw",
"straw_29.raw","straw_30.raw","straw_31.raw","straw_32.raw","straw_33.raw","straw_34.raw","straw_35.raw",
"straw_36.raw","straw_37.raw","straw_38.raw","straw_39.raw","straw_40.raw","straw_41.raw","straw_42.raw",
"straw_43.raw","straw_44.raw","straw_45.raw","straw_46.raw","straw_47.raw","straw_48.raw",
        
        
"leather_01.raw","leather_02.raw","leather_03.raw","leather_04.raw","leather_05.raw","leather_06.raw","leather_07.raw",
"leather_08.raw","leather_09.raw","leather_10.raw","leather_11.raw","leather_12.raw","leather_13.raw","leather_14.raw",
"leather_15.raw","leather_16.raw","leather_17.raw","leather_18.raw","leather_19.raw","leather_20.raw","leather_21.raw",
"leather_22.raw","leather_23.raw","leather_24.raw","leather_25.raw","leather_26.raw","leather_27.raw","leather_28.raw",
"leather_29.raw","leather_30.raw","leather_31.raw","leather_32.raw","leather_33.raw","leather_34.raw","leather_35.raw",
"leather_36.raw","leather_37.raw","leather_38.raw","leather_39.raw","leather_40.raw","leather_41.raw","leather_42.raw",
"leather_43.raw","leather_44.raw","leather_45.raw","leather_46.raw","leather_47.raw","leather_48.raw",
        
        
"sand_01.raw","sand_02.raw","sand_03.raw","sand_04.raw","sand_05.raw","sand_06.raw","sand_07.raw",
"sand_08.raw","sand_09.raw","sand_10.raw","sand_11.raw","sand_12.raw","sand_13.raw","sand_14.raw",
"sand_15.raw","sand_16.raw","sand_17.raw","sand_18.raw","sand_19.raw","sand_20.raw","sand_21.raw",
"sand_22.raw","sand_23.raw","sand_24.raw","sand_25.raw","sand_26.raw","sand_27.raw","sand_28.raw",
"sand_29.raw","sand_30.raw","sand_31.raw","sand_32.raw","sand_33.raw","sand_34.raw","sand_35.raw",
"sand_36.raw","sand_37.raw","sand_38.raw","sand_39.raw","sand_40.raw","sand_41.raw","sand_42.raw",
"sand_43.raw","sand_44.raw","sand_45.raw","sand_46.raw","sand_47.raw","sand_48.raw"
        
    };
    
    FILE *file;
    double energy[192][25];
    for (int imageNumber = 0; imageNumber < 192; imageNumber++)
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
        
        int kernelProduct1[5][5],kernelProduct2[5][5],kernelProduct3[5][5],kernelProduct4[5][5],kernelProduct5[5][5],kernelProduct6[5][5],
        kernelProduct7[5][5],kernelProduct8[5][5],kernelProduct9[5][5],kernelProduct10[5][5],kernelProduct11[5][5],kernelProduct12[5][5],
        kernelProduct13[5][5],kernelProduct14[5][5],kernelProduct15[5][5],kernelProduct16[5][5],kernelProduct17[5][5],kernelProduct18[5][5],
        kernelProduct19[5][5],kernelProduct20[5][5],kernelProduct21[5][5],kernelProduct22[5][5],kernelProduct23[5][5],kernelProduct24[5][5],
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
        
        // Calculate 25 filtered output images 
        int imageWindow[N][N];
        double convolution;
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
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
                            double product = imageWindow[i][j] * filterBank[i][j][featureNumber];
                            convolution = convolution + product;
                        }
                    }
                    filteredImages[row][column][featureNumber] = convolution;
                }
            }
        }
        
        /* Feature averaging */
        
        
        double energySum;
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            energySum = 0;
            for (int row = halfLength; row < extendedHeight - halfLength; row++)//Get rid of image extensions
            {
                for (int column = halfLength; column < extendedWidth - halfLength; column++)
                {
                    energySum = energySum + (abs(filteredImages[row][column][featureNumber]) * abs(filteredImages[row][column][featureNumber]));
                }
            }
            energy[imageNumber][featureNumber] = energySum/(height * width);
        }
    }//Repeat for all 192 images

    /* Separate Training and testing data for every class */
    
    //For GRASS
    //TRAINING
    double trainingGrass[72][25];//0 to 36 from grass
    for (int imageNumber = 0; imageNumber < 36; imageNumber++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            trainingGrass[imageNumber][featureNumber] = energy[imageNumber][featureNumber];//Fill up the first 36 samples from grass itself
        }
    }
    int imageNumber = 84; //84 to 95 from straw
    for (int fromStraw = 36; fromStraw < 48; fromStraw++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            trainingGrass[fromStraw][featureNumber] = energy[imageNumber][featureNumber];//Take the next 12 from straw
        }
        imageNumber = imageNumber + 1;
    }
    imageNumber = 132; //132 to 143 from Leather
    for (int fromLeather = 48; fromLeather < 60; fromLeather++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            trainingGrass[fromLeather][featureNumber] = energy[imageNumber][featureNumber];//Take the next 12 from Leather
        }
        imageNumber = imageNumber + 1;
    }
   imageNumber = 180; //180 to 191 from sand
    for (int fromSand = 60; fromSand < 72; fromSand++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            trainingGrass[fromSand][featureNumber] = energy[imageNumber][featureNumber];//Take the next 12 from Sand
        }
        imageNumber = imageNumber + 1;
    }
    //TESTING
    double testingGrass[24][25];//First 12 from grass and then 4 each from straw, sand and leather
    imageNumber = 36;//36 to 47 from grass
    for (int fromGrass = 0; fromGrass < 12; fromGrass++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            testingGrass[fromGrass][featureNumber] = energy[imageNumber][featureNumber];
        }
        imageNumber = imageNumber + 1;
    }
    imageNumber = 48;//48 to 51 from straw
    for (int fromStraw = 12; fromStraw < 16; fromStraw++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            testingGrass[fromStraw][featureNumber] = energy[imageNumber][featureNumber];
        }
        imageNumber = imageNumber + 1;
    }
    imageNumber = 96;//96 to 99 from leather
    for (int fromLeather = 16; fromLeather < 20; fromLeather++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            testingGrass[fromLeather][featureNumber] = energy[imageNumber][featureNumber];
        }
        imageNumber = imageNumber + 1;
    }
    imageNumber = 144;//144 to 147 from sand
    for (int fromSand = 20; fromSand < 24; fromSand++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            testingGrass[fromSand][featureNumber] = energy[imageNumber][featureNumber];
        }
        imageNumber = imageNumber + 1;
    }
    //POST PROCEESING OF GRASS USING NORMALIZATION
    double copyFeature[72];
    double min,max,difference;
    int size = sizeof(copyFeature)/sizeof(copyFeature[0]);
    
    for (int featureNumber = 0; featureNumber < 25; featureNumber++)
    {
        for (int imageNumber = 0; imageNumber < 72; imageNumber++)
        {
            copyFeature[imageNumber] = trainingGrass[imageNumber][featureNumber];
        }
        sort (copyFeature, copyFeature + size);
        min = copyFeature[0];
        max = copyFeature[71];
        difference = max - min;
        for (int imageNumber = 0; imageNumber < 72; imageNumber++)
        {
            trainingGrass[imageNumber][featureNumber] = (trainingGrass[imageNumber][featureNumber] - min) / difference;//every training feature will get normalised
        }
        for (int imageNumber = 0; imageNumber < 24; imageNumber++)
        {
            testingGrass[imageNumber][featureNumber] = (testingGrass[imageNumber][featureNumber] - min) / difference;//every feature will get normalised
        }
    }

    //For STRAW
    //TRAINING
    double trainingStraw[72][25];
    imageNumber = 48;// 48 to 83 from straw
    for (int fromStraw = 0; fromStraw < 36; fromStraw++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            trainingStraw[fromStraw][featureNumber] = energy[imageNumber][featureNumber];//Fill up the first 36 samples from straw itself
        }
        imageNumber = imageNumber + 1;
    }
    imageNumber = 36;//36 to 47 from grass
    for (int fromGrass = 36; fromGrass < 48; fromGrass++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            trainingStraw[fromGrass][featureNumber] = energy[imageNumber][featureNumber];//Next 12 from grass
        }
        imageNumber = imageNumber + 1;
    }
    imageNumber = 132;//132 to 143 from leather
    for (int fromLeather = 48; fromLeather < 60; fromLeather++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            trainingStraw[fromLeather][featureNumber] = energy[imageNumber][featureNumber];//Next 12 from Leather
        }
        imageNumber = imageNumber + 1;
    }
    imageNumber = 180;//180 to 191 from sand
    for (int fromSand = 60; fromSand < 72; fromSand++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            trainingStraw[fromSand][featureNumber] = energy[imageNumber][featureNumber];//Next 12 from sand
        }
        imageNumber = imageNumber + 1;
    }
    //TESTING
    double testingStraw[24][25];
    imageNumber = 84;//84 to 95 of straw
    for (int fromStraw = 0; fromStraw < 12; fromStraw++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            testingStraw[fromStraw][featureNumber] = energy[imageNumber][featureNumber];
        }
        imageNumber = imageNumber + 1;
    }
    imageNumber = 0;//0 to 3 from grass
    for (int fromGrass = 12; fromGrass < 16; fromGrass++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            testingStraw[fromGrass][featureNumber] = energy[imageNumber][featureNumber];
        }
        imageNumber = imageNumber + 1;
    }
    imageNumber = 96;//96 to 99 from leather
    for (int fromLeather = 16; fromLeather < 20; fromLeather++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            testingStraw[fromLeather][featureNumber] = energy[imageNumber][featureNumber];
        }
        imageNumber = imageNumber + 1;
    }
    imageNumber = 144;//144 to 147 from sand
    for (int fromSand = 20; fromSand < 24; fromSand++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            testingStraw[fromSand][featureNumber] = energy[imageNumber][featureNumber];
        }
        imageNumber = imageNumber + 1;
    }
    //POST PROCESSING OF STRAW BY NORMALIZATION
    for (int featureNumber = 0; featureNumber < 25; featureNumber++)
    {
        for (int imageNumber = 0; imageNumber < 72; imageNumber++)
        {
            copyFeature[imageNumber] = trainingStraw[imageNumber][featureNumber];
        }
        sort (copyFeature, copyFeature + size);
        min = copyFeature[0];
        max = copyFeature[71];
        difference = max - min;
        for (int imageNumber = 0; imageNumber < 72; imageNumber++)
        {
            trainingStraw[imageNumber][featureNumber] = (trainingStraw[imageNumber][featureNumber] - min) / difference;//every training feature will get normalised
        }
        for (int imageNumber = 0; imageNumber < 24; imageNumber++)
        {
            testingStraw[imageNumber][featureNumber] = (testingStraw[imageNumber][featureNumber] - min) / difference;//every feature will get normalised
        }
    }

    //For LEATHER
    //TRAINING
    double trainingLeather[72][25];
    imageNumber = 96;//96 to 131 from leather
    for (int fromLeather = 0; fromLeather < 36; fromLeather++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            trainingLeather[fromLeather][featureNumber] = energy[imageNumber][featureNumber];//Fill up the first 36 samples from leather itself
        }
        imageNumber = imageNumber + 1;
    }
    imageNumber = 36;//36 to 47 from grass
    for (int fromGrass = 36; fromGrass < 48; fromGrass++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            trainingLeather[fromGrass][featureNumber] = energy[imageNumber][featureNumber];//Next 12 from grass
        }
        imageNumber = imageNumber + 1;
    }
    imageNumber = 84; //84 to 95 from straw
    for (int fromStraw = 48; fromStraw < 60; fromStraw++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            trainingLeather[fromStraw][featureNumber] = energy[imageNumber][featureNumber];//Take the next 12 from straw
        }
        imageNumber = imageNumber + 1;
    }
    imageNumber = 180;//180 to 191 from sand
    for (int fromSand = 60; fromSand < 72; fromSand++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            trainingLeather[fromSand][featureNumber] = energy[imageNumber][featureNumber];//Next 12 from sand
        }
        imageNumber = imageNumber + 1;
    }
    //TESTING
    double testingLeather[24][25];
    imageNumber = 132;//132 to 143 from leather
    for (int fromLeather = 0; fromLeather < 12; fromLeather++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            testingLeather[fromLeather][featureNumber] = energy[imageNumber][featureNumber];
        }
        imageNumber = imageNumber + 1;
    }
    imageNumber = 0;//0 to 3 from grass
    for (int fromGrass = 12; fromGrass < 16; fromGrass++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            testingLeather[fromGrass][featureNumber] = energy[imageNumber][featureNumber];
        }
        imageNumber = imageNumber + 1;
    }
    imageNumber = 48;//48 to 51 from straw
    for (int fromStraw = 16; fromStraw < 20; fromStraw++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            testingLeather[fromStraw][featureNumber] = energy[imageNumber][featureNumber];
        }
        imageNumber = imageNumber + 1;
    }
    imageNumber = 144;//144 to 147 from sand
    for (int fromSand = 20; fromSand < 24; fromSand++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            testingLeather[fromSand][featureNumber] = energy[imageNumber][featureNumber];
        }
        imageNumber = imageNumber + 1;
    }
    //POST PROCESSING OF LEATHER BY NORMALIZATION
    for (int featureNumber = 0; featureNumber < 25; featureNumber++)
    {
        for (int imageNumber = 0; imageNumber < 72; imageNumber++)
        {
            copyFeature[imageNumber] = trainingLeather[imageNumber][featureNumber];
        }
        sort (copyFeature, copyFeature + size);
        min = copyFeature[0];
        max = copyFeature[71];
        difference = max - min;
        for (int imageNumber = 0; imageNumber < 72; imageNumber++)
        {
            trainingLeather[imageNumber][featureNumber] = (trainingLeather[imageNumber][featureNumber] - min) / difference;//every training feature will get normalised
        }
        for (int imageNumber = 0; imageNumber < 24; imageNumber++)
        {
            testingLeather[imageNumber][featureNumber] = (testingLeather[imageNumber][featureNumber] - min) / difference;//every feature will get normalised
        }
    }

    //For SAND
    //TRAINING
    double trainingSand[72][25];
    imageNumber = 144;//144 to 179 from sand
    for (int fromSand = 0; fromSand < 36; fromSand++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            trainingSand[fromSand][featureNumber] = energy[imageNumber][featureNumber];//fill up the first 36 samples from sand itself
        }
        imageNumber = imageNumber + 1;
    }
    imageNumber = 36;//36 to 47 from grass
    for (int fromGrass = 36; fromGrass < 48; fromGrass++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            trainingSand[fromGrass][featureNumber] = energy[imageNumber][featureNumber];//Next 12 from grass
        }
        imageNumber = imageNumber + 1;
    }
    imageNumber = 84; //84 to 95 from straw
    for (int fromStraw = 48; fromStraw < 60; fromStraw++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            trainingSand[fromStraw][featureNumber] = energy[imageNumber][featureNumber];//Take the next 12 from straw
        }
        imageNumber = imageNumber + 1;
    }
    imageNumber = 132;//132 to 143 from leather
    for (int fromLeather = 60; fromLeather < 72; fromLeather++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            trainingSand[fromLeather][featureNumber] = energy[imageNumber][featureNumber];//Next 12 from Leather
        }
        imageNumber = imageNumber + 1;
    }
    //TESTING
    double testingSand[24][25];
    imageNumber = 180;//180 to 191 from sand
    for (int fromSand = 0; fromSand < 12; fromSand++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            testingSand[fromSand][featureNumber] = energy[imageNumber][featureNumber];
        }
        imageNumber = imageNumber + 1;
    }
    imageNumber = 0;//0 to 3 from grass
    for (int fromGrass = 12; fromGrass < 16; fromGrass++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            testingSand[fromGrass][featureNumber] = energy[imageNumber][featureNumber];
        }
        imageNumber = imageNumber + 1;
    }
    imageNumber = 48;//48 to 51 from straw
    for (int fromStraw = 16; fromStraw < 20; fromStraw++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            testingSand[fromStraw][featureNumber] = energy[imageNumber][featureNumber];
        }
        imageNumber = imageNumber + 1;
    }
    imageNumber = 96;//96 to 99 from leather
    for (int fromLeather = 20; fromLeather < 24; fromLeather++)
    {
        for (int featureNumber = 0; featureNumber < 25; featureNumber++)
        {
            testingSand[fromLeather][featureNumber] = energy[imageNumber][featureNumber];
        }
        imageNumber = imageNumber + 1;
    }
    //POST PROCESSING OF SAND BY NORMALIZATION
    for (int featureNumber = 0; featureNumber < 25; featureNumber++)
    {
        for (int imageNumber = 0; imageNumber < 72; imageNumber++)
        {
            copyFeature[imageNumber] = trainingSand[imageNumber][featureNumber];
        }
        sort (copyFeature, copyFeature + size);
        min = copyFeature[0];
        max = copyFeature[71];
        difference = max - min;
        for (int imageNumber = 0; imageNumber < 72; imageNumber++)
        {
            trainingSand[imageNumber][featureNumber] = (trainingSand[imageNumber][featureNumber] - min) / difference;//every training feature will get normalised
        }
        for (int imageNumber = 0; imageNumber < 24; imageNumber++)
        {
            testingSand[imageNumber][featureNumber] = (testingSand[imageNumber][featureNumber] - min) / difference;//every feature will get normalised
        }
    }

    /* Principal Component Analysis */
    
    //FOR GRASS
    double reducedTrainingGrass[72][3];
    double reducedTestingGrass[24][3];
    
    Mat featuresTrainingGrass = Mat(72,25,CV_64F,trainingGrass);
    Mat featuresTestingGrass = Mat(24,25,CV_64F,testingGrass);
    
    //Create pca class
    PCA pcaGrass(featuresTrainingGrass, Mat(), CV_PCA_DATA_AS_ROW, 3);
    
    //Create vector to hold 72*3 projected features of training
    Mat trainingProjectedGrass(72,3,CV_64F);
    pcaGrass.project(featuresTrainingGrass,trainingProjectedGrass);
    
    //Create vector to hold 24*3 projected features of testing
    Mat testingProjectedGrass(24,3,CV_64F);
    pcaGrass.project(featuresTestingGrass,testingProjectedGrass);
    
    Mat newTrainingFeaturesGrass;
    trainingProjectedGrass.convertTo(newTrainingFeaturesGrass, CV_64F);
    
    Mat newTestingFeaturesGrass;
    testingProjectedGrass.convertTo(newTestingFeaturesGrass, CV_64F);
    
    //cout << "training set for grass is"<<endl;
    for (int i = 0; i < 72; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            reducedTrainingGrass[i][j] = newTrainingFeaturesGrass.at<double>(i,j);
            //cout << reducedTrainingGrass[i][j] << "\t";
        }
        //cout << endl;
    }
    //cout << endl << "testing set for grass is"<<endl;
  
    for (int i = 0; i < 24; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            reducedTestingGrass[i][j] = newTestingFeaturesGrass.at<double>(i,j);
            //cout << reducedTestingGrass[i][j] << "\t";
        }
       // cout << endl;
    }
    
    //FOR STRAW
    double reducedTrainingStraw[72][3];
    double reducedTestingStraw[24][3];
    
    Mat featuresTrainingStraw = Mat(72,25,CV_64F,trainingStraw);
    Mat featuresTestingStraw = Mat(24,25,CV_64F,testingStraw);
    
    //Create pca class
    PCA pcaStraw(featuresTrainingStraw, Mat(), CV_PCA_DATA_AS_ROW, 3);
    
    //Create vector to hold 72*3 projected features of training
    Mat trainingProjectedStraw(72,3,CV_64F);
    pcaStraw.project(featuresTrainingStraw,trainingProjectedStraw);
    
    //Create vector to hold 24*3 projected features of testing
    Mat testingProjectedStraw(24,3,CV_64F);
    pcaStraw.project(featuresTestingStraw,testingProjectedStraw);
    
    Mat newTrainingFeaturesStraw;
    trainingProjectedStraw.convertTo(newTrainingFeaturesStraw, CV_64F);
    
    Mat newTestingFeaturesStraw;
    testingProjectedStraw.convertTo(newTestingFeaturesStraw, CV_64F);
    
    //cout << "training set for straw is"<<endl;
    for (int i = 0; i < 72; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            reducedTrainingStraw[i][j] = newTrainingFeaturesStraw.at<double>(i,j);
            //cout << reducedTrainingStraw[i][j] << "\t";
        }
        //cout << endl;
    }
    //cout << endl << "testing set for straw is"<<endl;
    for (int i = 0; i < 24; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            reducedTestingStraw[i][j] = newTestingFeaturesStraw.at<double>(i,j);
            //cout << reducedTestingStraw[i][j] << "\t";
        }
        //cout << endl;
    }
    
    //FOR LEATHER
    double reducedTrainingLeather[72][3];
    double reducedTestingLeather[24][3];
    
    Mat featuresTrainingLeather = Mat(72,25,CV_64F,trainingLeather);
    Mat featuresTestingLeather = Mat(24,25,CV_64F,testingLeather);
    
    //Create pca class
    PCA pcaLeather(featuresTrainingLeather, Mat(), CV_PCA_DATA_AS_ROW, 3);
    
    //Create vector to hold 72*3 projected features of training
    Mat trainingProjectedLeather(72,3,CV_64F);
    pcaLeather.project(featuresTrainingLeather,trainingProjectedLeather);
    
    //Create vector to hold 24*3 projected features of testing
    Mat testingProjectedLeather(24,3,CV_64F);
    pcaLeather.project(featuresTestingLeather,testingProjectedLeather);
    
    Mat newTrainingFeaturesLeather;
    trainingProjectedLeather.convertTo(newTrainingFeaturesLeather, CV_64F);
    
    Mat newTestingFeaturesLeather;
    testingProjectedLeather.convertTo(newTestingFeaturesLeather, CV_64F);
    //cout << "training set for leather is"<<endl;
    for (int i = 0; i < 72; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            reducedTrainingLeather[i][j] = newTrainingFeaturesLeather.at<double>(i,j);
            //cout << reducedTrainingLeather[i][j] << "\t";
        }
        //cout << endl;
    }
    //cout << endl << "testing set for leather is"<<endl;
    for (int i = 0; i < 24; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            reducedTestingLeather[i][j] = newTestingFeaturesLeather.at<double>(i,j);
            //cout << reducedTestingLeather[i][j] << "\t";
        }
        //cout << endl;
    }
    
    //FOR SAND
    double reducedTrainingSand[72][3];
    double reducedTestingSand[24][3];
    
    Mat featuresTrainingSand = Mat(72,25,CV_64F,trainingSand);
    Mat featuresTestingSand = Mat(24,25,CV_64F,testingSand);
    
    //Create pca class
    PCA pcaSand(featuresTrainingSand, Mat(), CV_PCA_DATA_AS_ROW, 3);
    
    //Create vector to hold 72*3 projected features of training
    Mat trainingProjectedSand(72,3,CV_64F);
    pcaSand.project(featuresTrainingSand,trainingProjectedSand);
    
    //Create vector to hold 12*3 projected features of testing
    Mat testingProjectedSand(24,3,CV_64F);
    pcaSand.project(featuresTestingSand,testingProjectedSand);
    
    Mat newTrainingFeaturesSand;
    trainingProjectedSand.convertTo(newTrainingFeaturesSand, CV_64F);
    
    Mat newTestingFeaturesSand;
    testingProjectedSand.convertTo(newTestingFeaturesSand, CV_64F);
    //cout << "training set for sand is"<<endl;
    for (int i = 0; i < 72; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            reducedTrainingSand[i][j] = newTrainingFeaturesSand.at<double>(i,j);
            //cout << reducedTrainingSand[i][j] << "\t";
        }
        //cout << endl;
    }
    //cout << endl << "testing set for sand is"<<endl;
    for (int i = 0; i < 24; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            reducedTestingSand[i][j] = newTestingFeaturesSand.at<double>(i,j);
            //cout << reducedTestingSand[i][j] << "\t";
        }
        //cout << endl;
    }
    
    // Calculate the mean and variance for all four classes
    
    double sumGrass, sumStraw, sumLeather, sumSand;
    
    double meanGrass[3];
    double varianceGrass[3];
    
    double meanNONGrass[3];
    double varianceNONGrass[3];
    
    double meanStraw[3];
    double varianceStraw[3];
    
    double meanNONStraw[3];
    double varianceNONStraw[3];
    
    double meanLeather[3];
    double varianceLeather[3];
    
    double meanNONLeather[3];
    double varianceNONLeather[3];
    
    double meanSand[3];
    double varianceSand[3];
    
    double meanNONSand[3];
    double varianceNONSand[3];
    
    for (int featureNumber = 0; featureNumber < 3; featureNumber++)
    {
        sumGrass = 0;
        sumStraw = 0;
        sumLeather = 0;
        sumSand = 0;
        
        //GRASS
        for (int imageNumber = 0; imageNumber < 36; imageNumber++)
        {
            sumGrass = sumGrass + reducedTrainingGrass[imageNumber][featureNumber];
        }
        meanGrass[featureNumber] = sumGrass / 36;
        
        sumGrass = 0;
        for (int imageNumber = 0; imageNumber < 36; imageNumber++)
        {
            difference = (reducedTrainingGrass[imageNumber][featureNumber] - meanGrass[featureNumber])*(reducedTrainingGrass[imageNumber][featureNumber] - meanGrass[featureNumber]);
            sumGrass = sumGrass + difference;
        }
        varianceGrass[featureNumber] = sumGrass/36;
        //NON-GRASS
        sumGrass = 0;
        for (int imageNumber = 36; imageNumber < 72; imageNumber++)
        {
            sumGrass = sumGrass + reducedTrainingGrass[imageNumber][featureNumber];
        }
        meanNONGrass[featureNumber] = sumGrass / 36;
        
        sumGrass = 0;
        for (int imageNumber = 36; imageNumber < 72; imageNumber++)
        {
            difference = (reducedTrainingGrass[imageNumber][featureNumber] - meanNONGrass[featureNumber])*(reducedTrainingGrass[imageNumber][featureNumber] - meanNONGrass[featureNumber]);
            sumGrass = sumGrass + difference;
        }
        varianceNONGrass[featureNumber] = sumGrass/36;
        
        //STRAW
        for (int imageNumber = 0; imageNumber < 36; imageNumber++)
        {
            sumStraw = sumStraw + reducedTrainingStraw[imageNumber][featureNumber];
        }
        meanStraw[featureNumber] = sumStraw / 36;
        
        sumStraw = 0;
        for (int imageNumber = 0; imageNumber < 36; imageNumber++)
        {
            difference = (reducedTrainingStraw[imageNumber][featureNumber] - meanStraw[featureNumber])*(reducedTrainingStraw[imageNumber][featureNumber] - meanStraw[featureNumber]);
            sumStraw = sumStraw + difference;
        }
        varianceStraw[featureNumber] = sumStraw/36;
        //NON-STRAW
        sumStraw = 0;
        for (int imageNumber = 36; imageNumber < 72; imageNumber++)
        {
            sumStraw = sumStraw + reducedTrainingStraw[imageNumber][featureNumber];
        }
        meanNONStraw[featureNumber] = sumStraw / 36;
        
        sumStraw = 0;
        for (int imageNumber = 36; imageNumber < 72; imageNumber++)
        {
            difference = (reducedTrainingStraw[imageNumber][featureNumber] - meanNONStraw[featureNumber])*(reducedTrainingStraw[imageNumber][featureNumber] - meanNONStraw[featureNumber]);
            sumStraw = sumStraw + difference;
        }
        varianceNONStraw[featureNumber] = sumStraw/36;
        
        //LEATHER
        for (int imageNumber = 0; imageNumber < 36; imageNumber++)
        {
            sumLeather = sumLeather + reducedTrainingLeather[imageNumber][featureNumber];
        }
        meanLeather[featureNumber] = sumLeather / 36;
        
        sumLeather = 0;
        for (int imageNumber = 0; imageNumber < 36; imageNumber++)
        {
            difference = (reducedTrainingLeather[imageNumber][featureNumber] - meanLeather[featureNumber])*(reducedTrainingLeather[imageNumber][featureNumber] - meanLeather[featureNumber]);
            sumLeather = sumLeather + difference;
        }
        varianceLeather[featureNumber] = sumLeather/36;
        //NON-LEATHER
        sumLeather = 0;
        for (int imageNumber = 36; imageNumber < 72; imageNumber++)
        {
            sumLeather = sumLeather + reducedTrainingLeather[imageNumber][featureNumber];
        }
        meanNONLeather[featureNumber] = sumLeather / 36;
        
        sumLeather = 0;
        for (int imageNumber = 36; imageNumber < 72; imageNumber++)
        {
            difference = (reducedTrainingLeather[imageNumber][featureNumber] - meanNONLeather[featureNumber])*(reducedTrainingLeather[imageNumber][featureNumber] - meanNONLeather[featureNumber]);
            sumLeather = sumLeather + difference;
        }
        varianceNONLeather[featureNumber] = sumLeather/36;
        
        //SAND
        for (int imageNumber = 0; imageNumber < 36; imageNumber++)
        {
            sumSand = sumSand + reducedTrainingSand[imageNumber][featureNumber];
        }
        meanSand[featureNumber] = sumSand / 36;
        
        sumSand = 0;
        for (int imageNumber = 0; imageNumber < 36; imageNumber++)
        {
            difference = (reducedTrainingSand[imageNumber][featureNumber] - meanSand[featureNumber])*(reducedTrainingSand[imageNumber][featureNumber] - meanSand[featureNumber]);
            sumSand = sumSand + difference;
        }
        varianceSand[featureNumber] = sumSand/36;
        //NON-SAND
        sumSand = 0;
        for (int imageNumber = 36; imageNumber < 72; imageNumber++)
        {
            sumSand = sumSand + reducedTrainingSand[imageNumber][featureNumber];
        }
        meanNONSand[featureNumber] = sumSand / 36;
        
        sumSand = 0;
        for (int imageNumber = 36; imageNumber < 72; imageNumber++)
        {
            difference = (reducedTrainingSand[imageNumber][featureNumber] - meanNONSand[featureNumber])*(reducedTrainingSand[imageNumber][featureNumber] - meanNONSand[featureNumber]);
            sumSand = sumSand + difference;
        }
        varianceNONSand[featureNumber] = sumSand/36;
    }
    
    //Create Labels
    int trueLabelTraining[72];
    int trueLabelTesting[24];

    for (int i = 0; i < 36; i++)
        trueLabelTraining[i] = 1;//For eg. Grass
    for (int i = 36; i < 72; i++)
        trueLabelTraining[i] = -1;//Non-Grass
    
    for (int i = 0; i < 12; i++)
        trueLabelTesting[i] = 1;//For e.g. Grass
    for (int i = 12; i < 24; i++)
        trueLabelTesting[i] = -1;//Non-Grass
    
    int classifiedLabelsTraining[72];
    int classifiedLabelsTesting[24];
    
    //cout << endl << endl << endl << endl << endl;
    /* MINIMUM DISTANCE TO MEAN CLASSIFIER */
    
    double distanceFromClass[72];
    double distanceFromNONClass[72];
    float errorGrassTraining;
    float errorGrassTesting;
    float errorStrawTraining;
    float errorStrawTesting;
    float errorLeatherTraining;
    float errorLeatherTesting;
    float errorSandTraining;
    float errorSandTesting;
    
    //GRASS VS NON-GRASS
    
    //TRAINING
    for (int imageNumber = 0; imageNumber < 72; imageNumber++)
    {
        sumGrass = 0;//Grass
        for (int featureNumber = 0; featureNumber < 3; featureNumber++)
        {
            difference = (reducedTrainingGrass[imageNumber][featureNumber] - meanGrass[featureNumber])*(reducedTrainingGrass[imageNumber][featureNumber] - meanGrass[featureNumber]);
            sumGrass = sumGrass + (difference/varianceGrass[featureNumber]);
        }
        distanceFromClass[imageNumber] = sqrt(sumGrass);
        
        sumGrass = 0;//Non-Grass
        for (int featureNumber = 0; featureNumber < 3; featureNumber++)
        {
            difference = (reducedTrainingGrass[imageNumber][featureNumber] - meanNONGrass[featureNumber])*(reducedTrainingGrass[imageNumber][featureNumber] - meanNONGrass[featureNumber]);
            sumGrass = sumGrass + (difference/varianceNONGrass[featureNumber]);
        }
        distanceFromNONClass[imageNumber] = sqrt(sumGrass);
        
    }
    //Compare the distances and assign labels accordingly
    for (int i = 0; i < 72; i++)
    {
        if (distanceFromClass[i] < distanceFromNONClass[i])
            classifiedLabelsTraining[i] = 1;
        else
            classifiedLabelsTraining[i] = -1;
    }
    
    int correctClassification = 0;
    for (int i = 0; i < 72; i++)
    {
        if (trueLabelTraining[i] == classifiedLabelsTraining[i])
            correctClassification = correctClassification + 1;
    }
    errorGrassTraining = (double(72-correctClassification)/72) * 100;
    cout << "grass training error is " << errorGrassTraining << "%" << endl;
    
    //TESTING
    for (int imageNumber = 0; imageNumber < 24; imageNumber++)
    {
        sumGrass = 0;//Grass
        for (int featureNumber = 0; featureNumber < 3; featureNumber++)
        {
            difference = (reducedTestingGrass[imageNumber][featureNumber] - meanGrass[featureNumber])*(reducedTestingGrass[imageNumber][featureNumber] - meanGrass[featureNumber]);
            sumGrass = sumGrass + (difference/varianceGrass[featureNumber]);
        }
        distanceFromClass[imageNumber] = sqrt(sumGrass);
        
        sumGrass = 0;//Non-Grass
        for (int featureNumber = 0; featureNumber < 3; featureNumber++)
        {
            difference = (reducedTestingGrass[imageNumber][featureNumber] - meanNONGrass[featureNumber])*(reducedTestingGrass[imageNumber][featureNumber] - meanNONGrass[featureNumber]);
            sumGrass = sumGrass + (difference/varianceNONGrass[featureNumber]);
        }
        distanceFromNONClass[imageNumber] = sqrt(sumGrass);
        
    }
    //Compare the distances and assign labels accordingly
    for (int i = 0; i < 24; i++)
    {
        if (distanceFromClass[i] < distanceFromNONClass[i])
            classifiedLabelsTesting[i] = 1;
        else
            classifiedLabelsTesting[i] = -1;
    }
    
    correctClassification = 0;
    for (int i = 0; i < 24; i++)
    {
        if (trueLabelTesting[i] == classifiedLabelsTesting[i])
            correctClassification = correctClassification + 1;
    }
    errorGrassTesting = (double(24-correctClassification)/24) * 100;
    cout << "grass testing error is " << errorGrassTesting << "%" << endl;
    
    //STRAW VS NON-STRAW
    
    //TRAINING
    for (int imageNumber = 0; imageNumber < 72; imageNumber++)
    {
        sumStraw = 0;//Straw
        for (int featureNumber = 0; featureNumber < 3; featureNumber++)
        {
            difference = (reducedTrainingStraw[imageNumber][featureNumber] - meanStraw[featureNumber])*(reducedTrainingStraw[imageNumber][featureNumber] - meanStraw[featureNumber]);
            sumStraw = sumStraw + (difference/varianceStraw[featureNumber]);
        }
        distanceFromClass[imageNumber] = sqrt(sumStraw);
        
        sumStraw = 0;//Non-Straw
        for (int featureNumber = 0; featureNumber < 3; featureNumber++)
        {
            difference = (reducedTrainingStraw[imageNumber][featureNumber] - meanNONStraw[featureNumber])*(reducedTrainingStraw[imageNumber][featureNumber] - meanNONStraw[featureNumber]);
            sumStraw = sumStraw + (difference/varianceNONStraw[featureNumber]);
        }
        distanceFromNONClass[imageNumber] = sqrt(sumStraw);
        
    }
    //Compare the distances and assign labels accordingly
    for (int i = 0; i < 72; i++)
    {
        if (distanceFromClass[i] < distanceFromNONClass[i])
            classifiedLabelsTraining[i] = 1;
        else
            classifiedLabelsTraining[i] = -1;
    }
    
    correctClassification = 0;
    for (int i = 0; i < 72; i++)
    {
        if (trueLabelTraining[i] == classifiedLabelsTraining[i])
            correctClassification = correctClassification + 1;
    }
    errorStrawTraining = (double(72-correctClassification)/72) * 100;
    cout << "straw training error is " << errorStrawTraining << "%" << endl;
    //TESTING
    for (int imageNumber = 0; imageNumber < 24; imageNumber++)
    {
        sumStraw = 0;//Grass
        for (int featureNumber = 0; featureNumber < 3; featureNumber++)
        {
            difference = (reducedTestingStraw[imageNumber][featureNumber] - meanStraw[featureNumber])*(reducedTestingStraw[imageNumber][featureNumber] - meanStraw[featureNumber]);
            sumStraw = sumStraw + (difference/varianceStraw[featureNumber]);
        }
        distanceFromClass[imageNumber] = sqrt(sumStraw);
        
        sumStraw = 0;//Non-Grass
        for (int featureNumber = 0; featureNumber < 3; featureNumber++)
        {
            difference = (reducedTestingStraw[imageNumber][featureNumber] - meanNONStraw[featureNumber])*(reducedTestingStraw[imageNumber][featureNumber] - meanNONStraw[featureNumber]);
            sumStraw = sumStraw + (difference/varianceNONStraw[featureNumber]);
        }
        distanceFromNONClass[imageNumber] = sqrt(sumStraw);
        
    }
    //Compare the distances and assign labels accordingly
    for (int i = 0; i < 24; i++)
    {
        if (distanceFromClass[i] < distanceFromNONClass[i])
            classifiedLabelsTesting[i] = 1;
        else
            classifiedLabelsTesting[i] = -1;
    }
    
    correctClassification = 0;
    for (int i = 0; i < 24; i++)
    {
        if (trueLabelTesting[i] == classifiedLabelsTesting[i])
            correctClassification = correctClassification + 1;
    }
    errorStrawTesting = (double(24-correctClassification)/24) * 100;
    cout << "straw testing error is " << errorStrawTesting << "%" << endl;

    //LEATHER VS NON-LEATHER
    
    //TRAINING
    for (int imageNumber = 0; imageNumber < 72; imageNumber++)
    {
        sumLeather = 0;//Leather
        for (int featureNumber = 0; featureNumber < 3; featureNumber++)
        {
            difference = (reducedTrainingLeather[imageNumber][featureNumber] - meanLeather[featureNumber])*(reducedTrainingLeather[imageNumber][featureNumber] - meanLeather[featureNumber]);
            sumLeather = sumLeather + (difference/varianceLeather[featureNumber]);
        }
        distanceFromClass[imageNumber] = sqrt(sumLeather);
        
        sumLeather = 0;//Non-Leather
        for (int featureNumber = 0; featureNumber < 3; featureNumber++)
        {
            difference = (reducedTrainingLeather[imageNumber][featureNumber] - meanNONLeather[featureNumber])*(reducedTrainingLeather[imageNumber][featureNumber] - meanNONLeather[featureNumber]);
            sumLeather = sumLeather + (difference/varianceNONLeather[featureNumber]);
        }
        distanceFromNONClass[imageNumber] = sqrt(sumLeather);
        
    }
    //Compare the distances and assign labels accordingly
    for (int i = 0; i < 72; i++)
    {
        if (distanceFromClass[i] < distanceFromNONClass[i])
            classifiedLabelsTraining[i] = 1;
        else
            classifiedLabelsTraining[i] = -1;
    }
    
    correctClassification = 0;
    for (int i = 0; i < 72; i++)
    {
        if (trueLabelTraining[i] == classifiedLabelsTraining[i])
            correctClassification = correctClassification + 1;
    }
    errorLeatherTraining = (double(72-correctClassification)/72) * 100;
    cout << "leather training error is " << errorLeatherTraining << "%" << endl;
    //TESTING
    for (int imageNumber = 0; imageNumber < 24; imageNumber++)
    {
        sumLeather = 0;//Grass
        for (int featureNumber = 0; featureNumber < 3; featureNumber++)
        {
            difference = (reducedTestingLeather[imageNumber][featureNumber] - meanLeather[featureNumber])*(reducedTestingLeather[imageNumber][featureNumber] - meanLeather[featureNumber]);
            sumLeather = sumLeather + (difference/varianceLeather[featureNumber]);
        }
        distanceFromClass[imageNumber] = sqrt(sumLeather);
        
        sumLeather = 0;//Non-Grass
        for (int featureNumber = 0; featureNumber < 3; featureNumber++)
        {
            difference = (reducedTestingLeather[imageNumber][featureNumber] - meanNONLeather[featureNumber])*(reducedTestingLeather[imageNumber][featureNumber] - meanNONLeather[featureNumber]);
            sumLeather = sumLeather + (difference/varianceNONLeather[featureNumber]);
        }
        distanceFromNONClass[imageNumber] = sqrt(sumLeather);
        
    }
    //Compare the distances and assign labels accordingly
    for (int i = 0; i < 24; i++)
    {
        if (distanceFromClass[i] < distanceFromNONClass[i])
            classifiedLabelsTesting[i] = 1;
        else
            classifiedLabelsTesting[i] = -1;
    }
    
    correctClassification = 0;
    for (int i = 0; i < 24; i++)
    {
        if (trueLabelTesting[i] == classifiedLabelsTesting[i])
            correctClassification = correctClassification + 1;
    }
    errorLeatherTesting = (double(24-correctClassification)/24) * 100;
    cout << "leather testing error is " << errorLeatherTesting << "%" << endl;
    
    //SAND VS NON-SAND
    
    //TRAINING
    for (int imageNumber = 0; imageNumber < 72; imageNumber++)
    {
        sumSand = 0;//Sand
        for (int featureNumber = 0; featureNumber < 3; featureNumber++)
        {
            difference = (reducedTrainingSand[imageNumber][featureNumber] - meanSand[featureNumber])*(reducedTrainingSand[imageNumber][featureNumber] - meanSand[featureNumber]);
            sumSand = sumSand + (difference/varianceSand[featureNumber]);
        }
        distanceFromClass[imageNumber] = sqrt(sumSand);
        
        sumSand = 0;//Non-Leather
        for (int featureNumber = 0; featureNumber < 3; featureNumber++)
        {
            difference = (reducedTrainingSand[imageNumber][featureNumber] - meanNONSand[featureNumber])*(reducedTrainingSand[imageNumber][featureNumber] - meanNONSand[featureNumber]);
            sumSand = sumSand + (difference/varianceNONSand[featureNumber]);
        }
        distanceFromNONClass[imageNumber] = sqrt(sumSand);
        
    }
    //Compare the distances and assign labels accordingly
    for (int i = 0; i < 72; i++)
    {
        if (distanceFromClass[i] < distanceFromNONClass[i])
            classifiedLabelsTraining[i] = 1;
        else
            classifiedLabelsTraining[i] = -1;
    }
    
    correctClassification = 0;
    for (int i = 0; i < 72; i++)
    {
        if (trueLabelTraining[i] == classifiedLabelsTraining[i])
            correctClassification = correctClassification + 1;
    }
    errorSandTraining = (double(72-correctClassification)/72) * 100;
    cout << "sand training error is " << errorSandTraining << "%" << endl;
    //TESTING
    for (int imageNumber = 0; imageNumber < 24; imageNumber++)
    {
        sumSand = 0;//Grass
        for (int featureNumber = 0; featureNumber < 3; featureNumber++)
        {
            difference = (reducedTestingSand[imageNumber][featureNumber] - meanSand[featureNumber])*(reducedTestingSand[imageNumber][featureNumber] - meanSand[featureNumber]);
            sumSand = sumSand + (difference/varianceSand[featureNumber]);
        }
        distanceFromClass[imageNumber] = sqrt(sumSand);
        
        sumSand = 0;//Non-Grass
        for (int featureNumber = 0; featureNumber < 3; featureNumber++)
        {
            difference = (reducedTestingSand[imageNumber][featureNumber] - meanNONSand[featureNumber])*(reducedTestingSand[imageNumber][featureNumber] - meanNONSand[featureNumber]);
            sumSand = sumSand + (difference/varianceNONSand[featureNumber]);
        }
        distanceFromNONClass[imageNumber] = sqrt(sumSand);
        
    }
    //Compare the distances and assign labels accordingly
    for (int i = 0; i < 24; i++)
    {
        if (distanceFromClass[i] < distanceFromNONClass[i])
            classifiedLabelsTesting[i] = 1;
        else
            classifiedLabelsTesting[i] = -1;
    }
    
    correctClassification = 0;
    for (int i = 0; i < 24; i++)
    {
        if (trueLabelTesting[i] == classifiedLabelsTesting[i])
            correctClassification = correctClassification + 1;
    }
    errorSandTesting = (double(24-correctClassification)/24) * 100;
    cout << "sand testing error is " << errorSandTesting << "%" << endl; ;
    cout << "Please run the MATLAB code for SVM" << endl;
   
    return 0;
}



        


    
    
