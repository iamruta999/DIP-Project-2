% NAME: Amruta Kulkarni
% USC ID: 6914970827
% USC Email: arkulkar@usc.edu
% Submission date: 11 Oct 2015

% Problem 1A, part 4
% This code performs feature reduction using Fishers Linear Discriminant function for LDA from the classification
% toolbox
clear all;
clc;

%Load the training and testing data along with the labels
train = load('normalisedTraining.mat');
training = train.normalisedTraining(:,1:25);
test = load('normalisedTesting.mat');
testing = test.normalisedTesting(:,1:25);
label = load('trueLabel.mat');
trainingLabels = label.trueLabel(25:96,:);
testingLabels = label.trueLabel(1:24,:);
for i = 1:1:72
    if (trainingLabels(i) == 2)
        trainingLabels(i) = 0;%As the labels can only be 0 or 1 for LDA
    end
end

for i = 1:1:24
    if (testingLabels(i) == 2)
        testingLabels(i) = 0;
    end
end

%LDA
[patterns, train_targets, w] = FishersLinearDiscriminant(training', trainingLabels);
testPatterns = w'*testing';

%Get the reduced features for training and testing data
newTraining = patterns(1,:)';
newTesting = testPatterns';

%Separate the two classes and calculate the mean and variance
meanGrass = mean(newTraining(1:36,:));
meanStraw = mean(newTraining(37:72,:));
varianceGrass = var(newTraining(1:36,:));
varianceStraw = var(newTraining(37:72,:));

%Calculate the mahalanobis distance and label the data
%TRAINING
distanceFromGrassTraining = zeros(72,1);
distanceFromStrawTraining = zeros(72,1);
ldaLabelsTraining = zeros(72,1);

for i = 1:1:72
    
    differenceGrass = (newTraining(i,1) - meanGrass) * (newTraining(i,1) - meanGrass);
    distanceFromGrassTraining(i) = sqrt(differenceGrass / varianceGrass);
    
    differenceStraw = (newTraining(i,1) - meanStraw) * (newTraining(i,1) - meanStraw);
    distanceFromStrawTraining(i) = sqrt(differenceStraw / varianceStraw);
    
    if(distanceFromGrassTraining(i) < distanceFromStrawTraining(i))
        ldaLabelsTraining(i) = 1;
    else
        ldaLabelsTraining(i) = 0;
    end
   
end
correct = 0;
for i = 1:1:72
    if (trainingLabels(i) == ldaLabelsTraining(i))
        correct = correct + 1;
    end
end
error = (72 - correct)/72;
disp('training error is');
disp(error);

%TESTING
distanceFromGrassTesting = zeros(24,1);
distanceFromStrawTesting = zeros(24,1);
ldaLabelsTesting = zeros(24,1);

for i = 1:1:24
    
    differenceGrass = (newTesting(i,1) - meanGrass) * (newTesting(i,1) - meanGrass);
    distanceFromGrassTesting(i) = sqrt(differenceGrass / varianceGrass);
    
    differenceStraw = (newTesting(i,1) - meanStraw) * (newTesting(i,1) - meanStraw);
    distanceFromStrawTesting(i) = sqrt(differenceStraw / varianceStraw); 
    
    if(distanceFromGrassTesting(i) < distanceFromStrawTesting(i))
        ldaLabelsTesting(i) = 1;
    else
        ldaLabelsTesting(i) = 0;
    end
end

correct = 0;
for i = 1:1:24
    if (testingLabels(i) == ldaLabelsTesting(i))
        correct = correct + 1;
    end
end
error = (24 - correct)/24;
disp('testing error is');
disp(error);




