#include "average.h"

float average(const int *arr, int size)
{
    int sum = 0;
    int count = 0;

    for (int i = 0; i < size; ++i)
    {
        if (arr[i] >= 0 && arr[i] <= 100)
        {
            sum += arr[i];
            count++;
        }
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
        printf("Usage: ./a.out num1 num2 ...\n");
        return 1;
    }

    int arr[argc - 1];
    for (int i = 1; i < argc; ++i)
        arr[i - 1] = atoi(argv[i]);

    float avg = average(arr, argc - 1);
    printf("Average: %.2f\n", avg);

    return 0;
}
 */
