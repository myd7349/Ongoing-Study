% 2012-10-11T13:10+08:00
function [imgDataDst, imgClrMapDst, imgDataSrc, imgClrMapSrc] = ...
    ColorReplace(imgName, clrSrc, clrDst)
% ColorReplace - Replace one color in an image with another color.
% -- input --
% imgName     : Source image name.
% clrSrc      : A color in the image. It specifies the color that will be
%               replaced. For example, if the source image is a 3-channel 
%               true color image. The "clrSrc" may have such format: [R, G, B].
% clrDst      : A color you specify. This function will replace the color
%               "clrSrc" in the image "imgDataSrc" with color "clrDst".
%               "clrDst" and "clrSrc" must be same in size.
% -- output --
% imgDataDst  : The image data matrix after color replacement.
% imgClrMapDst: The color map of "imgDataDst".
% imgDataSrc  : The image data matrix before color replacement.
% imgClrMapSrc: The color map of "imgDataSrc".
% -- note -- 
% When it comes to an indexed image, color replacement is be.  
% -- see also --
% imview, impixelinfo, imshow, imwrite, imread. 
% -- example --
% close all; clear; clc;
% [imgDataDst, imgClrMapDst, imgDataSrc, imgClrMapSrc] = ...
% ColorReplace('canoe.tif', [0.13, 0.13, 0.13], [1.0, 1.0, 1.0]);
% imshow(imgDataSrc, imgClrMapSrc); title('Before color replacement:');
% figure; imshow(imgDataDst, imgClrMapDst); title('After color replacement:'); 
% -- author --
% myd7349<myd7349@gmail.com> 2012/10/10 12:47

if length(clrSrc(:)) ~= length(clrDst(:))
    error('Wrong color arguments.');
end

%{
if ~isa(imgDataSrc, 'numeric')
    error('Not an image. The input image data matrix must be numeric');
end

if ndims(imgDataSrc) ~= 3 ...
        || imgC < 1 || imgC > 4
    error('Unsupported image type.');
end
%}

try
    [imgDataSrc, imgClrMapSrc] = imread(imgName);
catch
    error('Can not open this image.');
end

imgDataDst = imgDataSrc;
imgClrMapDst = imgClrMapSrc;

if isempty(imgClrMapSrc)
    [imgH, imgW, imgC] = size(imgDataSrc);
    if length(clrSrc(:)) == imgC
        clrSrc = reshape(clrSrc, 1, 1, imgC);
        clrDst = reshape(clrDst, 1, 1, imgC);
        for h = 1:imgH
            for w = 1:imgW
                if all(imgDataDst(h, w, :) == clrSrc)
                    imgDataDst(h, w, :) = clrDst;
                end
            end % end of "for w = 1:imgW"
        end % end of "for h = 1:imgH"
    else
        clrSrc = reshape(clrSrc, 1, 1, length(clrSrc(:)));
        clrDst = reshape(clrDst, 1, 1, length(clrDst(:)));
        imgC = min(imgC, length(clrSrc(:)));
        for h = 1:imgH
            for w = 1:imgW
                pixTmp = imgDataDst(h, w, :);
                if all(pixTmp(1:imgC) == clrSrc(1:imgC))
                    pixTmp(1:imgC) = clrDst(1:imgC);
                    imgDataDst(h, w, :) = pixTmp;
                end % end of "if all(pixTmp(1:imgC) == clrSrc(1:imgC))"
            end % end of "for w = 1:imgW"
        end % end of "for h = 1:imgH"
    end % end of "if length(clrSrc(:)) == imgC
else
    [mapH, mapC] = size(imgClrMapSrc);
    if nargout == 1 || nargout == 3
        warning('This image is an indexed image, you may need the color map.');
    end
    clrSrc = reshape(clrSrc, 1, length(clrSrc(:)));
    if any(clrSrc > 1.0)
        clrSrc = clrSrc ./ 255;
    end
    clrDst = reshape(clrDst, 1, length(clrDst(:)));
    if any(clrDst > 1)
        clrSrc = clrDst ./ 255;
    end
    mapC = min(mapC, length(clrSrc(:)));
    epsilon = 1.0/256.0;
    for h = 1:mapH
        clrTmp = imgClrMapSrc(h, :);
        if all(abs(clrTmp(1:mapC) - clrSrc(1:mapC)) < epsilon)
            clrTmp(1:mapC) = clrDst(1:mapC);
            imgClrMapDst(h, :) = clrTmp;
        end
    end % end of "for h = 1:mapH"
end

end % end of function 