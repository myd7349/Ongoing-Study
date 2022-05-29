#! /usr/bin/env python3
# -*- coding: utf-8 -*-

import tkinter as tk
import tkinter.filedialog as filedialog

import mne.io

root = tk.Tk()
root.withdraw()


def select_edf_file():
    return filedialog.askopenfilename(title='Select a EDF(+)/BDF(+) file:',
                                      filetypes=(('EDF/EDF+ Files', '.edf'),
                                                 ('BDF/BDF+ Files',
                                                  '.bdf'), ('All Files', '*')),
                                      multiple=False)


def main():
    edf_fname = select_edf_file()
    raw_edf = mne.io.read_raw_edf(edf_fname)
    raw_edf.plot()

    raw_avg_ref = raw_edf.copy()
    raw_avg_ref.load_data()
    raw_avg_ref.set_eeg_reference(ref_channels='average')
    raw_avg_ref.plot()


if __name__ == '__main__':
    main()


# References:
# [Quick and easy file dialog in Python?](https://stackoverflow.com/questions/9319317/quick-and-easy-file-dialog-in-python)
# https://docs.python.org/3/library/dialog.html
# [Setting the EEG reference](https://mne.tools/0.22/auto_tutorials/preprocessing/plot_55_setting_eeg_reference.html)
