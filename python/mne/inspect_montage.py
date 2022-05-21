#!/usr/bin/env python3
# coding: utf-8
# runfile('./inspect_montage.py', wdir='./', args='-m standard_1020 -p -P --csharp --show-names Fp1 Fp2 F3 F4 C3 C4 P3 P4 O1 O2 F7 F8 T3 T4 T5 T6 Fz Cz Pz --ch-names')

import argparse
from collections import OrderedDict
from pprint import pprint
import os.path
import string
import sys

import mne
import mne.channels


def perror(*args, **kwargs):
    print(*args, **kwargs, file=sys.stderr)


def main():
    prog = os.path.splitext(os.path.basename(sys.argv[0]))[0]

    parser = argparse.ArgumentParser(
        prog=prog,
        description='Get EEG sensor locations.',
    )
    parser.add_argument('-l',
                        '--list',
                        action='store_true',
                        help='Get a list of builtin montages')
    parser.add_argument('-m', '--montage', help='Specify montage name')
    parser.add_argument('-p',
                        '--position',
                        action='store_true',
                        help='Get sensor positions')
    parser.add_argument('--csharp',
                        action='store_true',
                        help='Generate C# code')
    parser.add_argument('--csv', action='store_true', help='Generate CSV')
    parser.add_argument('--ch-names',
                        action='store_true',
                        help='Show channel names')
    parser.add_argument('-P',
                        '--plot',
                        action='store_true',
                        help='Plot montage')
    parser.add_argument('-s',
                        '--sphere',
                        choices=('auto', 'select', 'eeglab'),
                        default='mne',
                        help='Specify sphere')
    parser.add_argument('-k',
                        '--kind',
                        choices=('topomap', '3d'),
                        default='topomap',
                        help='Specify sphere')
    parser.add_argument('--show-names',
                        nargs='+',
                        type=str,
                        help='True, False, or a list of sensor names')

    args = parser.parse_args()

    builtin_motages = mne.channels.get_builtin_montages()

    if args.list:
        pprint(builtin_motages)
        sys.exit(0)

    if not args.montage:
        perror('-m/--montage is required.')
        sys.exit(1)

    if args.montage not in builtin_motages:
        perror(
            f'Unknown montage "{args.montage}". To get a list of builtin montages, use -l/--list argument.'
        )
        sys.exit(1)

    montage = mne.channels.make_standard_montage(args.montage)

    if args.ch_names:
        pprint(montage.ch_names)

    show_names = True
    if args.show_names:
        if len(args.show_names) == 1:
            b = args.show_names[0].casefold()
            if b in ('true', 'false'):
                show_names = b in ('true', )
            else:
                show_names = args.show_names
        else:
            show_names = args.show_names

    if args.position:
        ch_pos_dict = montage.get_positions()['ch_pos']

        #if show_names is bool:
        if type(show_names) is bool:
            pprint(ch_pos_dict)
        else:
            ch_pos_dict_icase = OrderedDict(
                zip(map(str.lower, ch_pos_dict.keys()), ch_pos_dict.values()))

            ch_pos_dict = OrderedDict()
            i = 0
            for channel in map(str.lower, show_names):
                ch_pos_dict[show_names[i]] = ch_pos_dict_icase[channel]
                i += 1

            pprint(ch_pos_dict)

        if args.csharp:
            coord_template = string.Template(
                '["$electrode"] = new Point3D($x, $y, $z),')

            for ch, pos in ch_pos_dict.items():
                print(
                    coord_template.substitute(electrode=ch,
                                              x=pos[0],
                                              y=pos[1],
                                              z=pos[2]))

        if args.csv:
            for ch, pos in ch_pos_dict.items():
                print(f'{ch},{pos[0]},{pos[1]},{pos[2]}')

    if args.plot:
        sphere = 'eeglab' if args.sphere == 'eeglab' else None

        #if not show_names is bool:
        if not type(show_names) is bool:
            for i in range(len(show_names)):
                if show_names[i] == 'T3':
                    show_names[i] = 'T7'
                elif show_names[i] == 'T4':
                    show_names[i] = 'T8'
                elif show_names[i] == 'T5':
                    show_names[i] = 'P7'
                elif show_names[i] == 'T6':
                    show_names[i] = 'P8'

        if args.kind == '3d':
            fig = montage.plot(sphere=sphere,
                               kind=args.kind,
                               show=False,
                               show_names=show_names)
            fig.gca().view_init(azim=70, elev=15)
        else:
            montage.plot(sphere=sphere, kind=args.kind, show_names=show_names)


if __name__ == '__main__':
    main()

# References:
# https://github.com/neuropsychology/TruScanEEGpy
# [Working with sensor locations](https://mne.tools/stable/auto_tutorials/intro/40_sensor_locations.html)
# https://github.com/mne-tools/mne-python/blob/main/mne/viz/montage.py
# https://github.com/mne-tools/mne-python/blob/main/mne/viz/utils.py
# [Converting from a string to boolean in Python](https://stackoverflow.com/questions/715417/converting-from-a-string-to-boolean-in-python)
# [Case insensitive dictionary](https://stackoverflow.com/questions/2082152/case-insensitive-dictionary)
# https://en.wikipedia.org/wiki/10%E2%80%9320_system_(EEG)
