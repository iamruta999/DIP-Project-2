NAME: Amruta Kulkarni
USC ID: 6914-9708-27
E-mail: arkulkar@usc.edu

The following steps will guide you to execute the files that are contained in this folder.
1. Download the BSR, MCL_CCP-master, Segmentation Benchmark softwares that contain various functions to execute the following files.
2. The SLIC folder and the Mean Shift segmentation code is provided within this folder named SLIC.
3. Copy all these downloaded folders in MATLAB and add them on the path.

For Problem 3A
1. Convert the Man and Rhinos image from raw to jpeg format using ImageJ. Name them Man.jpg and Rhinos.jpg and copy them into MATLAB.
2. Execute the Problem_3A.m file to get the results.
3. Store the output matrix 'y' in each case as ManMS.mat and RhinosMS.mat and we will use these .mat files in Problem_3C.m file

For Problem 3B
1. In this file, modify the first line in the section %%read color image as: img_name = 'Rhinos.jpg' OR img_name = 'Man.jpg'
2. Run this file to get the results
3. Store the final 'color_segment' result as RhinosCCP.mat OR ManCCP.mat and we will use these .mat files in Problem_3C.m file

For Problem 3C
1. Convert the Rhinos_color_GT and Man_color_GT from raw to jpeg with the same name.
2. Copy these .jpg images into MATLAB
3. For every ground truth image, take RhinosCCP.mat or RhinoMS.mat and ManCCP.mat or ManMS.mat respectively to calculate the needed metrics.



 