```python
#!/usr/bin/env python3
# coding: utf-8

from collections import OrderedDict
from pprint import pprint

import mne.channels


CHANNELS = frozenset((
    'Fp1', 'Fp2',
    'F7', 'F3', 'Fz', 'F4', 'F8',
    'T3', 'C3', 'Cz', 'C4', 'T4',
    'A1', 'A2', 'M1', 'M2',
    'T5', 'P3', 'Pz', 'P4', 'T6',
    'O1', 'O2',
))


def get_montage(name):
    return mne.channels.make_standard_montage(name)


def get_ch_pos(montage):
    return montage.get_positions()['ch_pos']


def main():
    standard_1020_montage = get_montage('standard_1020')
    ch_pos = get_ch_pos(standard_1020_montage)

    pprint(ch_pos)

    channels_pos = OrderedDict()
    for ch, pos in ch_pos.items():
        if ch in CHANNELS:
            channels_pos[ch] = pos
    pprint(channels_pos)

    standard_1020_montage.plot(
        show_names=CHANNELS,
        show=False)


if __name__ == '__main__':
    main()
```

### mne.channels.make_standard_montage

[make_standard_montage@channels/montage.py#L1486](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/channels/montage.py#L1486)

- [standard_1020@channels/_standard_montage_utils.py#L148](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/channels/_standard_montage_utils.py#L148)

- [_mgh_or_standard@channels/_standard_montage_utils.py#L77](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/channels/_standard_montage_utils.py#L77)
  
  1. Read electrode positions from file `Read elec loc from file Python39\site-packages\mne\channels\data\montages\standard_1020.elc`;
  
  2. pos = np.array(pos) / 1000.(unit: mm -> m);
  
  3. If we are in MRI/MNI coordinates, we need to replace nasion, LPA, and RPA with those of fsaverage for ``trans='fsaverage'`` to work:
     
     [get_mni_fiducials@_freesurfer.py#L378](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/_freesurfer.py#L378)
     
     This will read file Read from Python\Python39\site-packages\mne\data\fsaverage\fsaverage-fiducials.fif, the return values:
     
     > nasion: 1.467630383558571339e-03 8.506715297698974609e-02 -3.483611345291137695e-02
     > 
     > lpa: -8.061611652374267578e-02 -2.908875234425067902e-02 -4.131076857447624207e-02
     > 
     > rpa: 8.436284959316253662e-02 -2.850276418030261993e-02 -4.127743467688560486e-02
  
  4. [make_dig_montage](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/channels/_standard_montage_utils.py#L115)

     [make_dig_montage@channels/montage.py#L80](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/channels/montage.py#L80)

### mne.channels.montage.DigMontage.plot

[plot_montage@viz/montage.py#L10](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/viz/montage.py#L10)

- [raw.set_montage(montage, on_missing='ignore')](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/viz/montage.py#L71)
  
  [set_montage@io/meas_info.py#L191](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/io/meas_info.py#L191)
  
  - [_set_montage(info, montage, match_case, match_alias, on_missing](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/io/meas_info.py#L223)
    
    [_set_montage@channels/montage.py#L894](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/channels/montage.py#L894)
    
    - [mnt_head = _get_montage_in_head(montage)](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/channels/montage.py#L929)
      
      [_get_montage_in_head@channels/montage.py#L851](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/channels/montage.py#L851)
      
      - [return transform_to_head(montage.copy())](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/channels/montage.py#L856)
        
        [transform_to_head@channels/montage.py#L504](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/channels/montage.py#L504)
        
        - [native_head_t = compute_native_head_t(montage)](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/channels/montage.py#L525)
          
          [compute_native_head_t@channels/montage.py#L1449](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/channels/montage.py#L1449)
          
          - [native_head_t = get_ras_to_neuromag_trans](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/channels/montage.py#L1481)
            
            [get_ras_to_neuromag_trans@transforms.py#L640](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/transforms.py#L640)
            
            Please read the `__doc__` of this function carefully and make sure you understand how transform matrix is calculated.
            
            > 9.999936819076538086e-01  3.551873844116926193e-03    2.020481042563915253e-04    -1.762724952529908483e-03
            > 
            > -3.557568648830056190e-03    9.983891248703002930e-01    5.662585794925689697e-02    3.109435042779478894e-02
            > 
            > -5.947367753833532333e-07    -5.662621930241584778e-02    9.983954429626464844e-01    3.959724907613275391e-02
            > 
            > 0.000000000000000000e+00    0.000000000000000000e+00    0.000000000000000000e+00    1.000000000000000000e+00
        
        - [d['r'] = apply_trans(native_head_t, d['r'])](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/channels/montage.py#L530)
          
          [apply_trans@transforms.py#L216](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/transforms.py#L216)
      
      - [ch_pos = mnt_head._get_ch_pos()](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/channels/montage.py#L939)
      
      - [eeg_ref_pos = np.zeros(3) if not(refs) else ch_pos.pop(refs.pop())](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/channels/montage.py#L967)

- [fig = plot_sensors](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/viz/montage.py#L72)
  
  [plot_sensorsviz/utils.py#L861](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/viz/utils.py#L861)
  
  - [fig = _plot_sensors](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/viz/utils.py#L1026)
    
    [_plot_sensors@viz/utils.py#L1068](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/viz/utils.py#L1068)
    
    - [sphere = _check_sphere(sphere, info)](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/viz/utils.py#L1076)
      
      [_check_sphere@utils/check.py#L801](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/utils/check.py#L801)
      
      - [sphere = HEAD_SIZE_DEFAULT](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/utils/check.py#L805)
        
        [HEAD_SIZE_DEFAULT = 0.095 # in \[m\]@defaults.py#L192](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/defaults.py#L192)
    
    - [pos, outlines = _get_pos_outlines(info, picks, sphere, to_sphere=to_sphere](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/viz/utils.py#L1107)
      
      [_get_pos_outlines@viz/topomap.py#L676](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/viz/topomap.py#L676)
      
      - [pos = _find_topomap_coords](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/viz/topomap.py#L682)
        
        [_find_topomap_coords@channels/layout.py#L597](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/channels/layout.py#L597)
        
        - [pos = _auto_topomap_coords](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/channels/layout.py#L625)
          
          [_auto_topomap_coords@channels/layout.py#L633](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/channels/layout.py#L633)
          
          - [cart_coords = _cart_to_sph(locs3d](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/channels/layout.py#L732)
            
            [_cart_to_sph@transforms.py#L711](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/transforms.py#L711)
          
          - [out = _pol_to_cart(cart_coords[:, 1:][:, ::-1])](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/channels/layout.py#L733)
            
            [_pol_to_cart@transforms.py#L1150](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/transforms.py#L1150)
      
      - [outlines = _make_head_outlines](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/viz/topomap.py#L685)
        
        [make_head_outlines@viz/topomap.py#L408](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/viz/topomap.py#L408)
    
    - [_draw_outlines(ax, outlines)](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/viz/utils.py#L1109)
      
      [_draw_outlines@viz/topomap.py#L457](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/viz/topomap.py#L457)
    
    - [pts = ax.scatter](https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/viz/utils.py#L1110)
