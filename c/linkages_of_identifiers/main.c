// 2014-07-07T16:48+08:00

// `Zen_of_life` has internal linkage and `hah` has external linkage in this example.
// So, in the two different translation units(`foo.c` and `bar.c`):
//   (1) `Zen_of_life` in `foo_zen` and `bar_zen` denotes two individual objects;
//   (2) `hah` in `foo_hah` and `bar_hah` denotes the same object;
//

int main()
{
    extern void foo_zen(void);
    extern void bar_zen(void);
    foo_zen();
    bar_zen();

    extern void foo_hah(void);
    extern void bar_hah(void);
    foo_hah();
    bar_hah();

    return 0;
}
// References:
// ISO/IEC 9899:1999 (E)/6.2.2 Linkages of identifiers
