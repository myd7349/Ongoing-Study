// 2015-05-15T16:32+08:00
#include <cstdarg>
#include <cstdio>
#include <regex>

#include "../../common.h"

#ifdef WIN32
# include <windows.h>
inline void sleep_ms(unsigned int ms)
{
	Sleep(ms);
}
#else
# error Not tested yet!
void sleep_ms(unsigned int ms)
{
	struct timespec t;

	t.tv_sec  =  msecs / 1000;
	t.tv_nsec = (msecs % 1000) * 1000000;
	
	nanosleep(&t, NULL);
}
#endif

unsigned int count_d_format_spec(const char *format)
{
	if (nullptr == format) {
		return 0;
	}

	// Use <regex> to make sure that there is
	// %[flags][width][.precision][length]specifier 
	std::regex re("%"
		"[-+ 0]?"                  // flag
		"\\d*|\\*?"                // width
		"(?:.\\d+|.*)?"            // precision
		"(?:h{0,2}|l{0,2}|[jzt]?)" // length
		"[di]"                     // specifier
		);

	return 0;
}

void count_down(int start, int interval = 1000, const char *format = nullptr, ...)
{
	if (start <= 0) {
		return;
	}

	if (count_d_format_spec(format) != 1) {
		format = "%d\n";
	}

	char buffer[256];

	while (start >= 0) {
		std::va_list args;
	
		va_start(args, format);
		std::vsnprintf(buffer, ARRAYSIZE(buffer), format, args);
		va_end(args);

		std::printf("%s", buffer);
	}
}

int main()
{
	count_down(5, 1000, "Counting down: %d\n");

	return 0;
}