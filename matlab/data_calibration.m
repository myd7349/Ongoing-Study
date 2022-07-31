sf = 512;
freq = 10;
step = int32(sf / freq + 5);
signal = 1;

[filename, pathname] = uigetfile({'*.txt', 'Text Files (*.txt)'; '*.*', 'All Files(*.*)'});

if ~isequal(filename, 0)
    file_path = [pathname, filename];
    [~, filename_without_ext, ~] = fileparts(filename);

    data = importdata(file_path);

    signal_data = data.data(:,signal);

    result = [];

    for i=1:step:size(signal_data, 1)
        start_index = i;
        end_index = i + step;
        if end_index > size(signal_data, 1)
            end_index = size(signal_data, 1);
        end

        data_piece = signal_data(start_index:end_index);
        minimum = min(data_piece);
        maximum = max(data_piece);

        data_piece_result = [
            double(start_index) / double(sf), ...
            double(end_index) / double(sf), ...
            minimum, ...
            maximum, ...
            maximum - minimum];
        result = [result; data_piece_result];
    end

    [filename, pathname, format] = uiputfile({'*.csv', 'CSV File (*.csv)'}, '', filename_without_ext);
    if ~isequal(filename, 0)
        file_path = [pathname, filename];
        if isequal(format, 1)
            writematrix(result, file_path);
        end
    end

    plot(result(:, 3:5));
end


% References:
% https://jp.mathworks.com/matlabcentral/answers/857225-how-does-division-work-for-integer-types
% https://jp.mathworks.com/matlabcentral/answers/380821-how-to-convert-table-to-matrix
% https://jp.mathworks.com/matlabcentral/answers/113813-append-rows-at-the-end-of-matrix
% https://jp.mathworks.com/matlabcentral/answers/23686-floating-point-value-to-integer-value
