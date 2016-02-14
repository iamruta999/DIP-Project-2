//NAME: Amruta Kulkarni
//USC ID: 6914970827
//USC Email: arkulkar@usc.edu
//Submission date: 11 Oct 2015

//Problem 2b
//This code performs edge detection on the farm and cougar images by using Canny edge detection.
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

int main(int argc, char *argv[])
{
    //char *argv[] = {"Farm.raw","edge1Farm.raw","edge2Farm.raw","edge3Farm.raw","edge4Farm.raw","edge5Farm.raw"};
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
    //PART 1
    Mat gray = Mat(height, width, CV_8UC1, grayImageData);
    Mat edge, finalEdge;
    
    Canny(gray, edge, 0.3*255, 0.6*255);
    edge.convertTo(finalEdge, CV_8UC1);
    
    unsigned char final[height][width];
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            final[row][column] = finalEdge.at<uchar>(row,column);
        }
    }
    
    if (!(file=fopen(argv[2],"wb")))
    {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(final, sizeof(unsigned char), height*width, file);
	fclose(file);
    
    //PART 2
    Canny(gray, edge, 0.2*255, 0.7*255);
    edge.convertTo(finalEdge, CV_8UC1);
    
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            final[row][column] = finalEdge.at<uchar>(row,column);
        }
    }
    
    if (!(file=fopen(argv[3],"wb")))
    {
		cout << "Cannot open file: " << argv[3] << endl;
		exit(1);
	}
	fwrite(final, sizeof(unsigned char), height*width, file);
	fclose(file);
    
    //PART 3
    Canny(gray, edge, 0.2*255, 0.5*255);
    edge.convertTo(finalEdge, CV_8UC1);

    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            final[row][column] = finalEdge.at<uchar>(row,column);
        }
    }
    
    if (!(file=fopen(argv[4],"wb")))
    {
		cout << "Cannot open file: " << argv[4] << endl;
		exit(1);
	}
	fwrite(final, sizeof(unsigned char), height*width, file);
	fclose(file);
    
    //PART 4
    Canny(gray, edge, 0.4*255, 0.7*255);
    edge.convertTo(finalEdge, CV_8UC1);
    
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            final[row][column] = finalEdge.at<uchar>(row,column);
        }
    }
    
    if (!(file=fopen(argv[5],"wb")))
    {
		cout << "Cannot open file: " << argv[5] << endl;
		exit(1);
	}
	fwrite(final, sizeof(unsigned char), height*width, file);
	fclose(file);
    
    //PART 5
    Canny(gray, edge, 0.4*255, 0.5*255);
    edge.convertTo(finalEdge, CV_8UC1);
    
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            final[row][column] = finalEdge.at<uchar>(row,column);
        }
    }
    
    if (!(file=fopen(argv[6],"wb")))
    {
		cout << "Cannot open file: " << argv[6] << endl;
		exit(1);
	}
	fwrite(final, sizeof(unsigned char), height*width, file);
	fclose(file);
    
    
    
    

    return 0;
}

