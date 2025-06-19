#include "average.h"

static int is_valid_score(int val)
{
    return (val >= 0 && val <= 100);
}

static void add_if_valid(int val, int *sum, int *count)
{
    if (is_valid_score(val))
    {
        *sum += val;
        (*count)++;
    }
}

float average(const int *arr, int size)
{
    int sum = 0;
    int count = 0;

    for (int i = 0; i < size; ++i)
    {
        add_if_valid(arr[i], &sum, &count);
    }

    if (count == 0)
        return 0.0f;

    return (float)sum / count;
}

/* 
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Usage: %s <list of integers>\n", argv[0]);
        return 1;
    }

    int size = argc - 1;
    int arr[size];

    for (int i = 0; i < size; ++i)
        arr[i] = atoi(argv[i + 1]);

    float avg = average(arr, size);
    printf("Average of valid scores: %.2f\n", avg);

    return 0;
}
 */
