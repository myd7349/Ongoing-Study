# -*- coding: utf-8 -*-

import io

from pcpp.preprocessor import Preprocessor  # pip install pcpp
from pycparser.c_parser import CParser  # pip install pycparser


code = '''
struct edf_param_struct{         /* this structure contains all the relevant EDF-signal parameters of one signal */
  char   label[17];              /* label (name) of the signal, null-terminated string */
  long long smp_in_file;         /* number of samples of this signal in the file */
  double phys_max;               /* physical maximum, usually the maximum input of the ADC */
  double phys_min;               /* physical minimum, usually the minimum input of the ADC */
  int    dig_max;                /* digital maximum, usually the maximum output of the ADC, cannot not be higher than 32767 for EDF or 8388607 for BDF */
  int    dig_min;                /* digital minimum, usually the minimum output of the ADC, cannot not be lower than -32768 for EDF or -8388608 for BDF */
  int    smp_in_datarecord;      /* number of samples of this signal in a datarecord, if the datarecord has a duration of one second (default), then it equals the samplerate */
  char   physdimension[9];       /* physical dimension (uV, bpm, mA, etc.), null-terminated string */
  char   prefilter[81];          /* null-terminated string */
  char   transducer[81];         /* null-terminated string */
      };
'''

# Output of C++ Insights(show padding information):
# struct edf_param_struct  /* size: 232, align: 8 */
# {
#   char label[17];                 /* offset: 0, size: 17
#   char __padding[7];                            size: 7 */
#   long long smp_in_file;          /* offset: 24, size: 8 */
#   double phys_max;                /* offset: 32, size: 8 */
#   double phys_min;                /* offset: 40, size: 8 */
#   int dig_max;                    /* offset: 48, size: 4 */
#   int dig_min;                    /* offset: 52, size: 4 */
#   int smp_in_datarecord;          /* offset: 56, size: 4 */
#   char physdimension[9];          /* offset: 60, size: 9 */
#   char prefilter[81];             /* offset: 69, size: 81 */
#   char transducer[81];            /* offset: 150, size: 81
#   char __padding[1];                            size: 1 */
# };


def cpp(code):
    preprocessor = Preprocessor()
    preprocessor.parse(code)

    sstream = io.StringIO()
    preprocessor.write(sstream)

    return sstream.getvalue()


preprocessed_code = cpp(code)
print(preprocessed_code)

parser = CParser()
ast = parser.parse(preprocessed_code)
print(ast)


# References:
# [How to use StringIO in Python3?](https://stackoverflow.com/questions/11914472/how-to-use-stringio-in-python3)
# https://www.liaoxuefeng.com/wiki/1016959663602400/1017609424203904
# https://github.com/andreasfertig/cppinsights/blob/a4c4796a057ffef597c77f8902249a9d1b884cca/CodeGenerator.cpp#L2501-L2542
