clc;
clear;
close all;

data = [magic(5) / 1000; 0, 0, 0, 0, 0];
disp(data);

fid = fopen('magic.bin', 'w+');
if fid == -1
    error('Failed to open file for writing.');
end

fwrite(fid, data, '*double');

fseek(fid, 0, 'bof');

data2 = fread(fid, [6, 5], '*double');
disp(data2);

fclose(fid);
