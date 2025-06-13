#include "first_last.h"

void first_last(int arr[], int size, int target, int *first, int *last)
{
    int i;
    *first = -1;
    *last = -1;

    for (i = 0; i < size; i++)
    {
        if (arr[i] == target)
        {
            if (*first == -1)
                *first = i;
            *last = i;
        }
    }
}
/* 
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    printf("Usage: %s <target> <array elements...>\n", argv[0]);

    if (argc < 3)
    {
        fprintf(stderr, "Error: missing arguments.\n");
        return 1;
    }

    int target = atoi(argv[1]);
    int size = argc - 2;
    int *arr = (int *)malloc(size * sizeof(int));
    if (!arr)
    {
        fprintf(stderr, "Error: memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < size; i++)
        arr[i] = atoi(argv[i + 2]);

    int first, last;
    first_last(arr, size, target, &first, &last);

    printf("First occurrence: %d\n", first);
    printf("Last occurrence: %d\n", last);

    free(arr);
    return 0;
}
 */