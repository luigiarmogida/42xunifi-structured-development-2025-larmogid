#include "first_last.h"

static int find_first(int arr[], int size, int target)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == target)
            return i;
    }
    return -1;
}

static int find_last(int arr[], int size, int target)
{
    for (int i = size - 1; i >= 0; i--)
    {
        if (arr[i] == target)
            return i;
    }
    return -1;
}

void first_last(int arr[], int size, int target, int *first, int *last)
{
    *first = find_first(arr, size, target);
    *last = find_last(arr, size, target);
}

/* #include <stdio.h>
#include <stdlib.h>
#include "first_last.h"

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <target> <array elements...>\n", argv[0]);
        return 1;
    }

    int target = atoi(argv[1]);
    int size = argc - 2;
    int *arr = malloc(size * sizeof(int));
    if (!arr)
        return 1;

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