#include <assert.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>


int main()
{
    wchar_t ch;
    unsigned char buf[2];

    _wsetlocale(LC_ALL, L"");

    FILE *fp = _wfopen(L"colon.txt", L"w+");
    if (fp != NULL)
    {
        int ret = fwprintf(fp, L"：");
        assert(ret != -1);

        rewind(fp);

        fwscanf(fp, L"%c", &ch);
        fwprintf(stdout, L"%c\n", ch);

        rewind(fp);

#if 0
        ret = fread(buf, sizeof(buf[0]), _countof(buf), fp);
        ch = *(const wchar_t *)buf;
        fwprintf(stdout, L"%c\n", ch);
#endif

        fclose(fp);
    }

    return 0;
}
