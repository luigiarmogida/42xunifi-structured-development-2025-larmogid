#include "segmented_runs.h"
#include "segmented_runs.h"

/*  
    Livello basso: verifica se esiste una sottosequenza 
    strettamente crescente di almeno 3 elementi consecutivi.
*/
static int has_increasing_run(const int *segment, int length)
{
    int run_length = 1;
    for (int i = 1; i < length; ++i)
    {
        if (segment[i] > segment[i - 1])
        {
            run_length++;
            if (run_length >= 3)
                return 1;
        }
        else
        {
            run_length = 1;
        }
    }
    return 0;
}

/* 
    Logica operativa: isola e restituisce il prossimo segmento 
    (cioè una sequenza tra due -1) dall’array. 
*/
static int extract_next_segment(const int *arr, int size, int *start_index, const int **segment_ptr, int *segment_length)
{
    int i = *start_index;

    // Salta eventuali -1 consecutivi
    while (i < size && arr[i] == -1)
        i++;

    if (i >= size)
        return 0;

    int start = i;
    while (i < size && arr[i] != -1)
        i++;

    *segment_ptr = &arr[start];
    *segment_length = i - start;
    *start_index = i + 1; // Salta anche il -1
    return 1;
}

/*  
    Livello alto (controllo): scorre l'intero array, 
    estrae i segmenti, e chiede a has_increasing_run 
    se un segmento è valido. 
*/
int count_segments(const int *arr, int size)
{
    int count = 0;
    int index = 0;

    const int *segment;
    int segment_length;

    while (extract_next_segment(arr, size, &index, &segment, &segment_length))
    {
        if (segment_length >= 3 && has_increasing_run(segment, segment_length))
            count++;
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