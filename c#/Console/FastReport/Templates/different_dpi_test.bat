"%~dp0..\ReportGenerator\bin\Release\ReportGenerator.exe" -i "%~dp0Rectangle.frx" -o rect_2020_3_0_96dpi.emf
mspaint rect_2020_3_0_96dpi.emf
del rect_2020_3_0_96dpi.emf
"%~dp0..\ReportGenerator\bin\Release\ReportGenerator.exe" -i "%~dp0Rectangle.frx" -o rect_2020_3_0_600dpi.emf -x 600 -y 600
mspaint rect_2020_3_0_600dpi.emf
del rect_2020_3_0_600dpi.emf

"%~dp0..\ReportGeneratorDotNet_4_7_2\bin\Release\ReportGenerator.exe" -i "%~dp0Rectangle.frx" -o rect_2021_4_16_96dpi.emf
mspaint rect_2021_4_16_96dpi.emf
del rect_2021_4_16_96dpi.emf
"%~dp0..\ReportGeneratorDotNet_4_7_2\bin\Release\ReportGenerator.exe" -i "%~dp0Rectangle.frx" -o rect_2021_4_16_600dpi.emf -x 600 -y 600
mspaint rect_2021_4_16_600dpi.emf
del rect_2021_4_16_600dpi.emf

:: Conclusion:
:: FastReport.OpenSource.2020.3.0 doesn't handle resolution correctly.
