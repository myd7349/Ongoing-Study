% 2012-09-26T08:48+08:00
function VDICOM
close all;
clear;
warning off all;
clc;

progInfo = struct('Name', 'VDICOM' ...
    , 'Version', 'v1.0 20120920', 'Author', 'myd7349' ...
    , 'Email', 'myd7349@gmail.com' ...
    , 'Help', ['This is a simple DICOM image explorer written with ' ...
               , 'MATLAB 7.'] ...
    , 'wndWidth', 640, 'wndHeight', 480);

figure('CreateFcn', @FigCreate_Callback, 'Resize', 'off' ...
    , 'NumberTitle', 'off', 'Name', progInfo.Name ...
    , 'MenuBar', 'None' ...
    , 'CloseRequestFcn', @FileExit_Callback);

hFile = uimenu('Label', 'File', 'HandleVisibility', 'off');
uimenu(hFile, 'Label', 'Open DICOM image...', 'Callback', @FileOpen_Callback);
uimenu(hFile, 'Label', 'Close', 'Callback', @FileClose_Callback);
uimenu(hFile, 'Label', 'Save', 'Callback', @FileSave_Callback);
uimenu(hFile, 'Label', 'Save As...', 'Callback', @FileSaveAs_Callback);
uimenu(hFile, 'Label', 'Exit', 'Callback', @FileExit_Callback);
hEdit = uimenu('Label', 'Edit');
set(hEdit, 'HandleVisibility', 'off');
uimenu('Label', 'About...', 'Callback', @About_Callback);

%% callback function of figure
    function FigCreate_Callback(h, eventdata, handles, varargin)
        scrSize  = get(0, 'ScreenSize');
        wndWidth  = 640;
        wndHeight = 480;
        set(gcf, 'Position',[(scrSize(3)- progInfo.wndWidth)/2 ...
            , (scrSize(4) - progInfo.wndHeight)/2, progInfo.wndWidth ...
            , progInfo.wndHeight]);
    end

%% callback functions of 'File'
    function varargout = FileOpen_Callback(h, eventdata, handles, varargin)
        [filename, pathname] = ...
            uigetfile({'*.dcm;*.img', 'DICOM Image File(*.dcm, *.img)' ...
            ; '*.*', 'All Files(*.*)'});
        if isequal(filename,0)
        else
            hDCMDat = guidata(gcf);
            hDCMDat.Name = [pathname, filename];
            hDCMDat.Type = 1; % 1: dcm file, 0: image file, -1: error
            try,
                hDCMDat.Info = dicominfo(hDCMDat.Name);   
                [hDCMDat.Img, hDCMDat.Map] = dicomread(hDCMDat.Info);  
            catch,
                hDCMDat.Type = 0;
            end
            
            if 0 == hDCMDat.Type
                    try, 
                        hDCMDat.Info = imfinfo(hDCMDat.Name);
                        [hDCMDat.Img, hDCMDat.Map] = imread(hDCMDat.Name);  
                    catch,
                        hDCMDat.Type = -1;
                    end
            end
            
            if hDCMDat.Type ~= -1
                try,
                    imshow(hDCMDat.Img, hDCMDat.Map);
                    set(gcf, 'Name', [progInfo.Name, ' - ', hDCMDat.Name]);
                    cd(pathname);
                catch,
                    errordlg('It may not be a DICOM image.');
                end
            else
                errordlg('Neither a DICOM image nor a normal image file.' ...
                    , 'Open File Failed:');
            end
        end
    end % FileOpen_Callback

    function FileClose_Callback(h, eventdata, handles, varargin)
        clf;
        set(gcf, 'Name', progInfo.Name);
    end % FileSave_Callback
    
    function FileSave_Callback(h, eventdata, handles, varargin)
        msgbox('Save');
    end % FileSave_Callback
    
    function FileSaveAs_Callback(h, eventdata, handles, varargin)
        msgbox('Save As');
    end % FileSaveAs_Callback

    function FileExit_Callback(h, eventdata, handles, varargin)
        if  isequal(questdlg('Quit or not?','Message:','Yes', 'No' ...
                , 'Yes'), 'Yes')
            closereq; % exit VDICOM
        end
    end % FileExit_Callback

%% callback functions of 'Edit'

%% callback functions of 'About...'
    function About_Callback(h, eventdata, handles, varargin)
        msgbox({['Name:    ', progInfo.Name] ...
              , ['Version: ', progInfo.Version] ...
              , ['Author:   ', progInfo.Author] ...
              , ['Email:     ', progInfo.Email] ... 
              , progInfo.Help}, 'About VDICOM:');
    end % HelpAbout_Callback
    
end

