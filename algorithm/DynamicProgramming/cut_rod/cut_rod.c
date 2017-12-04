// 2017-11-24T20:49+08:00
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../algutils.h"


int max(int x, int y)
{
    return x > y ? x : y;
}


// Recursive top-down implementation
// [1] P363
int cut_rod(int p[], int n)
{
    int i;
    int q = INT_MIN;

    assert(p != NULL && n >= 0);

    if (n == 0)
        return 0;

    for (i = 1; i <= n; ++i)
        q = max(q, p[i-1] + cut_rod(p, n - i));

    return q;
}


// Using dynamic programming for optimal rod cutting
//
// First approach: top-down with memoization
// [1] P364
int memoized_cut_rod_aux(int p[], int n, int r[])
{
    int i;
    int q;

    assert(p != NULL && n >= 0 && r != NULL);

    if (n == 0)
        return 0;

    if (r[n - 1] >= 0)
        return r[n - 1];

    q = INT_MIN;

    for (i = 1; i <= n; ++i)
        q = max(q, p[i - 1] + memoized_cut_rod_aux(p, n - i, r));

    r[n - 1] = q;

    return q;
}


int memoized_cut_rod(int p[], int n)
{
    int i;
    int *r = NULL;
    int q;

    assert(p != NULL && n >= 0);

    if (n == 0)
        return 0;

    r = malloc(n * sizeof(int));
    if (r == NULL)
        return -1;

    for (i = 0; i < n; ++i)
        r[i] = INT_MIN;

    q = memoized_cut_rod_aux(p, n, r);

    free(r);

    return q;
}


// Using dynamic programming for optimal rod cutting
//
// Second approach: bottom-up method
// [1] P366
int bottom_up_cut_rod(int p[], int n)
{
    int *r = NULL;
    int i, j;
    int q;

    assert(p != NULL && n >= 0);

    if (n == 0)
        return 0;

    r = malloc(n * sizeof(int));
    if (r == NULL)
        return -1;

    for (j = 1; j <= n; ++j)
    {
        q = INT_MIN;

        for (i = 1; i <= j; ++i)
            q = max(q, i == j ? (p[i - 1] + 0) : (p[i - 1] + r[j - i - 1]));

        r[j - 1] = q;
    }

    q = r[n - 1];

    free(r);

    return q;
}


int extended_bottom_up_cut_rod(int p[], int n, int s[])
{
    int *r = NULL;
    int i, j;
    int q;

    assert(p != NULL && n >= 0 && s != NULL);

    if (n == 0)
        return 0;

    memset(s, 0, n * sizeof(int));

    r = malloc(n * sizeof(int));
    if (r == NULL)
        return -1;

    for (j = 0; j < n; ++j)
    {
        q = INT_MIN;

        for (i = 0; i <= j; ++i)
        {
            int q2 = i == j ? (p[i] + 0) : (p[i] + r[j - i - 1]);

            if (q < q2)
            {
                q = q2;
                s[j] = i + 1;
            }
        }

        r[j] = q;
    }

    q = r[n - 1];

    free(r);

    return q;
}


void print_cut_rod_solution(int p[], int n, int s[])
{
    int revenue = extended_bottom_up_cut_rod(p, n, s);

    if (revenue <= 0)
        return;

    printf("-------------------------------------------------------------------------------\n");
    printf("Rot prices: ");
    printvinl(p, n);
    printf("Cut a rot of length %d like this:", n);

    while (n > 0)
    {
        printf(" %d", s[n - 1]);
        n = n - s[n - 1];
    }

    printf(", will get the largest revenue %d.\n", revenue);
}


int main()
{
    int prices[] = { 1, 5, 8, 9, 10, 17, 17, 20, 24, 30, 35, 41, 43, 50 };
    int revenue;
    int s[ARRAYSIZE(prices)];
    int i;

    revenue = cut_rod(prices, 4);
    printf("%d\n", revenue);

    revenue = memoized_cut_rod(prices, 5);
    printf("%d\n", revenue);

    revenue = bottom_up_cut_rod(prices, 5);
    printf("%d\n", revenue);

    for (i = 0; i <= ARRAYSIZE(prices); ++i)
        print_cut_rod_solution(prices, i, s);

    return 0;
}

// References:
// [1] Introduction to Algorithms, 3rd Edition
