NAME: Amruta Kulkarni
USC ID: 6914-9708-27
E-mail: arkulkar@usc.edu

The following steps will guide you to execute the files that are contained in this folder.

FOR PROBLEM 1A 
1. Copy all the images of straw and grass in the folder named Problem_1A.
2. Open the "main_Maha_PCA.cpp" file in Xcode and set the address of this folder in the custom directry in scheme.
3. Run this file by adding the required OpenCV libraraies.
4. The console will display the error rates for training and testing data for the two different techniques of No feature reduction and PCA
5. Now, uncomment the 6 lines in the section "//Separate Training & Testing" which is in "/*Principal Component Analysis*/"
6. Now, the console will display all the training and testing samples with 25 features each.
7. Copy the training samples and testing samples separately into matlab with the name 'normalisedTraining.mat' and 'normalisedTesting.mat'.
8. Now, uncomment a section in "/* Minimum ditance to class means classifier */" to display the labels on console.
9. Copy these labels in Matlab with name trueLabel
10. Now run the file "problem1A_LDA.m" in MATLAB.
11. Error rates for training and testing using LDA will be displayed

FOR PROBLEM 1B
1. Copy all the images of grass, straw, leather and sand in the folder named Problem_1B
2. Open the "main.Maha.cpp" file and run it in Xcode.
3. The console will display the error rates for training and testing data for the 4 different classifiers
4. Uncomment the lines in "/*Principal Component analysis*/" to get the training and testing dataon the console
5. Copy this data into matlab as per the names used in the file problem1b_SVM.m
6. Run the file problem1b_SVM by using the libSVM directory.

FOR PROBLEM 2A and 2B
1. Copy the Farm.raw and Cougar.raw in the folder named Problem_2A and also in Problem_2B.
2. In terminal, type the address of the folder that you want to execute and then type "make".
3 It will ask you to enter the file names, please do so by following the displayed example.

FOR PROBLEM 2C
1. Copy the Farm and Cougar images into this folder and then give the address of this folder in terminal.
2. Then type "make"
3. 3 images will be generated in this folder.
4. Copy these images into Matlab and as per the way the file "structured_edge.m" calls them
5. Now, run Structured_edge.m.
6. You need 2 different toolboxes to run this file.

FOR PROBLEM 2D
1. Follow the example fiven in the file "Evaluate_F_measure" to construct the ground truths
2. Run this file by giving appropriate inputs.
3. You will need to open raw images using fopen.

