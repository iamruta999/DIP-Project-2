//NAME: Amruta Kulkarni
//USC ID: 6914970827
//USC Email: arkulkar@usc.edu
//Submission date: 11 Oct 2015

//Problem 2a
//This code performs edge detection on the farm and cougar images by using Sobel edge detection.
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <fstream>
#include <string>
#include <iostream>

#define PI 3.14159265

using namespace std;

int main(int argc, char *argv[])
{
    //Read the 24 bit color image
    FILE *file;
    
    int width = 481;
    int height = 321;
    int bytesPerPixel = 3;
    
    /* Allocate image data array */
    unsigned char imageData[height][width][bytesPerPixel];
    
    /* Read image */
    if (!(file=fopen(argv[1],"rb")))
    {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(imageData, sizeof(unsigned char), height*width*bytesPerPixel, file);
    fclose(file);
    
    //Convert the color image to grayscale image
    unsigned char grayImageData[height][width];
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            grayImageData[row][column] = ((0.21 * imageData[row][column][0]) +
                                          (0.72 * imageData[row][column][1]) +
                                          (0.07 * imageData[row][column][2]));
        }
    }
    
    //Write the grayscale image to a new file
    if (!(file=fopen(argv[2],"wb")))
    {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(grayImageData, sizeof(unsigned char), height*width, file);
	fclose(file);
    
    //Create extended image
    int N = 3;
    int extendedWidth = width + (N-1);
    int extendedHeight = height + (N-1);
    int halfLength = (N-1)/2;
    
    int extendedGrayImageData[extendedHeight][extendedWidth];
    //central, top and bottom part
    for(int row = 0; row < height; row++)
    {
        for(int column = 0;column < width; column++)
            
        {
            
            extendedGrayImageData[row+halfLength][column+halfLength] = grayImageData[row][column];//copy the gray data in the central part of the extended image
            
            int countTop = 0;                                                 //Top part of extended gray
            for ( int emptyRow = 0; emptyRow < halfLength; emptyRow++)
            {
                extendedGrayImageData[emptyRow][column+halfLength] = grayImageData[halfLength-countTop][column];
                countTop = countTop + 1;
            }
            
            int countBottom = 0;                                              //Bottom part of extended gray
            for ( int emptyrow = extendedHeight-1; emptyrow > ((height-1)+halfLength); emptyrow--)
            {
                extendedGrayImageData[emptyrow][column+halfLength] = grayImageData[(height-1)-halfLength+countBottom][column];
                countBottom = countBottom + 1;
            }
        }
    }
    
    //left and right part
    for (int row = 0; row < extendedHeight; row++)
    {
        int countLeft = 0;                                                   //Left columns of extended gray
        for (int emptyColumn = 0; emptyColumn < halfLength; emptyColumn++)
        {
            extendedGrayImageData[row][emptyColumn] = extendedGrayImageData[row][(N-1)-countLeft];
            countLeft = countLeft + 1;
        }
        
        int countRight = 0;                                                 //Right columns of extended gray
        for (int emptyColumn = extendedWidth-1; emptyColumn > ((width-1)+halfLength); emptyColumn--)
        {
            extendedGrayImageData[row][emptyColumn] = extendedGrayImageData[row][(extendedWidth-1)-N+countRight];
            countRight = countRight + 1;
        }
    }
    
    //Sobel Edge Detector
    
    int gradientX[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    int gradientY[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};
    float gX,gY;
    int sum = 0;
    int neighborhood[N][N];
    int gradientMagnitude[height][width];//Magnitude
    int gradientAngle[height][width];//Angle
    for (int row = halfLength; row < extendedHeight-halfLength; row++)
    {
        for (int column = halfLength; column < extendedWidth-halfLength; column++)
        {
            //Take a local window for every pixel
            for ( int i = 0; i < N; i++)
            {
                for ( int j = 0; j < N; j++)
                {
                    neighborhood[i][j] = extendedGrayImageData[row + (i - halfLength)][column + (j - halfLength)];
                }
            }

            //Apply gradientX Sobel filter
            sum = 0;
            for ( int i = 0; i < N; i++)
            {
                for ( int j = 0; j < N; j++)
                {
                    sum = sum + (neighborhood[i][j]*gradientX[i][j]);
                }
            }
            gX = sum / 4;
            //Apply gradientY Sobel filter
            sum = 0;
            for ( int i = 0; i < N; i++)
            {
                for ( int j = 0; j < N; j++)
                {
                    sum = sum + (neighborhood[i][j]*gradientY[i][j]);
                }
            }
            gY = sum / 4;
            //Assign the magnitude of the gradient to the central pixel
            gradientMagnitude[row-1][column-1] = sqrt( (gX * gX) + (gY * gY) );
            gradientAngle[row-1][column-1] = atan2(gX, gY) * 180/PI;
        }
       
    }
    
    //Make gradient angles equal to 0 or 90 to be used during non-maximal suppression
    for(int row = 0; row < height; row++)
    {
        for(int column = 0; column < width; column++)
        {
            if (abs(gradientAngle[row][column]) <= 45)
                gradientAngle[row][column] = 0;
            if (abs(gradientAngle[row][column]) > 45 && abs(gradientAngle[row][column]) <= 135)
                gradientAngle[row][column] = 90;
            if (abs(gradientAngle[row][column]) > 135 && abs(gradientAngle[row][column]) <= 180)
                gradientAngle[row][column] = 0;
        }
    }
    
            
    
    //Normalize the gradient map to the range 0-255
    int minUnnormalized;
    int maxUnnormalized;
    for(int row = 0; row < height; row++)
    {
        for(int column = 0; column < width; column++)
        {
            minUnnormalized = min(gradientMagnitude[row][column], minUnnormalized);
            maxUnnormalized = max(gradientMagnitude[row][column], maxUnnormalized);
        }
    }
    //cout << minUnnormalized <<"\t"<< maxUnnormalized << endl;
    int min = 0;
    int max = 255;
    int differenceOld = maxUnnormalized - minUnnormalized;
    int differnceNew = max - min;
    //cout << differenceOld << "\t" << differnceNew << endl;
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            gradientMagnitude[row][column] = (gradientMagnitude[row][column])*(float(differnceNew)/float(differenceOld));
        }
    }
    
    //Write the file for gradient magnitude Map
    unsigned char data[height][width];
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            data[row][column] = gradientMagnitude[row][column];
        }
    }
    if (!(file=fopen(argv[3],"wb")))
    {
		cout << "Cannot open file: " << argv[3] << endl;
		exit(1);
	}
	fwrite(data, sizeof(unsigned char), height*width, file);
	fclose(file);

    
    //Calculate histogram to determine the 10% and 15% pixels
    int histGray[256];
    for (int i = 0; i<256; i++)
    {
        histGray[i] = 0;     //assign 0 to the array to avoid garbage values
    }
    int grayLevel = 0;
    for(int row = 0; row < height; row++)
    {
        for(int column = 0; column < width; column++)
        {
            grayLevel = gradientMagnitude[row][column];
            histGray[grayLevel] = histGray[grayLevel] + 1;
        }
    }
    
    //Edge Map
    unsigned char edgeMap[height][width];
    int threshold;
    //The edge map for top 10% pixels as edges
    sum = 0;
    for (int i = 0; i<256; i++)
    {
        sum = sum + histGray[i];
        if (sum > (0.9 * height * width))//Top 10% pixels
        {
            threshold = i;
            //cout << i << endl;
            i = 256;
        }
    }
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            if (gradientMagnitude[row][column] < threshold)
                edgeMap[row][column] = 255;
            else
                edgeMap[row][column] = 0;
        }
    }
    
    //Write the file for edge map for 10%
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            data[row][column] = edgeMap[row][column];
        }
    }
    if (!(file=fopen(argv[4],"wb")))
    {
		cout << "Cannot open file: " << argv[4] << endl;
		exit(1);
	}
	fwrite(data, sizeof(unsigned char), height*width, file);
	fclose(file);

    
    //Non-Maximal Suppression
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            if (gradientAngle[row][column] == 0)//Horizontal direction
            {
                if (edgeMap[row][column] < edgeMap[row][column-1] && edgeMap[row][column] < edgeMap[row][column+1])
                {
                    edgeMap[row][column] = edgeMap[row][column];
                }
                else
                    edgeMap[row][column] = 255;
            }
            
            
            if (gradientAngle[row][column] == 90)//Vertical direction
            {
                if (edgeMap[row][column] < edgeMap[row-1][column] && edgeMap[row][column] < edgeMap[row+1][column])
                {
                    edgeMap[row][column] = edgeMap[row][column];
                }
                else
                    edgeMap[row][column] = 255;

            }
        }
    }
    
    //Write the file for edge map for 10% and maximal value suppression
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            data[row][column] = edgeMap[row][column];
        }
    }
    if (!(file=fopen(argv[5],"wb")))
    {
		cout << "Cannot open file: " << argv[5] << endl;
		exit(1);
	}
	fwrite(data, sizeof(unsigned char), height*width, file);
	fclose(file);
    
    
    
    //The edge map for top 15% pixels as edges
    sum = 0;
    for (int i = 0; i<256; i++)
    {
        sum = sum + histGray[i];
        if (sum > (0.85 * height * width))//Top 15% pixels
        {
            threshold = i;
            //cout << i << endl;
            i = 256;
        }
    }
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            if (gradientMagnitude[row][column] < threshold)
                edgeMap[row][column] = 255;
            else
                edgeMap[row][column] = 0;
        }
    }
    
    //Write the file for edge map for 10%
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            data[row][column] = edgeMap[row][column];
        }
    }
    if (!(file=fopen(argv[6],"wb")))
    {
		cout << "Cannot open file: " << argv[6] << endl;
		exit(1);
	}
	fwrite(data, sizeof(unsigned char), height*width, file);
	fclose(file);
    
    //Non-Maximal Suppression
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            if (gradientAngle[row][column] == 0)//Horizontal direction
            {
                if (edgeMap[row][column] < edgeMap[row][column-1] && edgeMap[row][column] < edgeMap[row][column+1])
                {
                    edgeMap[row][column] = edgeMap[row][column];
                }
                else
                    edgeMap[row][column] = 255;
            }
            
            
            if (gradientAngle[row][column] == 90)//Vertical direction
            {
                if (edgeMap[row][column] < edgeMap[row-1][column] && edgeMap[row][column] < edgeMap[row+1][column])
                {
                    edgeMap[row][column] = edgeMap[row][column];
                }
                else
                    edgeMap[row][column] = 255;
                
            }
        }
    }
    
    //Write the file for edge map for 15% and maximal value suppression
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            data[row][column] = edgeMap[row][column];
        }
    }
    if (!(file=fopen(argv[7],"wb")))
    {
		cout << "Cannot open file: " << argv[7] << endl;
		exit(1);
	}
	fwrite(data, sizeof(unsigned char), height*width, file);
	fclose(file);


    return 0;
    
}
