% NAME: Amruta Kulkarni
% USC ID: 6914970827
% USC Email: arkulkar@usc.edu
% Submission date: 11 Oct 2015

% Problem 2d
% This code uses the edgesEvalImg function to calculate the F Precision and recall values for different edge maps obtaibed by using different edge detection techniques
clear all;
clc
row = 321;
col = 481;
[thrs,cntR,sumR,cntP,sumP,V] = edgesEvalImg('Non-Maximal15Cougar','Farm_GT1.mat','thrs',1);

%% The groundtruth is created as follows

% fin = fopen('Cougar_GT5.raw');
% H = fread(fin, [col row], 'uint8=>uint8');  
% b = H';
% b = (b==255);
% b = 1-b;
% im(b)
% field = 'Boundaries';
% S = struct(field,b);
% groundTruth = {S};

