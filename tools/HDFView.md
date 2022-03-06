PS F:\HDFViewApp-3.1.2-win10_64-vs16\HDFView> .\HDFView.exe

>SLF4J: Class path contains multiple SLF4J bindings.
>SLF4J: Found binding in [jar:file:///F:/HDFViewApp-3.1.2-win10_64-vs16/HDFView/app/mods/slf4j-nop-1.7.25.jar!/org/slf4j/
>impl/StaticLoggerBinder.class]
>SLF4J: Found binding in [jar:file:/F:/HDFViewApp-3.1.2-win10_64-vs16/HDFView/app/extra/slf4j-simple-1.7.25.jar!/org/slf4
>j/impl/StaticLoggerBinder.class]
>SLF4J: Found binding in [jar:file:/F:/HDFViewApp-3.1.2-win10_64-vs16/HDFView/app/slf4j-nop-1.7.25.jar!/org/slf4j/impl/St
>aticLoggerBinder.class]
>SLF4J: See http://www.slf4j.org/codes.html#multiple_bindings for an explanation.
>SLF4J: Actual binding is of type [org.slf4j.helpers.NOPLoggerFactory]
>java.lang.UnsatisfiedLinkError: F:\HDFViewApp-3.1.2-win10_64-vs16\HDFView\runtime\bin\hdf5_java.dll:

[java.lang.UnsatisfiedLinkError: no jhdf5 in java.library.path](https://stackoverflow.com/questions/42138270/java-lang-unsatisfiedlinkerror-no-jhdf5-in-java-library-path)

[How to fix an UnsatisfiedLinkError (Can't find dependent libraries) in a JNI project](https://stackoverflow.com/questions/6092200/how-to-fix-an-unsatisfiedlinkerror-cant-find-dependent-libraries-in-a-jni-pro)

> ```java
> java -XshowSettings:properties -version
> ```

[Java error - cannot find library in java.library.path?](https://stackoverflow.com/questions/7195778/java-error-cannot-find-library-in-java-library-path)

> java -Djava.library.path=<path_to_dll> <main_class>

[HDFView 3.1.2 issues and regressions](https://forum.hdfgroup.org/t/hdfview-3-1-2-issues-and-regressions/7887)

https://support.hdfgroup.org/ftp/HDF5/releases/HDF-JAVA/hdfview-3.1.2/hdfview_scripts/

https://github.com/ClassViewer/java-gui-launcher
