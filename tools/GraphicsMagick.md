[How can I reposition page elements of a PDF and write to a new PDF?](https://stackoverflow.com/questions/59295631/how-can-i-reposition-page-elements-of-a-pdf-and-write-to-a-new-pdf)

http://www.graphicsmagick.org/convert.html

[Imagemagic convert: How can we set a page "a4 Landscape"?](https://stackoverflow.com/questions/43421097/imagemagic-convert-how-can-we-set-a-page-a4-landscape)

[Convert an A4R (A4 lanscape) scanned jpeg, to A4R (A4 lanscape) pdf](https://unix.stackexchange.com/questions/487826/convert-an-a4r-a4-lanscape-scanned-jpeg-to-a4r-a4-lanscape-pdf)

[ImageMagick resize - set width for both landscape and portrait images](https://stackoverflow.com/questions/25557479/imagemagick-resize-set-width-for-both-landscape-and-portrait-images)

[ImageMagick: How to thicken lines](https://unix.stackexchange.com/questions/299218/imagemagick-how-to-thicken-lines)

> convert in.emf -monochrome out.png
> 
> convert in.emf -density 300x300 -auto-orient -morphology Erode Octagon out.png

[graphicsmagick how to remove transparent area and shrink the canvas size of a 32-bit image](https://stackoverflow.com/questions/19827613/graphicsmagick-how-to-remove-transparent-area-and-shrink-the-canvas-size-of-a-32)

> ```
> gm convert input.png -trim +repage output.png
> ```

[Resize without whitespace surrounding on images using graphicsmagick or imagemagick](https://stackoverflow.com/questions/24299938/resize-without-whitespace-surrounding-on-images-using-graphicsmagick-or-imagemag)

[How to change dpi in PostScript](https://stackoverflow.com/questions/17714871/how-to-change-dpi-in-postscript)

> The  default dpi in ps is 72dpi.

According to [Page size](http://www.graphicsmagick.org/GraphicsMagick.html#details-page):

A4 paper size is 210mmx297mm.

And 1inch equals to 2.54cm.

29.7/2.54*72 = 841.8897 dots.

[GraphicsMagick montage with border with rotation](https://stackoverflow.com/questions/35092907/graphicsmagick-montage-with-border-with-rotation)

[How to offset image contents by X,Y pixels using ImageMagick?](https://stackoverflow.com/questions/40659159/how-to-offset-image-contents-by-x-y-pixels-using-imagemagick)

> ```
> convert start.png -trim -bordercolor red -border 10x50 result.png
> ```

[Setting a white background](https://github.com/danielgatis/rembg/discussions/161)

> ```
> convert image.png -background white -alpha remove -alpha off white.png
> ```

https://github.com/swharden/Microscopy/blob/master/video-screen-capture/crop-a-gator.py
