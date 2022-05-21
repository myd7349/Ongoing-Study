import mne
import mne.channels

import TruScanEEGpy

layout = TruScanEEGpy.layout_128('10-20')
print(layout)
montage = TruScanEEGpy.montage_mne_128(layout)
print(montage)
mne.viz.plot_montage(montage)

print(mne.channels.get_builtin_montages())
easycap_montage = mne.channels.make_standard_montage('standard_1020')
print(easycap_montage)

easycap_montage.plot()  # 2D
easycap_montage.plot(sphere='eeglab')  # 2D
fig = easycap_montage.plot(kind='3d', show=False)  # 3D
fig = fig.gca().view_init(azim=70, elev=15)  # set view angle for tutorial


# References:
# https://github.com/neuropsychology/TruScanEEGpy
# [Working with sensor locations](https://mne.tools/stable/auto_tutorials/intro/40_sensor_locations.html)
