/* 2015-04-22T13:59+08:00 */
#include <assert.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

#include "hpdf.h" /* libharu */

#include "../../common.h"

#ifdef _MSC_VER
# pragma comment(lib, "libhpdf.lib")
#endif

static jmp_buf env_buf;

static void HPDF_STDCALL hpdf_error_handler(
    HPDF_STATUS error_no,
    HPDF_STATUS detail_no,
    void *user_data)
{
    (void)user_data;

    fprintf(stderr, "Failed to create PDF file:\nError No.: %#04x\nDetailed No.: %d", 
        (unsigned int)error_no, (int)detail_no);

    longjmp(env_buf, 1);
}

static void print_page_size(HPDF_Page page)
{
    HPDF_REAL page_w = 0.0f;
    HPDF_REAL page_h = 0.0f;

    assert(page != NULL);

    page_w = HPDF_Page_GetWidth(page); /* in pixels, hah? */
    page_h = HPDF_Page_GetHeight(page);

    printf("Page width: %.2f, page height: %.2f\n", page_w, page_h);
}

static void draw_test(HPDF_Page page)
{
    assert(page != NULL);

    HPDF_Page_SetWidth(page, 200.0f); /* in pixels, hah? */
    HPDF_Page_SetHeight(page, 200.0f);
    print_page_size(page);

    HPDF_Page_MoveTo(page, 5.0f, 5.0f); /* in dots, hah? */
    HPDF_Page_LineTo(page, 5.0f, 195.0f);
    HPDF_Page_LineTo(page, 195.0f, 195.0f);
    HPDF_Page_LineTo(page, 195.0f, 5.0f);
    HPDF_Page_LineTo(page, 5.0f, 5.0f);
    HPDF_Page_Stroke(page);

    HPDF_Page_Rectangle(page, 50.0f, 50.0f, 100.0f, 100.0f);
    HPDF_Page_Stroke(page);
}

int main(void)
{
    HPDF_Doc pdf = NULL;
    HPDF_Page page_1 = NULL;
    HPDF_Page page_2 = NULL;

    pdf = HPDF_New(hpdf_error_handler, NULL);
    if (NULL == pdf) {
        fprintf(stderr, "Failed to create HPDF_Doc object.\n");
        return EXIT_FAILURE;
    }

    if (setjmp(env_buf)) {
        HPDF_Free(pdf);
        return EXIT_FAILURE;
    }

    HPDF_SetCompressionMode(pdf, HPDF_COMP_ALL);

    /* P1 */
    page_1 = HPDF_AddPage(pdf);
    HPDF_Page_SetSize(page_1, HPDF_PAGE_SIZE_A4, HPDF_PAGE_LANDSCAPE);
    print_page_size(page_1);

    draw_test(page_1);

    /* P2 */
    page_2 = HPDF_AddPage(pdf);
    /* Set new DPI: 300 */
    HPDF_Page_Concat(page_2, 72.0f / 300.0f, 0.0f, 0.0f, 72.0f / 300.0f, 0.0f, 0.0f);

    draw_test(page_2);

    /*
    Conclusion:
    Change the DPI will influence HPDF_Page_MoveTo/HPDF_Page_LineTo/HPDF_Page_Rectangle/...,
    but not HPDF_Page_SetSize/HPDF_Page_SetWidth/HPDF_Page_SetHeight/....
    Because they may use different unit.
    */

    HPDF_SaveToFile(pdf, "set_page_size.pdf");
    HPDF_Free(pdf);

    PAUSE();
    return 0;
}

/*
References:
[libharu's wiki](https://github.com/libharu/libharu/wiki)
*/