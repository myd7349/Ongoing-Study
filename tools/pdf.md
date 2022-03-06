Extract tabular data from PDF:

- [Tabula](https://github.com/tabulapdf/tabula)
- [PDFPlumber](https://github.com/jsvine/pdfplumber)
- [Tabula #731](https://github.com/tabulapdf/tabula/issues/731)
- [PDFBox](https://github.com/apache/pdfbox)
- [PdfPig](https://github.com/UglyToad/PdfPig)

PDF Viewers:

- Foxit PDF Reader

- [MuPDF](https://github.com/ArtifexSoftware/mupdf)

- [PdfiumViewer](https://github.com/pvginkel/PdfiumViewer)

- [PDF-XChange Viewer](https://www.tracker-software.com/product/pdf-xchange-viewer)

- [SumatraPDF](https://github.com/sumatrapdfreader/sumatrapdf)

- [Okular](https://github.com/KDE/okular)

- [Reader for iOS](https://github.com/vfr/Reader)

- [XpdfReader](https://www.xpdfreader.com/about.html)

Tools:

- [Xpdf & XpdfReader](https://www.xpdfreader.com/about.html)

- [caj2pdf](https://github.com/caj2pdf/caj2pdf)

- [diff-pdf](https://github.com/vslavik/diff-pdf)

- [pdf2svg](https://github.com/dawbarton/pdf2svg)

- [xhtml2pdf](https://github.com/xhtml2pdf/xhtml2pdf)

- [img2pdf](https://github.com/josch/img2pdf)
  
  https://twitter.com/terrywang/status/1303592660670668802
  
  > 命令行下处理 PDF 神奇组合 img2pdf + ocrmypdf 前者无损（快速、高效）生成 PDF 文件；后者 OCR 在扫描文件上加一层文本使其可搜索。两者可管道组合很灵活。另有诸多优化功能及高级应用场景参阅文档。可利用多核心，性能和可靠性历经百万级实战考验。处理小朋友们的正式姓名变更文件电子版派上用场。

- [OCRmyPDF](https://github.com/jbarlow83/OCRmyPDF)

- [uPDF](https://www.zhihu.com/question/23360635/answer/876404121)

- pdftk4all

- [pdfarranger](https://github.com/pdfarranger/pdfarranger)

- [pdfcrack](https://github.com/robins/pdfcrack)

- [splitpdf](https://sourceforge.net/projects/splitpdf/)

- Chrome
  
  [Using Headless Chrome to Convert Offline HTML to PDF in Bulk](https://kingsamchen.github.io/2021/10/09/headless-chrome-for-converting-offline-htmls-to-pdf-in-bulk/)
  
  > chrome.exe --headless --disable-gpu --print-to-pdf-no-header --print-to-pdf=$dest_file $file

- [naps2](https://github.com/cyanfish/naps2)

- [unoconv](https://github.com/unoconv/unoconv)
  
  - [I have a few EMF files. How I can convert them into ps/pdf/tiff on Linux?](https://stackoverflow.com/questions/7976438/i-have-a-few-emf-files-how-i-can-convert-them-into-ps-pdf-tiff-on-linux)

- [Poppler](https://poppler.freedesktop.org/releases.html)
  
  - [EMF format not supported for all printers](https://github.com/tojocky/node-pdfium/issues/5)
    
    > Actually, I tried using pdfium and it did not work that well  (generated EMF didn't look good (in windows viewer) and wasn't being  printed).
    > 
    > So I ended up using exec to execute Poppler's pdftops and it  generated postscript file that worked on Windows 7 in RAW mode and was  printed pretty quickly.

- [ImageMagick](https://imagemagick.org/index.php)
  
  > convert myemf.emf -scale 100% myemf.pdf/jpg/png

- [PDF24 Creator](https://en.pdf24.org/emf-2-pdf.html)

- [Convert EMF to PDF (vector)](https://superuser.com/questions/339986/convert-emf-to-pdf-vector)

- [Kuroko](https://github.com/shioyadan/kuroko) -  A small tool to convert from EMF to PDF.

- [Acrobat](https://helpx.adobe.com/uk/acrobat/kb/unable-convert-emf-to-pdfs.html)

- [Convert to EMF | PDF Creator Plus](https://www.youtube.com/watch?v=FNMe2KpGR_U)
  
  - [PDF Creator Plus](https://www.peernet.com/conversion-software/create-pdf/)

- [Programmatically convert EMF to PDF with Foxit](https://developers.foxit.com/developer-hub/document/programmatically-convert-emf-to-pdf/)

- [VeryDoc Metafile to PDF Converter](https://www.verydoc.com/emf-to-pdf.html)

- [Converseen](https://converseen.fasterland.net/) - A free batch image processor.
  
  - [5 Best Free EMF to PDF Converter Software for Windows](https://listoffreeware.com/free-emf-to-pdf-converter-software-windows/)
  - [Source code](https://github.com/Faster3ck/Converseen)
  - It uses Magick++.

- GhostScript
  
  - [Print PDF using GhostScript](https://stackoverflow.com/questions/20524323/print-pdf-using-ghostscript)

- [libemf2svg](https://github.com/kakwa/libemf2svg)

- [htmldoc](https://github.com/michaelrsweet/htmldoc)

- [PDFtk](https://www.pdflabs.com/tools/pdftk-the-pdf-toolkit/)

- [PDFPatcher](https://github.com/wmjordan/PDFPatcher)

- [GitHub - viper-framework/pdftools: Single directory containing pdfid and pdf-parser of Didier Stevens](https://github.com/viper-framework/pdftools)

EMF

- [How to render the PDF page as EMF or meta file in PDFium](https://stackoverflow.com/questions/49153715/how-to-render-the-pdf-page-as-emf-or-meta-file-in-pdfium)

- [Skia Issue 2772: Support Windows EMF backend](https://bugs.chromium.org/p/skia/issues/detail?id=2772)
  
  - https://chromium.googlesource.com/chromium/+/refs/heads/trunk/skia/ext/vector_platform_device_emf_win.h
  
  - [Is Metafile images like EMF and WMF supported by Skiasharp library?](https://github.com/mono/SkiaSharp/issues/1314)
    
    > Unfortunately not. SkiaSharp really only works with bitmap/raster images such as png/webp/jpg/bmp.

PDF Printers:

- [List of virtual printer software](https://en.wikipedia.org/wiki/List_of_virtual_printer_software)

- [Windows programmable virtual printer "device"](https://stackoverflow.com/questions/50078444/windows-programmable-virtual-printer-device)

- doPDF

- PDF24 Creator

- PDFCreator

- PDF Factory

- Microsoft Print to PDF

- Foxit Reader PDF Printer

- [Two Pilots Virtual Printer](https://www.colorpilot.com/emfprinterpilot.html)

- GhostPCL document conversion engine
  
  - https://github.com/elliottnick/VirtualPrinterPCLtoPDF/tree/master/VirtualPrinter/gspcl
    - https://ghostscript.com/
  - https://github.com/elliottnick/VirtualPrinterPCLtoPDF

- [clawPDF](https://github.com/clawsoftware/clawPDF)

- [PdfScribe](https://github.com/stchan/PdfScribe)
  
  It depends on Ghostscript.

- Zan Image Printer

Articles:

- [Print File Formats: A Comparative Analysis of EMF, OpenXPS and PDF for Enterprise Printing](https://citrixready.citrix.com/content/dam/ready/partners/pr/process-fusion-inc/uniprint-infinity/White-Paper-Comparison-of-Print-File-Formats-web.pdf)

PDF translation:

- [一帆文档翻译](https://fanyipdf.com/)

Online Tools:

- https://pdffly.com/
