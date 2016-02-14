% NAME: Amruta Kulkarni
% USC ID: 6914970827
% USC Email: arkulkar@usc.edu
% Submission date: 11 Oct 2015

% Problem 2c
%This code performs the structured edge detection on farm and cougar images
clc
clear all;
clc;
%% set opts for training (see edgesTrain.m)
opts=edgesTrain();                % default options (good settings)
opts.modelDir='models/';          % model will be in models/forest
opts.modelFnm='modelBsds';        % model name
opts.nPos=5e5; opts.nNeg=5e5;     % decrease to speedup training
opts.useParfor=0;                 % parallelize if sufficient memory

%% train edge detector (~20m/8Gb per tree, proportional to nPos/nNeg)
tic, model=edgesTrain(opts); toc; % will load model if already trained

%% set detection parameters (can set after training)
model.opts.multiscale=1;          % for top accuracy set multiscale=1
model.opts.sharpen=20;             % for top speed set sharpen=0
model.opts.nTreesEval=4;          % for top speed set nTreesEval=1
model.opts.nThreads=6;            % max number threads for evaluation
model.opts.nms=1;                 % set to true to enable nms

%% evaluate edge detector on BSDS500 (see edgesEval.m)
if(0), edgesEval( model, 'show',1, 'name','' ); end

%% detect edge and visualize results
row = 321;
col = 481;
fin = fopen('redFarm.raw','r');
I = fread(fin, [col row], 'uint8=>uint8');
Red = I';
fin = fopen('greenFarm.raw','r');
I = fread(fin, [col row], 'uint8=>uint8');
Green = I';
fin = fopen('blueFarm.raw','r');
I = fread(fin, [col row], 'uint8=>uint8');
Blue = I';
Farm = cat(3, Red,Green,Blue);
tic, E=edgesDetect(Farm,model); toc
E = (E>0.125);
E = 1-E;
figure(1); im(Farm); figure(2); im(E);
