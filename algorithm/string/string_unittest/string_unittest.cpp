#include <gtest/gtest.h>

#include <cstring>
#include <memory>

#include "../stringview.h"
#include "../substr.h"


#ifdef _MSC_VER
#pragma warning(disble: 4251)
#endif


struct free_deleter
{
    void operator()(_TCHAR* x)
    {
        free(x);
    }
};



TEST(StringTest, Test_stringview_substr)
{
    const _TCHAR *s = _T("Hello, world!");
    stringview_t view = stringview_substr(s, 0, stringview_npos);
    EXPECT_EQ(view.cbegin, s);
    EXPECT_EQ(view.count, _tcslen(s));

    view = stringview_substr(s, 0, 5);
    EXPECT_EQ(view.cbegin, s);
    EXPECT_EQ(view.count, 5);

    view = stringview_substr(s, 13, stringview_npos);
    EXPECT_EQ(view.cbegin, s + _tcslen(s));
    EXPECT_EQ(view.count, 0);

    view = stringview_substr(s, 7, 5);
    EXPECT_EQ(memcmp(view.cbegin, _T("world"), _tcslen(_T("world")) * sizeof(_TCHAR)), 0);
    EXPECT_EQ(view.count, 5);
}


TEST(StringTest, Test_substr)
{
    std::unique_ptr<_TCHAR, free_deleter> s(substr(_T("datadata.txt"), 4, 7), free_deleter());
    EXPECT_STREQ(s.get(), _T("data.tx"));
}


TEST(StringTest, Test_stringview_substr_insitu)
{
    EXPECT_STREQ(substr_insitu(_T("datadata.txt"), 9, str_npos), _T("txt"));
    EXPECT_STREQ(substr_insitu(_T("datadata.txt"), 8, str_npos), _T(".txt"));

    EXPECT_STREQ(substr_insitu(_T("datadata.txt"), 0, str_npos), _T("datadata.txt"));
    EXPECT_STREQ(substr_insitu(_T("datadata.txt"), 4, str_npos), _T("data.txt"));

    EXPECT_EQ(substr_insitu(_T("datadata.txt"), 4, 7), static_cast<const _TCHAR *>(NULL));
    EXPECT_STREQ(substr_insitu(_T("datadata.txt"), 4, 8), _T("data.txt"));
    EXPECT_STREQ(substr_insitu(_T("datadata.txt"), 4, 9), _T("data.txt"));
}


// References:
// https://stackoverflow.com/questions/30339692/disable-the-warning-of-specific-libraries-by-cmake
// https://stackoverflow.com/questions/2368811/how-to-set-warning-level-in-cmake
// https://stackoverflow.com/questions/3477525/is-it-possible-to-use-a-c-smart-pointers-together-with-cs-malloc
