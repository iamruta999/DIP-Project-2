//NAME: Amruta Kulkarni
//USC ID: 6914970827
//USC Email: arkulkar@usc.edu
//Submission date: 11 Oct 2015

//Problem 2C
//This code extracts the Red, green and blue channels from a color image
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{
    /* Define file pointer and variable */
    FILE *file;
    int bytesPerPixel = 3;
    int width = 481;
    int height = 321;
    
    /* Allocate image data array */
    unsigned char imageData[height][width][bytesPerPixel];
    
    /* Read image */
    if (!(file=fopen(argv[1],"rb")))
    {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(imageData, sizeof(unsigned char), width*height*bytesPerPixel, file);
	fclose(file);
    
    /* Separate the three color planes */
    
    unsigned char red[height][width];
    unsigned char green[height][width];
    unsigned char blue[height][width];
    
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            red[row][column] = imageData[row][column][0];
            
            green[row][column] = imageData[row][column][1];
            
            blue[row][column] = imageData[row][column][2];
            
        }
    }
    
    if (!(file=fopen(argv[2],"wb")))
    {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(red, sizeof(unsigned char), height*width, file);
	fclose(file);
    
    if (!(file=fopen(argv[3],"wb")))
    {
		cout << "Cannot open file: " << argv[3] << endl;
		exit(1);
	}
	fwrite(green, sizeof(unsigned char), height*width, file);
	fclose(file);
    
    if (!(file=fopen(argv[4],"wb")))
    {
		cout << "Cannot open file: " << argv[4] << endl;
		exit(1);
	}
	fwrite(blue, sizeof(unsigned char), height*width, file);
	fclose(file);
    
    return 0;
}

    
