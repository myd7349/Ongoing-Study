### #1 Try

Build Geomview with WSL2:

Clone source code from GitHub:

https://github.com/geomview/geomview

```
$ sudo apt-get install autoconf
$ sudo apt-get install libtool
$ autoreconf -i ./configure.ac
$ ./configure
```

[Some M4 macros don't seem to be defined](https://unix.stackexchange.com/questions/18673/some-m4-macros-dont-seem-to-be-defined)

[Can not run configure command: "No such file or directory"](https://unix.stackexchange.com/questions/158960/can-not-run-configure-command-no-such-file-or-directory)

Dependencies:

```
 libmotif-dev
```

However, I can not install this package successfully:

[apt not working: installed libc-bin package post-installation script subprocess returned error exit status 134](https://askubuntu.com/questions/1160366/apt-not-working-installed-libc-bin-package-post-installation-script-subprocess)

[libc-bin update error](https://github.com/microsoft/WSL/issues/4760)

https://github.com/geomview/geomview/blob/master/INSTALL.Geomview


### #2 Try

Build Geomview with Cygwin:

First, Clone source code from GitHub:

https://github.com/geomview/geomview

Second, install these packages:

- autoconf
- automake
- libtool

Then:

```
libtoolize --force
aclocal
autoheader
automake --force-missing --add-missing
autoconf
./configure
```

[Error with install: autoreconf fails to run aclocal](https://github.com/buffer/pylibemu/issues/24)

[trying to compile ... getting : 'config/ltmain.sh' not found](https://github.com/zyvitski/libzaudio/issues/1)

[Cannot find install-sh, install.sh, or shtool in ac-aux](https://askubuntu.com/questions/27677/cannot-find-install-sh-install-sh-or-shtool-in-ac-aux)

[How do I install cygwin components from the command line?](https://stackoverflow.com/questions/9260014/how-do-i-install-cygwin-components-from-the-command-line)

https://www.cygwin.com/packages/summary/libXm-devel.html

```
checking for motif... configure: error:

Can't find Motif header file Xm/Xm.h.  Geomview requires Motif
(or Lesstif).  See the file INSTALL.Geomview for details.
```

### #3 Try

Build Geomview with Cygwin:

Download from https://sourceforge.net/projects/geomview/files/

```
./configure
```

```
checking for motif... configure: error:

Can't find Motif header file Xm/Xm.h.  Geomview requires Motif
(or Lesstif).  See the file INSTALL.Geomview for details.
```

```
checking for motif... configure: error:

Can't find Motif header file Xm/Xm.h.  Geomview requires Motif
(or Lesstif).  See the file INSTALL.Geomview for details.
```

### #4 Try

https://cygwin.com/packages/summary/geomview.html

Install it, then run:

```
$ geomview
Error: Can't open display:
```

[Cygwin on Windows: Can't open display](https://unix.stackexchange.com/questions/227889/cygwin-on-windows-cant-open-display)

> Unix GUI programs display through an X server. Cygwin doesn't automatically start an X server. You need to install the packages xorg-server and xinit, and run startxwin.

This works for me:

```
startx /usr/bin/geomview
```
