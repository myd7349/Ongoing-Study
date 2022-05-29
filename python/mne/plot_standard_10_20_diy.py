#!/usr/bin/env python3
# coding: utf-8

from collections import OrderedDict
import json
from pprint import pprint

from matplotlib import rcParams
import matplotlib.pyplot as plt
import mne
import mne.channels
import numpy as np

CHANNELS = [
    'Fp1',
    'Fp2',
    'F7',
    'F3',
    'Fz',
    'F4',
    'F8',
    'T3',
    'C3',
    'Cz',
    'C4',
    'T4',
    'A1',
    'A2',
    'M1',
    'M2',
    'T5',
    'P3',
    'Pz',
    'P4',
    'T6',
    'O1',
    'O2',
]


def get_montage(name):
    return mne.channels.make_standard_montage(name)


def get_ch_pos(montage):
    return montage.get_positions()['ch_pos']


def get_mni_fiducials(subject):
    return mne._freesurfer.get_mni_fiducials(subject)


def auto_topomap_coords(ch_pos, sphere):
    ch_names = []
    out_list = []

    for ch_name, pos in ch_pos.items():
        if not ch_name in CHANNELS:
            continue

        ch_names.append(ch_name)

        # translate to sphere origin, transform/flatten Z, translate back
        pos -= sphere[:3]
        # use spherical (theta, pol) as (r, theta) for polar->cartesian
        if mne.__version__ == '1.0.3':
            pos = np.atleast_2d(pos)
        cart_coords = mne.transforms._cart_to_sph(pos)
        out = mne.transforms._pol_to_cart(cart_coords[:, 1:][:, ::-1])
        # scale from radians to mm
        out *= cart_coords[:, [0]] / (np.pi / 2.)
        out += sphere[:2]
        out_list.append(out[0])
    return ch_names, np.asarray(out_list)


def main():
    standard_1020_montage = get_montage('standard_1020')

    ch_pos = get_ch_pos(standard_1020_montage)
    pprint(ch_pos)

    lpa, nasion, rpa = [x['r'].copy() for x in get_mni_fiducials('fsaverage')]
    pprint(lpa)
    pprint(nasion)
    pprint(rpa)

    trans = mne.transforms.get_ras_to_neuromag_trans(nasion, lpa, rpa)
    pprint(trans)

    transformed_ch_pos = OrderedDict()
    for ch_name, pos in ch_pos.items():
        transformed_ch_pos[ch_name] = np.dot(pos, trans[:3, :3].T)
        transformed_ch_pos[ch_name] += trans[:3, 3]
    pprint(transformed_ch_pos)

    sphere = mne.utils.check._check_sphere(None)
    print(sphere)

    ch_names, elec_pos = auto_topomap_coords(transformed_ch_pos, sphere)
    pprint(elec_pos)

    outlines = mne.viz.topomap._make_head_outlines(sphere, elec_pos, 'head',
                                                   np.zeros((2, )))
    pprint(outlines)

    outlines_dict = dict()
    for key, value in outlines.items():
        if isinstance(value, np.ndarray):
            outlines_dict[key] = value.tolist()
        elif isinstance(value, tuple):
            is_ndarray = (isinstance(item, np.ndarray) for item in value)
            if all(is_ndarray):
                outlines_dict[key] = tuple(item.tolist() for item in value)
            else:
                outlines_dict[key] = value

    with open('head_outlines.json', 'w') as fp:
        json.dump(outlines_dict, fp, indent=4)

    subplot_kw = dict()
    fig, ax = plt.subplots(1,
                           figsize=(max(rcParams['figure.figsize']), ) * 2,
                           subplot_kw=subplot_kw)

    ax.text(0, 0, '', zorder=1)
    mne.viz.topomap._draw_outlines(ax, outlines)

    pointsize = 25
    linewidth = 1
    colors = ('k', ) * elec_pos.shape[0]
    edgecolors = ('black', ) * elec_pos.shape[0]
    pts = ax.scatter(elec_pos[:, 0],
                     elec_pos[:, 1],
                     picker=True,
                     clip_on=False,
                     c=colors,
                     edgecolors=edgecolors,
                     s=pointsize,
                     lw=linewidth)
    pprint(pts)

    fig.lasso = None

    # Equal aspect for 3D looks bad, so only use for 2D
    ax.set(aspect='equal')
    fig.subplots_adjust(left=0, bottom=0, right=1, top=1)
    ax.axis("off")  # remove border around figure

    for ch_name, pos in zip(ch_names, elec_pos):
        if ch_name in CHANNELS:
            ax.text(pos[0] + 0.0025, pos[1], ch_name, ha='left', va='center')

    pprint(dict(zip(ch_names, elec_pos)))

    elec_pos_dict = dict()
    for ch_name, pos in zip(ch_names, elec_pos):
        elec_pos_dict[ch_name] = pos.tolist()

    with open('elec_pos.json', 'w') as fp:
        json.dump(elec_pos_dict, fp, indent=4)

    T3_index = CHANNELS.index('T3')
    assert CHANNELS[T3_index] == 'T3'
    CHANNELS[T3_index] = 'T7'

    T4_index = CHANNELS.index('T4')
    assert CHANNELS[T4_index] == 'T4'
    CHANNELS[T4_index] = 'T8'

    T5_index = CHANNELS.index('T5')
    assert CHANNELS[T5_index] == 'T5'
    CHANNELS[T5_index] = 'P7'

    T6_index = CHANNELS.index('T6')
    assert CHANNELS[T6_index] == 'T6'
    CHANNELS[T6_index] = 'P8'

    standard_1020_montage.plot(show_names=CHANNELS, show=False)


if __name__ == '__main__':
    main()

# References:
# Ongoing-Study/python/mne/plot_standard_10_20.md
# https://docs.python.org/3/library/json.html
# https://numpy.org/doc/stable/reference/generated/numpy.ndarray.tolist.html
# [NumPy array is not JSON serializable](https://stackoverflow.com/questions/26646362/numpy-array-is-not-json-serializable)
