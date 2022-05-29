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
    'PG1',
    'PG2',
    'T1',  # Near FT9
    'T2',  # Near FT10
    'AF9',
    'AF10',
    'FT9',
    'FT10',
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


def adjust_elec_pos(ch_names, elec_pos):
    R = mne.defaults.HEAD_SIZE_DEFAULT

    P = lambda n: elec_pos[ch_names.index(n)]

    P('Cz')[1] = 0

    P('A1')[0] = -P('A2')[0]
    P('M1')[0] = -P('M2')[0]

    P('T3')[0] = P('Cz')[0] - 2 * R * 0.4
    P('T3')[1] = P('Cz')[1]

    P('C3')[0] = P('Cz')[0] - 2 * R * 0.2
    P('C3')[1] = P('Cz')[1]

    P('C4')[0] = P('Cz')[0] + 2 * R * 0.2
    P('C4')[1] = P('Cz')[1]

    P('T4')[0] = P('Cz')[0] + 2 * R * 0.4
    P('T4')[1] = P('Cz')[1]

    P('Fz')[0] = P('Cz')[0]
    P('Fz')[1] = P('Cz')[1] + 2 * R * 0.2

    P('Pz')[0] = P('Cz')[0]
    P('Pz')[1] = P('Cz')[1] - 2 * R * 0.2

    F4_Cz_C4_rad = 0.5 * np.pi / 2.0
    F4_Cz_dist = 2 * R * 0.2

    P('F4')[0] = P('Cz')[0] + F4_Cz_dist * np.cos(F4_Cz_C4_rad)
    P('F4')[1] = P('Cz')[1] + F4_Cz_dist * np.sin(F4_Cz_C4_rad)

    P('F3')[0] = 2 * P('Cz')[0] - P('F4')[0]
    P('F3')[1] = P('F4')[1]

    P('P3')[0] = P('F3')[0]
    P('P3')[1] = -P('F3')[1]

    P('P4')[0] = P('F4')[0]
    P('P4')[1] = -P('F4')[1]

    Fp2_Cz_C4_rad = 0.8 * np.pi / 2
    Fp2_Cz_dist = 2 * R * 0.4

    P('Fp2')[0] = P('Cz')[0] + Fp2_Cz_dist * np.cos(Fp2_Cz_C4_rad)
    P('Fp2')[1] = P('Cz')[1] + Fp2_Cz_dist * np.sin(Fp2_Cz_C4_rad)

    P('Fp1')[0] = -P('Fp2')[0]
    P('Fp1')[1] = P('Fp2')[1]

    F8_Cz_C4_rad = 0.4 * np.pi / 2

    P('F8')[0] = P('Cz')[0] + Fp2_Cz_dist * np.cos(F8_Cz_C4_rad)
    P('F8')[1] = P('Cz')[1] + Fp2_Cz_dist * np.sin(F8_Cz_C4_rad)

    P('F7')[0] = -P('F8')[0]
    P('F7')[1] = P('F8')[1]

    P('O1')[0] = P('Fp1')[0]
    P('O1')[1] = -P('Fp1')[1]

    P('O2')[0] = P('Fp2')[0]
    P('O2')[1] = -P('Fp2')[1]

    P('T5')[0] = P('F7')[0]
    P('T5')[1] = -P('F7')[1]

    P('T6')[0] = P('F8')[0]
    P('T6')[1] = -P('F8')[1]

    return ch_names, elec_pos


