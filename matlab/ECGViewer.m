% 2017-06-23T18:30+08:00
function ECGViewer

clc
close all

figure('ResizeFcn', @OnResize)
set(gcf, 'Units', 'centimeters')

axes('Units', 'centimeters')

slider = uicontrol(gcf, 'Style', 'slider', ...
    'Min', 0, 'Max', 1, 'Value', 0, 'Units', 'centimeters');

    function OnResize(~, ~)
        fpos = get(gcf, 'Position');
        
        xmargin = 1;
        ymargin = xmargin;
        sliderheight = 0.8;
        controlpanelwidth = 3;
        controlpanelheight = 3;
        
        set(gca, 'Position', [xmargin, ymargin+sliderheight+ymargin, fpos(3)-controlpanelwidth-3*xmargin, fpos(4)-sliderheight-3*ymargin])
        set(slider, 'Position', [xmargin, ymargin, fpos(3)-controlpanelwidth-3*xmargin, sliderheight])
    end

end
