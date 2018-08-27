#include <gtest/gtest.h>

#include <cstring>
#include <memory>

#include "../getprogname.h"


struct free_deleter
{
    void operator()(_TCHAR* x)
    {
        free(x);
    }
};


std::wstring GetProgName(const _TCHAR *s)
{
    std::unique_ptr<_TCHAR, free_deleter> title(getprogname(s), free_deleter());
    if (title)
        return title.get();
    else
        return std::wstring();
}


bool IsProgNameEqualTo(const _TCHAR *s, const _TCHAR *progname)
{
    return GetProgName(s) == progname;
}


TEST(GetProgNameTest, ProgWithNoPathSep)
{
    EXPECT_TRUE(IsProgNameEqualTo(_T("a.out"), _T("a")));
    EXPECT_TRUE(IsProgNameEqualTo(_T("cat"), _T("cat")));
    EXPECT_TRUE(IsProgNameEqualTo(_T("cat.dog.exe"), _T("cat.dog")));
}


TEST(GetProgNameTest, ProgWithPathSep)
{
    EXPECT_TRUE(IsProgNameEqualTo(_T("./a.out"), _T("a")));
    EXPECT_TRUE(IsProgNameEqualTo(_T("C:\\a.out"), _T("a")));
    EXPECT_TRUE(IsProgNameEqualTo(_T(".etc/a.out"), _T("a")));
    EXPECT_TRUE(IsProgNameEqualTo(_T("/a/b"), _T("b")));
    EXPECT_TRUE(IsProgNameEqualTo(_T("/a/b/"), _T("")));
}


// References:
// https://stackoverflow.com/questions/3477525/is-it-possible-to-use-a-c-smart-pointers-together-with-cs-malloc
