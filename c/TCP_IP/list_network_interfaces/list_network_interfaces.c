#ifdef WIN32
#include "list_network_interfaces.win32.c"
#else
#include "list_network_interfaces.linux.c"
#endif
