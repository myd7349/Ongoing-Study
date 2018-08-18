cmake_minimum_required (VERSION 3.8)
project ("tcpsrv")
add_executable (tcpsrv
    "tcpsrv.c"
	"startsrv_win32.c"
	"startsrv_posix.c"
	"../get_in_addr.c"
	"../tcpopt.c"
        "../../ttoi.c"
	"../../../algorithm/containers/dynamic_array.c"
	)
