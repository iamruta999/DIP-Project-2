% NAME: Amruta Kulkarni
% USC ID: 6914970827
% USC Email: arkulkar@usc.edu
% Submission date: 20 Sept 2015

% Problem 1B, part 3
% This problem performs classification using Support Vector Machines from
% the libSVM libraray.
clear all;
clc;
%GRASS
disp('For Grass');
%Load the training and test data for grass
trainGrass = load('new_training_grass');
trainingGrass = trainGrass.new_training_grass;
testGrass = load('new_testing_grass');
testingGrass = testGrass.new_testing_grass;
%load the labels
trainLabels = load('labels');
trainingLabels = trainLabels.labels;
testLabels = load('new_labels_test');
testingLabels = testLabels.new_labels_test;
% DESIGN SVM
%Training error
model_training_grass = svmtrain(trainingLabels,trainingGrass,'-s 0 -t 0 -c 500');
[predict_label_training_grass, accuracy_training_grass, dec_values_training] = svmpredict(trainingLabels, trainingGrass, model_training_grass);
%Testing error
[predict_label_testing_grass, accuracy_testing_grass, dec_values_testing] = svmpredict(testingLabels, testingGrass, model_training_grass);

disp('$$$$$$$$$$$$$$$$$$$$$$$$$$');
%STRAW
disp('For Straw');
%Load the training and test data for straw
trainStraw = load('new_training_straw');
trainingStraw = trainStraw.new_training_straw;
testStraw = load('new_testing_straw');
testingStraw = testStraw.new_testing_straw;
%load the labels
trainLabels = load('labels');
trainingLabels = trainLabels.labels;
testLabels = load('new_labels_test');
testingLabels = testLabels.new_labels_test;
% DESIGN SVM
%Training error
model_training_straw = svmtrain(trainingLabels,trainingStraw,'-s 0 -t 0 -c 500');
[predict_label_training_straw, accuracy_training_straw, dec_values_training] = svmpredict(trainingLabels, trainingStraw, model_training_straw);
%Testing error
[predict_label_testing_straw, accuracy_testing_straw, dec_values_testing] = svmpredict(testingLabels, testingStraw, model_training_straw);

disp('$$$$$$$$$$$$$$$$$$$$$$$$$$');
%LEATHER
disp('For Leather');
%Load the training and test data for leather
trainLeather = load('new_training_leather');
trainingLeather = trainLeather.new_training_leather;
testLeather = load('new_testing_leather');
testingLeather = testLeather.new_testing_leather;
%load the labels
trainLabels = load('labels');
trainingLabels = trainLabels.labels;
testLabels = load('new_labels_test');
testingLabels = testLabels.new_labels_test;
% DESIGN SVM
%Training error
model_training_leather = svmtrain(trainingLabels,trainingLeather,'-s 0 -t 0 -c 500');
[predict_label_training_leather, accuracy_training_leather, dec_values_training] = svmpredict(trainingLabels, trainingLeather, model_training_leather);
%Testing error
[predict_label_testing_leather, accuracy_testing_leather, dec_values_testing] = svmpredict(testingLabels, testingLeather, model_training_leather);

disp('$$$$$$$$$$$$$$$$$$$$$$$$$$')
%SAND
disp('For Sand');
%Load the training and test data for sand
trainSand = load('new_training_sand');
trainingSand = trainSand.new_training_sand;
testSand = load('new_testing_sand');
testingSand = testSand.new_testing_sand;
%load the labels
trainLabels = load('labels');
trainingLabels = trainLabels.labels;
testLabels = load('new_labels_test');
testingLabels = testLabels.new_labels_test;
% DESIGN SVM
%Training error
model_training_sand = svmtrain(trainingLabels,trainingSand,'-s 0 -t 0 -c 500');
[predict_label_training_sand, accuracy_training_sand, dec_values_training] = svmpredict(trainingLabels, trainingSand, model_training_sand);
%Testing error
[predict_label_testing_sand, accuracy_sand_leather, dec_values_testing] = svmpredict(testingLabels, testingSand, model_training_sand);
