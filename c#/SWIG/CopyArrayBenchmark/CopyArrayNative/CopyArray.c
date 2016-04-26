// 2016-04-25T16:46+08:00
void CopyArray(const double *sourceArray, double *targetArray, int items)
{
    double *end = targetArray + items;
    while (targetArray < end)
        *targetArray++ = *sourceArray++;
}