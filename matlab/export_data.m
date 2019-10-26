[filename, pathname] = uigetfile({'*.dat', 'Data Files (*.dat)'; '*.*', 'All Files(*.*)'});

if ~isequal(filename,0)
    file_path = [pathname, filename];
    data = read_data(file_path);
    
    [~, filename_without_ext, ~] = fileparts(filename);
    [filename, pathname, format] = uiputfile({'*.csv', 'CSV File (*.csv)'}, '', filename_without_ext);
    if ~isequal(filename,0)
        file_path = [pathname, filename];
        if isequal(format, 1)
            csvwrite(file_path, data);
        end
    end
end
