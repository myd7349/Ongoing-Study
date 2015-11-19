// 2015-11-19T12:33+08:00


// Try to uncomment this line below and see what happens.
//#define DEFINE_MAINWINDOW_DESTRUCTOR (0)

#include "main_window.h"

int main()
{
    MainWindow win_no_border(640, 480, false);
    win_no_border.print_size();

    MainWindow win_with_border(640, 480, true);
    win_with_border.print_size();

    return 0;
}

// References:
// http://www.zhihu.com/question/37600082
// http://herbsutter.com/gotw/_100/
// http://www.gotw.ca/gotw/024.htm
// http://www.gotw.ca/publications/mill05.htm
// http://stackoverflow.com/questions/5606750/deletion-of-pointer-to-incomplete-type-and-smart-pointers
// [Incomplete types and shared_ptr / unique_ptr](http://howardhinnant.github.io/incomplete.html)
