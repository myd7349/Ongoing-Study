#include <xlsxwriter.h>

int main(void)
{
    lxw_workbook *workbook = workbook_new("example01.xlsx");
    lxw_worksheet *worksheet = workbook_add_worksheet(workbook, NULL);

    lxw_format *format = workbook_add_format(workbook);
    format_set_bold(format);

    worksheet_set_column(worksheet, 0, 0, 20, NULL);
    worksheet_write_string(worksheet, 0, 0, "Hello", NULL);

    worksheet_write_string(worksheet, 1, 0, "World", format);

    worksheet_write_number(worksheet, 2, 0, 123, NULL);
    worksheet_write_number(worksheet, 3, 0, 123.456, NULL);

    workbook_close(workbook);

    return 0;
}
