% 2018-04-12T12:04+08:00

clc;

%{
%img = imread('CIM_1.png');
img = imread('CIM_1_bw.png');
gray_img = rgb2gray(img);
bw_img = im2bw(gray_img, graythresh(gray_img));
imwrite(bw_img, 'CIM_1_bw.png');

imshow(img);
imshow(gray_img);
%}

bw_img = imread('CIM_1_bw.png');
[img_h, img_w] = size(bw_img);

imshow(bw_img);

[centers, radii] = imfindcircles(bw_img, [15,35], 'ObjectPolarity', 'dark');
circles = [centers, radii];
circles = sortrows(circles, 2);

cols_in_each_row = [12, 12, 1, 12, 12];
orders = [-1, 1, 1, -1, 1];
start_col = 1;

for i=1:length(cols_in_each_row)
    cols = cols_in_each_row(i);
    circles(start_col:start_col+cols-1, :) = sortrows(circles(start_col:start_col+cols-1, :), orders(i));
    start_col = start_col + cols;
end

centers = circles(:, 1:2);
radii = circles(:, 3);

%{
% First row
radii(1:12) = radii(7);
centers(1:12, 2) = centers(7, 2);
for i=1:12
    centers(i, 1) = (7 - i) * (centers(6, 1) - centers(7, 1)) + centers(7, 1);
end
%}

viscircles(centers, radii, 'EdgeColor', 'g');

circles_info = zeros(length(radii), 6);
circles_info(:, 1:2) = centers;
circles_info(:, 3) = radii;
for i=1:length(circles_info)
    circles_info(i, 4) = circles_info(i, 1) / img_w;
    circles_info(i, 5) = circles_info(i, 2) / img_h;
    circles_info(i, 6) = circles_info(i, 3) / img_w;
end

csvwrite('CIM_1.csv', circles_info);

% References:
% https://stackoverflow.com/questions/134712/how-can-i-sort-a-2-d-array-in-matlab-with-respect-to-one-column
% https://stackoverflow.com/questions/18820130/sort-matlab-array-in-descending-order
