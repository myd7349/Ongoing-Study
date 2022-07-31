function [ data ] = read_data( filename )
%read_data Export a binary data
%   Detailed explanation goes here

fid = fopen(filename);
if fid == -1
    error('Failed to open file');
end

% Calculate file size in bytes
fseek(fid, 0, 'eof');
total_bytes = ftell(fid);
frewind(fid);

channels = 5;
samples = total_bytes / channels / 8;

data = fread(fid, [samples, channels], '*double');

fclose(fid);

end


% References:
% https://stackoverflow.com/questions/1897422/how-can-i-display-an-error-message-in-matlab
% https://stackoverflow.com/questions/849739/how-do-you-get-the-size-of-a-file-in-matlab
% https://www.mathworks.com/help/matlab/math/removing-rows-or-columns-from-a-matrix.html
% https://github.com/sccn/eeglab/blob/develop/functions/miscfunc/shortread.m
