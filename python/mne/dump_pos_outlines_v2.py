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
    a1_index = ch_names.index('A1')
    a2_index = ch_names.index('A2')

    m1_index = ch_names.index('M1')
    m2_index = ch_names.index('M2')

    elec_pos[a1_index][0] = -elec_pos[a2_index][0]
    elec_pos[m1_index][0] = -elec_pos[m2_index][0]

    cz_index = ch_names.index('Cz')

    fp1_index = ch_names.index('Fp1')
    fp2_index = ch_names.index('Fp2')
    f7_index = ch_names.index('F7')
    f8_index = ch_names.index('F8')
    f4_index = ch_names.index('F4')
    fz_index = ch_names.index('Fz')

    ch_names.append('PG1')
    ch_names.append('PG2')
    ch_names.append('T1')
    ch_names.append('T2')

    pg1_y = elec_pos[fp2_index][1] + (elec_pos[fp2_index][1] -
                                      elec_pos[f4_index][1]) / 2
    t1_y = (elec_pos[fp1_index][1] + elec_pos[fz_index][1]) / 2

    elec_pos = np.vstack([
        elec_pos,
        [(elec_pos[fp1_index][0] + elec_pos[f7_index][0]) / 2, pg1_y],
        [(elec_pos[fp2_index][0] + elec_pos[f8_index][0]) / 2, pg1_y],
        [(elec_pos[a1_index][0] + elec_pos[f7_index][0]) / 2, t1_y],
        [(elec_pos[a2_index][0] + elec_pos[f8_index][0]) / 2, t1_y],
    ])

    assert len(ch_names) == elec_pos.shape[0]

    for ch_name, pos in zip(ch_names, elec_pos):
        if ch_name in ('A1', 'A2', 'M1', 'M2', 'AF9', 'AF10', 'FT9', 'FT10',
                       'Cz'):
            continue

        pos[1] -= elec_pos[cz_index][1]

    elec_pos[cz_index][1] = 0

    return ch_names, elec_pos


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
    print(sphere)

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

    subplot_kw = dict()
    fig, ax = plt.subplots(1,
                           figsize=(max(rcParams['figure.figsize']), ) * 2,
                           subplot_kw=subplot_kw)

    ax.text(0, 0, '', zorder=1)
    mne.viz.topomap._draw_outlines(ax, outlines)

    ch_names, elec_pos = adjust_elec_pos(ch_names, elec_pos)

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

    elec_pos_dict = OrderedDict()
    for ch_name, pos in zip(ch_names, elec_pos):
        elec_pos_dict[ch_name] = pos.tolist()

    pprint(elec_pos_dict)

    with open('elec.json', 'w') as fp:
        json.dump(elec_pos_dict, fp, indent=4)

    #mne.viz.plot_montage(standard_1020_montage)
    standard_1020_montage.plot()


if __name__ == '__main__':
    main()