def adjust_elec_pos_v2(ch_names, elec_pos):
    R = mne.defaults.HEAD_SIZE_DEFAULT

    P = lambda n: elec_pos[ch_names.index(n)]

    P('Cz')[1] = 0

    P('A1')[0] = -P('A2')[0]
    P('M1')[0] = -P('M2')[0]

    P('T3')[0] = P('Cz')[0] - 2 * R * 0.4
    P('T3')[1] = P('Cz')[1]

    P('C3')[0] = P('Cz')[0] - 2 * R * 0.2
    P('C3')[1] = P('Cz')[1]

    P('C4')[0] = P('Cz')[0] + 2 * R * 0.2
    P('C4')[1] = P('Cz')[1]

    P('T4')[0] = P('Cz')[0] + 2 * R * 0.4
    P('T4')[1] = P('Cz')[1]

    P('Fz')[0] = P('Cz')[0]
    P('Fz')[1] = P('Cz')[1] + 2 * R * 0.2

    P('Pz')[0] = P('Cz')[0]
    P('Pz')[1] = P('Cz')[1] - 2 * R * 0.2

    Fp2_Cz_C4_rad = 0.8 * np.pi / 2
    Fp2_Cz_dist = 2 * R * 0.4

    P('Fp2')[0] = P('Cz')[0] + Fp2_Cz_dist * np.cos(Fp2_Cz_C4_rad)
    P('Fp2')[1] = P('Cz')[1] + Fp2_Cz_dist * np.sin(Fp2_Cz_C4_rad)

    P('Fp1')[0] = -P('Fp2')[0]
    P('Fp1')[1] = P('Fp2')[1]

    F8_Cz_C4_rad = 0.4 * np.pi / 2

    P('F8')[0] = P('Cz')[0] + Fp2_Cz_dist * np.cos(F8_Cz_C4_rad)
    P('F8')[1] = P('Cz')[1] + Fp2_Cz_dist * np.sin(F8_Cz_C4_rad)

    P('F7')[0] = -P('F8')[0]
    P('F7')[1] = P('F8')[1]

    P('O1')[0] = P('Fp1')[0]
    P('O1')[1] = -P('Fp1')[1]

    P('O2')[0] = P('Fp2')[0]
    P('O2')[1] = -P('Fp2')[1]

    P('T5')[0] = P('F7')[0]
    P('T5')[1] = -P('F7')[1]

    P('T6')[0] = P('F8')[0]
    P('T6')[1] = -P('F8')[1]

    P('F4')[0] = (P('Fz')[0] + P('F8')[0]) / 2
    P('F4')[1] = P('Fz')[1]

    P('F3')[0] = 2 * P('Cz')[0] - P('F4')[0]
    P('F3')[1] = P('F4')[1]

    P('P3')[0] = P('F3')[0]
    P('P3')[1] = -P('F3')[1]

    P('P4')[0] = P('F4')[0]
    P('P4')[1] = -P('F4')[1]

    return ch_names, elec_pos


def adjust_elec_pos_v3(ch_names, elec_pos):
    R = mne.defaults.HEAD_SIZE_DEFAULT

    P = lambda n: elec_pos[ch_names.index(n)]

    P('Cz')[1] = 0

    P('A1')[0] = -P('A2')[0]
    P('M1')[0] = -P('M2')[0]

    P('T3')[0] = P('Cz')[0] - 2 * R * 0.4
    P('T3')[1] = P('Cz')[1]

    P('C3')[0] = P('Cz')[0] - 2 * R * 0.2
    P('C3')[1] = P('Cz')[1]

    P('C4')[0] = P('Cz')[0] + 2 * R * 0.2
    P('C4')[1] = P('Cz')[1]

    P('T4')[0] = P('Cz')[0] + 2 * R * 0.4
    P('T4')[1] = P('Cz')[1]

    P('F7')[0] = P('T3')[0]
    P('F7')[1] = P('T3')[1] + 2 * R * 0.2

    P('F3')[0] = P('C3')[0]
    P('F3')[1] = P('C3')[1] + 2 * R * 0.2

    P('Fz')[0] = P('Cz')[0]
    P('Fz')[1] = P('Cz')[1] + 2 * R * 0.2

    P('F4')[0] = P('C4')[0]
    P('F4')[1] = P('C4')[1] + 2 * R * 0.2

    P('F8')[0] = P('T4')[0]
    P('F8')[1] = P('T4')[1] + 2 * R * 0.2

    P('T5')[0] = P('F7')[0]
    P('T5')[1] = -P('F7')[1]

    P('P3')[0] = P('F3')[0]
    P('P3')[1] = -P('F3')[1]

    P('Pz')[0] = P('Fz')[0]
    P('Pz')[1] = -P('Fz')[1]

    P('P4')[0] = P('F4')[0]
    P('P4')[1] = -P('F4')[1]

    P('T6')[0] = P('F8')[0]
    P('T6')[1] = -P('F8')[1]

    P('Fp1')[0] = P('F3')[0]
    P('Fp1')[1] = P('F3')[1] + 2 * R * 0.2

    P('Fp2')[0] = -P('Fp1')[0]
    P('Fp2')[1] = P('Fp1')[1]

    P('O1')[0] = P('Fp1')[0]
    P('O1')[1] = -P('Fp1')[1]

    P('O2')[0] = P('Fp2')[0]
    P('O2')[1] = -P('Fp2')[1]

    return ch_names, elec_pos


