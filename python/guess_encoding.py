#!/usr/bin/env python3
# coding: utf-8
# yapf -i guess_encoding.py

import sys

py37_encoding_list = (
    'ascii', 'big5', 'big5hkscs', 'cp037', 'cp273', 'cp424', 'cp437', 'cp500',
    'cp720', 'cp737', 'cp775', 'cp850', 'cp852', 'cp855', 'cp856', 'cp857',
    'cp858', 'cp860', 'cp861', 'cp862', 'cp863', 'cp864', 'cp865', 'cp866',
    'cp869', 'cp874', 'cp875', 'cp932', 'cp949', 'cp950', 'cp1006', 'cp1026',
    'cp1125', 'cp1140', 'cp1250', 'cp1251', 'cp1252', 'cp1253', 'cp1254',
    'cp1255', 'cp1256', 'cp1257', 'cp1258', 'cp65001', 'euc_jp',
    'euc_jis_2004', 'euc_jisx0213', 'euc_kr', 'gb2312', 'gbk', 'gb18030', 'hz',
    'iso2022_jp', 'iso2022_jp_1', 'iso2022_jp_2', 'iso2022_jp_2004',
    'iso2022_jp_3', 'iso2022_jp_ext', 'iso2022_kr', 'latin_1', 'iso8859_2',
    'iso8859_3', 'iso8859_4', 'iso8859_5', 'iso8859_6', 'iso8859_7',
    'iso8859_8', 'iso8859_9', 'iso8859_10', 'iso8859_11', 'iso8859_13',
    'iso8859_14', 'iso8859_15', 'iso8859_16', 'johab', 'koi8_r', 'koi8_t',
    'koi8_u', 'kz1048', 'mac_cyrillic', 'mac_greek', 'mac_iceland',
    'mac_latin2', 'mac_roman', 'mac_turkish', 'ptcp154', 'shift_jis',
    'shift_jis_2004', 'shift_jisx0213', 'utf_32', 'utf_32_be', 'utf_32_le',
    'utf_16', 'utf_16_be', 'utf_16_le', 'utf_7', 'utf_8', 'utf_8_sig', 'mbcs')


def print_usage():
    print('guess_encoding.py <source_text> <target_text>')


def guess_encoding(source_text, target_text):
    for src in py37_encoding_list:
        for dst in py37_encoding_list:
            if src == dst:
                continue

            try:
                messy_text = source_text.encode(src).decode(dst)
                if messy_text == target_text:
                    print(f'{src} -> {dst}: {source_text} -> {messy_text}')
            except:
                pass


def main():
    argc = len(sys.argv)
    if len(sys.argv) != 3:
        print_usage()
        sys.exit()

    guess_encoding(sys.argv[1], sys.argv[2])


if __name__ == '__main__':
    main()

# py .\guess_encoding.py 中国 ÖÐ¹ú
# gb2312 -> cp1252: 中国 -> ÖÐ¹ú
# gb2312 -> latin_1: 中国 -> ÖÐ¹ú
# gb2312 -> iso8859_15: 中国 -> ÖÐ¹ú
# gbk -> cp1252: 中国 -> ÖÐ¹ú
# gbk -> latin_1: 中国 -> ÖÐ¹ú
# gbk -> iso8859_15: 中国 -> ÖÐ¹ú
# gb18030 -> cp1252: 中国 -> ÖÐ¹ú
# gb18030 -> latin_1: 中国 -> ÖÐ¹ú
# gb18030 -> iso8859_15: 中国 -> ÖÐ¹ú
# mbcs -> cp1252: 中国 -> ÖÐ¹ú
# mbcs -> latin_1: 中国 -> ÖÐ¹ú
# mbcs -> iso8859_15: 中国 -> ÖÐ¹ú

