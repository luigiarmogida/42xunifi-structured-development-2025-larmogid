#include "segmented_runs.h"

int count_segments(const int *arr, int size)
{
    int i = 0;
    int count = 0;
    int increasing_len = 1;
    int has_run = 0; /* almeno una run valida nel segmento */

    while (i < size)
    {
        // Nuovo segmento o inizio dell'array
        has_run = 0;
        increasing_len = 1;

        while (i < size && arr[i] != -1)
        {
            if (i > 0 && arr[i - 1] != -1 && arr[i] > arr[i - 1])
            {
                increasing_len++;
                if (increasing_len >= 3)
                    has_run = 1;
            }
            else
            {
                increasing_len = 1;
            }
            i++;
        }

        if (has_run)
            count++;

        // Salta il -1
        i++;
    }

    return count;
}

/* 
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Usage: %s <int1> <int2> ... <intN>\n", argv[0]);
        fprintf(stderr, "Error: missing arguments.\n");
        return 1;
    }

    int size = argc - 1;
    int *arr = (int *)malloc(sizeof(int) * size);
    if (!arr)
    {
        perror("malloc failed");
        return 1;
    }

    for (int i = 0; i < size; i++)
        arr[i] = atoi(argv[i + 1]);

    int result = count_segments(arr, size);
    printf("Count of valid segments: %d\n", result);

    free(arr);
    return 0;
}
 */