// 2015-09-29T14:09+08:00
// Can we call mktime/localtime with datetime 1970-01-01T00:00:00+08:00?
#include <assert.h>
#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <time.h>

int main(void)
{
    const char *locales[] = {NULL, "", "C"};
    size_t i = 0;

    struct tm atm;
    time_t t;

    atm.tm_sec = 0;
    atm.tm_min = 0;
    atm.tm_hour = 0;
    atm.tm_mday = 1;
    atm.tm_mon = 1 - 1; // tm_mon is 0 based
    atm.tm_year = 1970 - 1900; // tm_year is 1900 based
    atm.tm_isdst = -1;

    for (i = 0; i < sizeof(locales)/sizeof(locales[0]); i++) {
        printf("Local is: %s\n", setlocale(LC_ALL, locales[i]));

        // In VS2010, _mktime64 calls _localtime64_s.
        t = mktime(&atm);
        if (t == -1)
            puts("Illegal time.");
    }

    return 0;
}

// In my case, the output is:
/*
Local is: C
Illegal time.
Local is: Chinese (Simplified)_People's Republic of China.936
Illegal time.
Local is: C
Illegal time.
*/

// http://coliru.stacked-crooked.com/
/*
Local is: C
Local is: C
Local is: C
*/

// http://webcompiler.cloudapp.net/
/*
Local is: C
Local is: English_United States.1252
Local is: C
*/

// http://melpon.org/wandbox/
/*
Local is: C
Local is: en_US.UTF-8
Local is: C
*/