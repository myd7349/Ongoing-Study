#include <stdlib.h>

char pear[40];
static double peach;
int mango = 13;
static long melon = 2001;

int main(void)
{
	int i = 3, j, *ip;

	ip = malloc(sizeof(i));

	pear[5] = i;

	peach = 2.0 * mango;

	return 0;
}

/*
$ nm -sS a.out
0000000000004020 B __bss_start
0000000000004020 0000000000000001 b completed.7963
                 w __cxa_finalize@@GLIBC_2.2.5
0000000000004000 D __data_start
0000000000004000 W data_start
0000000000001080 t deregister_tm_clones
00000000000010f0 t __do_global_dtors_aux
0000000000003dc0 t __do_global_dtors_aux_fini_array_entry
0000000000004008 D __dso_handle
0000000000003dc8 d _DYNAMIC
0000000000004020 D _edata
0000000000004068 B _end
00000000000011e4 T _fini
0000000000001130 t frame_dummy
0000000000003db8 t __frame_dummy_init_array_entry
0000000000002144 r __FRAME_END__
0000000000003fb8 d _GLOBAL_OFFSET_TABLE_
                 w __gmon_start__
0000000000002004 r __GNU_EH_FRAME_HDR
0000000000001000 t _init
0000000000003dc0 t __init_array_end
0000000000003db8 t __init_array_start
0000000000002000 0000000000000004 R _IO_stdin_used
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
00000000000011e0 0000000000000001 T __libc_csu_fini
0000000000001180 000000000000005d T __libc_csu_init
                 U __libc_start_main@@GLIBC_2.2.5
0000000000001135 0000000000000043 T main
                 U malloc@@GLIBC_2.2.5
0000000000004010 0000000000000004 D mango
0000000000004018 0000000000000008 d melon
0000000000004028 0000000000000008 b peach
0000000000004040 0000000000000028 B pear
00000000000010b0 t register_tm_clones
0000000000001050 000000000000002b T _start
0000000000004020 D __TMC_END__
*/

