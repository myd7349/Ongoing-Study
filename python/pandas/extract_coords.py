#!/usr/bin/env python3
# coding: utf-8

import pathlib
import string

import pandas
import pooch

try:
    import matplotlib.pyplot as plt
    can_plot = True
except ImportError:
    can_plot = False


def main():
    montageXLS = pooch.retrieve(
        url='https://psychophysiology.cpmc.columbia.edu/mmedia/Kayser2003b/montageXLS.zip',
        known_hash='fb4831742db804a6008d53ddbf191f39923774be7b13de2645c10740b5927475',
        processor=pooch.Unzip())

    for xls_file in montageXLS:
        cols = 'B:G' if 'HighDensityMontage' in xls_file else 'A,C:G'
        data = pandas.read_excel(
            xls_file,
            header=4,
            usecols=cols,
            dtype={0: str})

        coord_template = string.Template('["$electrode"] = new Point3D($x, $y, $z),')
        for row_no, row in data.iterrows():
            print(coord_template.substitute(electrode=row[0], x=row.X, y=row.Y, z=row.Z))

        if can_plot:
            names = [row[0] for _, row in data.iterrows()]
            xs = [row.X for _, row in data.iterrows()]
            ys = [row.Y for _, row in data.iterrows()]

            dpi = 96
            width = 1024
            plt.figure(num=xls_file, figsize=(width/dpi, width/dpi), dpi=dpi)
            plt.xlim(-1.2, 1.2)
            plt.ylim(-1.2, 1.2)
            plt.scatter(xs, ys)
            for name, x, y in zip(names, xs, ys):
                plt.text(x, y, name)

            xls_file_path = pathlib.Path(pathlib.Path(xls_file).name).with_suffix('.png')
            plt.savefig(xls_file_path, transparent=True)


if __name__ == '__main__':
    main()


# References:
# https://psychophysiology.cpmc.columbia.edu/Software/CSDtoolbox/index.html
# [Pandas. How to read Excel file from ZIP archive](https://stackoverflow.com/questions/49157077/pandas-how-to-read-excel-file-from-zip-archive)
# [Import pandas dataframe column as string not int](https://stackoverflow.com/questions/13293810/import-pandas-dataframe-column-as-string-not-int)
# https://matplotlib.org/stable/api/_as_gen/matplotlib.pyplot.scatter.html
# [Changing file extension in Python](https://stackoverflow.com/questions/2900035/changing-file-extension-in-python)
# [Save plot to image file instead of displaying it using Matplotlib](https://stackoverflow.com/questions/9622163/save-plot-to-image-file-instead-of-displaying-it-using-matplotlib)
# [Specifying and saving a figure with exact size in pixels](https://stackoverflow.com/questions/13714454/specifying-and-saving-a-figure-with-exact-size-in-pixels)
# https://github.com/neuropsychology/TruScanEEGpy/blob/master/TruScanEEGpy/layouts/deymed_layout_128.txt