# References:
# [Opening a text file, and receiving a encoding error, tried multiple methods no hope](https://stackoverflow.com/questions/52307730/opening-a-text-file-and-receiving-a-encoding-error-tried-multiple-methods-no-h)
# [How to determine the encoding of text?](https://stackoverflow.com/questions/436220/how-to-determine-the-encoding-of-text)
# > from bs4 import UnicodeDammit
# > dammit = UnicodeDammit("Sacr\xc3\xa9 bleu!")
# > print(dammit.unicode_markup)
# > # Sacré bleu!
# > dammit.original_encoding
# > # 'utf-8'
# https://github.com/skywind3000/PyStand/issues/6
# My test:
# 1. Download PyStand-py38-pyqt5-lite.7z from PyStand's release page;
# 2. Uncompress it into a directory that contains Chinese characters(D:\中国 PyStand-py38-pyqt5-lite\, for example);
# 3. Add these lines into PyStand.int:
#    import PyQt5.QtCore
#    print('Qt5 Plugins path: %s' % PyQt5.QtCore.QLibraryInfo.location(PyQt5.QtCore.QLibraryInfo.PluginsPath))
#    print('Qt5 Prefix path: %s' % PyQt5.QtCore.QLibraryInfo.location(PyQt5.QtCore.QLibraryInfo.PrefixPath))
# 4. Run .\PyStand.exe in cmd.exe;
#    Output:
#    Qt5 Plugins path: D:/ÖÐ¹ú PyStand-py38-pyqt5-lite/site-packages/PyQt5/Qt5/plugins
#    Qt5 Prefix path: D:/ÖÐ¹ú PyStand-py38-pyqt5-lite/site-packages/PyQt5/Qt5
#
# 5. Solution 1:
#    Add this line:
#        os.environ['QT_QPA_PLATFORM_PLUGIN_PATH'] = r'.\site-packages\PyQt5\Qt5\plugins'
#    before import PyQt5.QtWidgets.
#
# 6. Solution 2:
#        from PyQt5.QtCore import *
#        QCoreApplication.addLibraryPath(r'.\site-packages\PyQt5\Qt5\plugins')
#        from PyQt5.QtWidgets import *
#
#
# [minimalistic PyQt 5.6.0 project "could not find or load the Qt platform plugin "windows""](https://github.com/pyinstaller/pyinstaller/issues/2857)
# > import PyQt5.QtCore
# > print('Qt5 Plugins path:\n\t%s' % PyQt5.QtCore.QLibraryInfo.location(PyQt5.QtCore.QLibraryInfo.PluginsPath))
# > print('Qt5 Prefix path:\n\t%s' % PyQt5.QtCore.QLibraryInfo.location(PyQt5.QtCore.QLibraryInfo.PrefixPath))
# [QFile cannot open filenames containing unicode characters](https://stackoverflow.com/questions/14805706/qfile-cannot-open-filenames-containing-unicode-characters)
# > from PyQt5.QtCore import *
# > print(QTextCodec.codecForLocale().name())
# > QTextCodec.setCodecForLocale(QTextCodec.codecForName('GBK'))
# [How can I get text encoding system explicitly in Qt?](https://stackoverflow.com/questions/16371553/how-can-i-get-text-encoding-system-explicitly-in-qt)
# [Set Qt default encoding to UTF-8](https://stackoverflow.com/questions/8705488/set-qt-default-encoding-to-utf-8)
# [Get a list of all the encodings Python can encode to](https://stackoverflow.com/questions/1728376/get-a-list-of-all-the-encodings-python-can-encode-to)
# [[PyQt] Wrong unicode text encoding in the embedded :qt/etc/qt.conf.](https://pyqt.riverbankcomputing.narkive.com/VhCNMeo2/wrong-unicode-text-encoding-in-the-embedded-qt-etc-qt-conf)
# Hi,
#
# When PyQt5 (wheel) is installed on a path containing non-latin1
# characters it fails with
# ```
# qt.qpa.plugin: Could not find the Qt platform plugin "cocoa" in ""
# This application failed to start because no Qt platform plugin could
# be initialized. Reinstalling the application may fix this problem.
#
# Abort trap: 6
# ```
#
# To reproduce this, run (in bash):
# ```
# python -m venv --clear ~/virt/šš
# ~/virt/šš/bin/python -m pip install PyQt5
# ~/virt/šš/bin/python -c "import PyQt5.QtWidgets as w; w.QApplication([])"
# ```
#
# Explicitly setting the QT_PLUGIN_PATH to the correct location does work however
# ```
# export QT_PLUGIN_PATH=$HOME/virt/šš/lib/python3.6/site-packages/PyQt5/Qt/plugins/
# ~/virt/šš/bin/python -c"import PyQt5.QtWidgets as w; w.QApplication([])"
# ```
#
# The problem is that reading the "Paths/Prefix" in qt.conf with
# QSettings (the way Qt does), produces a garbled path:
# ```
# from PyQt5.QtCore import QSettings
# s = QSettings(":qt/etc/qt.conf", QSettings.IniFormat)
# print(s.value("Paths/Prefix"))
# # -> .../virt/sÌ\x8csÌ\x8c/lib/python3.6/site-packages/PyQt5/Qt'
# ```
#
# Reading the file with QFile
# ```
# f = QFile(":/qt/etc/qt.conf")
# f.open(QFile.ReadOnly)
# print(bytes(f.readAll()).decode("utf-8"))
# ```
# reveals that the contents are utf-8 encoded, however from
# http://doc.qt.io/qt-5/qsettings.html#Format-enum
#
# QSettings will accept Latin-1 encoded INI files, but generate pure ASCII files, where non-ASCII values are encoded using standard INI escape sequences.
#
# The `QSettings` does have a `setIniCodec` method, but it is not used
# by Qt for parsing the qt.conf file.
#
# Writing the path using QSettings
# ```
# s = QSettings("a.conf", QSettings.IniFormat)
# s.setValue("Paths/Prefix", ".../virt/šš/...")
# ```
# produces:
# ```
# [Paths]
# Prefix=".../virt/\x161\x161/..."
# ```
# which can then be correctly read back.
#
# Unfortunately Qt does not provide a public interface for INI escape
# sequence encoding. It is implemented in
# http://code.qt.io/cgit/qt/qtbase.git/tree/src/corelib/io/qsettings.cpp?h=v5.11.2#n618
#
# Tested on:
# * macOS 10.11.6, Python 3.6, PyQt5 5.11.3
# * KDE Neon 16.04 Python 3.5, PyQt5 5.11.3
#
# Best wishes
# Aleš Erjavec
# _______________________________________________
# PyQt mailing list ***@riverbankcomputing.com
# https://www.riverbankcomputing.com/mailman/listi
#
# The contents are a QByteArray created by calling QString::toLocal8Bit() on the pathname of the PyQt5 directory. See qpycore_qt_conf.cpp in the source tarball.
#
# Sorry, I'm not clear what your suggestion/fix is.
#
# Phil
# [Make python3 default to latin-1 for a script?](https://stackoverflow.com/questions/33896784/make-python3-default-to-latin-1-for-a-script)
# > Normally the codec picked for STDIO encoding / decoding is based on the current locale of your terminal where you are running the script.
# > To switch codecs, you can switch locale in your terminal, or set one for just Python by setting the PYTHONIOENCODING environment variable:
# > PYTHONIOENCODING=latin1 ./yourscript.py
# [Python: Converting from ISO-8859-1/latin1 to UTF-8](https://stackoverflow.com/questions/6539881/python-converting-from-iso-8859-1-latin1-to-utf-8)
# [How to tell Qt/PySide2 where to look for the qt.conf file on Windows?](https://forum.qt.io/topic/118683/how-to-tell-qt-pyside2-where-to-look-for-the-qt-conf-file-on-windows)
# https://doc.qt.io/qt-5/qt-conf.html
# [PyQt5 - Failed to load platform plugin "windows". Available platforms are: windows, minimal](https://stackoverflow.com/questions/17695027/pyqt5-failed-to-load-platform-plugin-windows-available-platforms-are-windo)
# [the qt app shows Chinese in messy code on windows when using UTF-8 encoding-format](https://stackoverflow.com/questions/56106456/the-qt-app-shows-chinese-in-messy-code-on-windows-when-using-utf-8-encoding-form)
# > On Windows, printing UTF-8 to the console is not automatic. You need to execute this command first in the console to
# > change to codepage 65001 (which is the UTF-8 Windows codepage):
# > chcp 65001
# https://github.com/baoboa/pyqt5/blob/11d5f43bc6f213d9d60272f3954a0048569cfc7c/qpy/QtCore/qpycore_qt_conf.cpp#L93
# > static QByteArray qt_conf = pyqt5_dir.absoluteFilePath(PYQT_QTCONF_PREFIX).toLocal8Bit();
# https://github.com/qt/qt/blob/0a2f2382541424726168804be2c90b91381608c6/src/corelib/tools/qstring.cpp#L3763-L3770
# > QByteArray QString::toLocal8Bit() const
# > {
# > #ifndef QT_NO_TEXTCODEC
# >    if (QTextCodec::codecForLocale())
# >        return QTextCodec::codecForLocale()->fromUnicode(*this);
# > #endif // QT_NO_TEXTCODEC
# >    return toLatin1();
# }
# https://doc.qt.io/archives/qt-5.11/internationalization.html
# > Windows
# > File I/O defaults to Latin1, with Unicode options in QTextStream.
# [PySide2 application fail to run if the exe file path include non-ascii characters](https://github.com/marcelotduarte/cx_Freeze/issues/593)
# [Changing default encoding of Python?](https://stackoverflow.com/questions/2276200/changing-default-encoding-of-python)
# > import sys
# > reload(sys)  # Reload does the trick!
# > sys.setdefaultencoding('UTF8')
# >
# > export PYTHONIOENCODING=utf8
# [PyQt Greek letters encoding](https://stackoverflow.com/questions/34710924/pyqt-greek-letters-encoding)
# > Consider telling PyQt to use native Python unicode strings
# > Before you import PyQt, insert:
# > import sip
# > sip.setapi('QString', 2)
# DeprecationWarning: setapi() is deprecated.
# [[PyQt] UnicodeDecodeError with output from Windows OS command](https://riverbankcomputing.com/pipermail/pyqt/2017-December/039814.html)
# https://github.com/qt/qt/blob/0a2f2382541424726168804be2c90b91381608c6/src/corelib/global/qlibraryinfo.cpp#L111
# > QString qtconfig = QLatin1String(":/qt/etc/qt.conf");
# ["could not find or load the Qt platform plugin "windows" in ""](https://forum.qt.io/topic/90293/could-not-find-or-load-the-qt-platform-plugin-windows-in)
# > I solved it:
# > add system environment
# > QT_QPA_PLATFORM_PLUGIN_PATH
# > C:\Qt\Qt5.12.2\5.12.2\msvc2017_64\plugins\platforms
# [Qt based app 'Qt platform plugin windows not found' issue when opening a file](https://stackoverflow.com/questions/33901842/qt-based-app-qt-platform-plugin-windows-not-found-issue-when-opening-a-file)
# [How to deploy a Qt application on Windows?](https://stackoverflow.com/questions/622418/how-to-deploy-a-qt-application-on-windows)
# [Qt for Windows - Deployment](https://doc.qt.io/qt-5/windows-deployment.html)
# > An alternative to putting the plugins in the plugins subdirectory is to add a custom search path when you start your application
# > using QCoreApplication::addLibraryPath() or QCoreApplication::setLibraryPaths().
# > QCoreApplication::addLibraryPath("C:/some/other/path");
# > All Qt GUI applications require a plugin that implements the Qt Platform Abstraction (QPA) layer in Qt 5.
# > For Windows, the name of the platform plugin is qwindows.dll. This file must be located within a specific
# > subdirectory (by default, platforms) under your distribution directory. Alternatively, it is possible to
# > adjust the search path Qt uses to find its plugins, as described below.
# >