def plot_montage(sphere, outlines, ch_names, elec_pos):
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
    ax.scatter(elec_pos[:, 0],
               elec_pos[:, 1],
               picker=True,
               clip_on=False,
               c=colors,
               edgecolors=edgecolors,
               s=pointsize,
               lw=linewidth)

    fig.lasso = None

    # Equal aspect for 3D looks bad, so only use for 2D
    ax.set(aspect='equal')
    fig.subplots_adjust(left=0, bottom=0, right=1, top=1)
    #ax.axis("off")  # remove border around figure

    for ch_name, pos in zip(ch_names, elec_pos):
        if ch_name in CHANNELS:
            ax.text(pos[0] + 0.0025, pos[1], ch_name, ha='left', va='center')


def main():
    standard_1020_montage = get_montage('standard_1020')

    ch_pos = get_ch_pos(standard_1020_montage)

    lpa, nasion, rpa = [x['r'].copy() for x in get_mni_fiducials('fsaverage')]
    pprint(lpa)
    pprint(nasion)
    pprint(rpa)

    trans = mne.transforms.get_ras_to_neuromag_trans(nasion, lpa, rpa)

    transformed_ch_pos = OrderedDict()
    for ch_name, pos in ch_pos.items():
        transformed_ch_pos[ch_name] = np.dot(pos, trans[:3, :3].T)
        transformed_ch_pos[ch_name] += trans[:3, 3]

    sphere = mne.utils.check._check_sphere(None)

    ch_names, elec_pos = auto_topomap_coords(transformed_ch_pos, sphere)

    outlines = mne.viz.topomap._make_head_outlines(sphere, elec_pos, 'head',
                                                   np.zeros((2, )))

    outlines_dict = OrderedDict()
    for key, value in outlines.items():
        if 'mask' in key or key in ('clip_radius', 'clip_origin'):
            continue

        if isinstance(value, np.ndarray):
            outlines_dict[key] = value.tolist()
        elif isinstance(value, tuple):
            is_ndarray = (isinstance(item, np.ndarray) for item in value)
            if all(is_ndarray):
                outlines_dict[key] = tuple(item.tolist() for item in value)
            else:
                outlines_dict[key] = value

    with open('head.json', 'w') as fp:
        json.dump(outlines_dict, fp, indent=4)

    ch_names[ch_names.index('FT9')] = 'T1'
    ch_names[ch_names.index('FT10')] = 'T2'
    ch_names[ch_names.index('AF9')] = 'PG1'
    ch_names[ch_names.index('AF10')] = 'PG2'

    ch_names, elec_pos = adjust_elec_pos(ch_names, elec_pos)
    plot_montage(sphere, outlines, ch_names, elec_pos)

    ch_names, elec_pos = adjust_elec_pos_v2(ch_names, elec_pos)
    plot_montage(sphere, outlines, ch_names, elec_pos)

    ch_names, elec_pos = adjust_elec_pos_v3(ch_names, elec_pos)
    plot_montage(sphere, outlines, ch_names, elec_pos)

    ch_names, elec_pos = adjust_elec_pos_v2(ch_names, elec_pos)

    elec_pos_dict = OrderedDict()
    for ch_name, pos in zip(ch_names, elec_pos):
        elec_pos_dict[ch_name] = pos.tolist()

    with open('elec.json', 'w') as fp:
        json.dump(elec_pos_dict, fp, indent=4)

    #mne.viz.plot_montage(standard_1020_montage)
    standard_1020_montage.plot()


if __name__ == '__main__':
    main()
