test_file = 'test_generator.edf';

if ~isfile(test_file)
    msg = [ 'Downloading test file from' 10 ...
        'https://raw.githubusercontent.com/holgern/pyedflib/master/pyedflib/data/test_generator.edf' ];
    disp(msg);
    url = 'https://raw.githubusercontent.com/holgern/pyedflib/master/pyedflib/data/test_generator.edf';
    websave(test_file, url);
end

edf_data = edfread(test_file);
edf_info = edfinfo(test_file);

fs = edf_info.NumSamples / seconds(edf_info.DataRecordDuration);
fs = fs(1);

signum = 1;

t = (0:edf_info.NumSamples(signum)*edf_info.NumDataRecords(signum)-1) / fs(signum);

sin_1Hz = vertcat(edf_data.(5){:});
noise = vertcat(edf_data.(4){:});
sin_50Hz = vertcat(edf_data.(11){:});

data_len = fs * 10;

t_10s = t(1:data_len);
sin_1Hz_piece = sin_1Hz(1:data_len);
noise_piece = noise(1:data_len);
sin_50Hz_piece = sin_50Hz(1:data_len);

subplot(2,2,1);
plot(t_10s, sin_1Hz_piece);
title('Original data');

f_t = linspace(0, fs, length(sin_1Hz_piece));

sin_1Hz_piece_freq = fft(sin_1Hz_piece);

subplot(2,2,2);
plot(f_t, abs(sin_1Hz_piece_freq));
title('Original data FFT');

subplot(2,2,3);
data_with_noise = sin_1Hz_piece + noise_piece + sin_50Hz_piece;
plot(t_10s, data_with_noise);
title('Noise data(random noise + 50Hz noise)');

data_with_noise_freq = fft(data_with_noise);

subplot(2,2,4);
plot(f_t, abs(data_with_noise_freq));
title('Noise data FFT');


% References:
% [Designing Digital Filters with MATLAB](https://www.youtube.com/watch?v=VFt3UVw7VrE)
% https://jp.mathworks.com/matlabcentral/answers/49414-check-if-a-file-exists?s_tid=faqs_link
% https://www.mathworks.com/help/signal/ref/edfread.html
% https://stackoverflow.com/questions/23334819/flattening-a-cell-array
