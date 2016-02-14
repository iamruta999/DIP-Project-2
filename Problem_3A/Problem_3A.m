% NAME: Amruta Kulkarni
% USC ID: 6914-9708-27
% E-mail: arkulkar@usc.edu

% Problem_3A
% this code performs the superpixel representation and Mean Shift segmentation on an image
clear all;
clc;
% Read the image
A = imread('Man.jpg'); % for Rhino use 'Rhinos.jpg'
[l,Am,c] = slic(A,150,10,1,'median');
%Now we have labels in l
Maximum = max(max(l));
newImage = zeros(481,321,3);
lab = zeros(Maximum,3);
% Convert c into LAB
for i = 1:1:Maximum
    lab(i,1) = c(i).L;
    lab(i,2) = c(i).a;
    lab(i,3) = c(i).b;
end
% Create the Lab image
for i = 1:1:481    
    for j = 1:1:321
        newImage(i,j,:) = lab(l(i,j),:);
    end
end
%Convert Lab image to RGB format
finalImage = Lab2RGB(newImage);
imshow(finalImage); % This image is the superpixel representation
%Use Mean Shift segmentation 
y = meanShiftPixCluster(finalImage,15,10);
figure; imshow(y/255)