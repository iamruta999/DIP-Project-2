
% NAME: Amruta Kulkarni
% USC ID: 6914-9708-27
% E-mail: arkulkar@usc.edu

% Problem 3c
% This code calculates the 5 different evaluation metrics for the segmented image (MS or CCP)
clear all;
clc;
% Read the groundTruth image
A = imread('Rhinos_color_GT.jpg');
A = double(rgb2gray(A));       % convert to gray
field = 'Segmentation';  
S = struct(field,A);           % create a struct
groundTruth = {S};             % Convert to cell
seg = load('RhinosCCP.mat');   % Take the CCP or MS image
seg = seg.color_segment;       % For MS image do seg.y 
seg = seg/255;
imshow(seg)                    % Check if you have taken the image properly
seg = im2uint8(seg);
% Calculate CoV
[cov]=compare_covering(double(rgb2gray(seg)),groundTruth);
% Calculate PRI, GCE, VoI
[ri,gce,vi]=compare_segmentations(rgb2gray(seg),A);
% Calculate BDE
[averageError, returnStatus] = compare_image_boundary_error(A, double(rgb2gray(seg)));