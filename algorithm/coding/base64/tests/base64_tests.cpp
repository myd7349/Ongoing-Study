#include <cassert>
#include <iostream>
#include <cstdlib>
#include <cstring>

#include "../base64.h"
#include "dump.h"


static void test(const char *data, size_t len, const char *expected, B64_FLAGS flags)
{
    if (len == 0)
        len = std::strlen(data);

    std::string base64 = base64_encode(data, len, flags);

    std::cout << "------------------------------------------------------------\n";

    std::cout << "Raw    (" << len << "): ";
    dump_data(data, len);

    std::cout << "Encoded(" << base64.length() << "): " << base64 << '\n';

    if (!base64.empty())
    {
        bool ok = base64 == expected;
        assert(ok);
        if (!ok)
            std::exit(EXIT_FAILURE);
    }

    std::vector<unsigned char> decoded = base64_decode(base64, flags);
    std::cout << "Decoded(" << decoded.size() << "): ";
    dump_data(decoded.data(), decoded.size());

    assert(decoded.size() == len);
    assert(std::memcmp(data, decoded.data(), len) == 0);
}


int main(void)
{
    unsigned char data[] =
    {
        0x04, 'B', '<', 0x96, 0xaa, 0x0e, 0xda, 'e',  0x94,
        'U',  '{', 0xd5, ']', 0xaa, 't',  0xb6, 0xd5, '_'
    };
    unsigned char data2[] = { 0x99, 0x00, '`', 0xd2, 'R', 0xae };
    unsigned char data3[] = { 0xce, '_', '{', 0xad };

    test("", 0, "", B64F_NORMAL);
    test("\0", 1, "AA==", B64F_NORMAL);
    test("\0", 1, "AA", static_cast<B64_FLAGS>(B64F_NORMAL | B64F_NO_PADDING));
    test("\0\0", 2, "AAA=", B64F_NORMAL);
    test("\0\0", 2, "AAA", static_cast<B64_FLAGS>(B64F_NORMAL | B64F_NO_PADDING));
    test("\0\0\0", 3, "AAAA", B64F_NORMAL);
    test("hello, world", 0, "aGVsbG8sIHdvcmxk", B64F_NORMAL);
    test("hello, world!", 0, "aGVsbG8sIHdvcmxkIQ==", B64F_NORMAL);
    test("hello, world!", 0, "aGVsbG8sIHdvcmxkIQ", static_cast<B64_FLAGS>(B64F_NORMAL | B64F_NO_PADDING));

    test((const char *)data, sizeof(data), "BEI8lqoO2mWUVXvVXap0ttVf", B64F_NORMAL);
    test((const char *)data2, sizeof(data2), "mQBg0lKu", B64F_NORMAL);
    test((const char *)data3, sizeof(data3), "zl97rQ==", B64F_NORMAL);

    return 0;
}
