#include "critical_windows.h"

int count_critical_windows(const int *readings, int size) {
    int count = 0;

    if (size < 5)
        return 0;

    for (int i = 0; i <= size - 5; i++) 
    {
        int count_over_70 = 0;    // contatore
        int has_over_150 = 0;   // flag
        int sum = 0;

        for (int j = 0; j < 5; j++) 
        {
            int val = readings[i + j];

            if (val >= 70)
                count_over_70++;
            if (val > 150)
                has_over_150 = 1;
            sum += val;
        }

        if (count_over_70 >= 3 && !has_over_150 && (sum / 5) >= 90)
            count++;
    }

    return count;
}
/* 
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc < 6) {
        // Servono almeno 5 valori per avere una finestra valida
        printf("Usage: %s <reading1> <reading2> ... (at least 5 readings)\n", argv[0]);
        return 1;
    }

    int size = argc - 1;
    int readings[size];

    for (int i = 0; i < size; i++) {
        readings[i] = atoi(argv[i + 1]);
    }

    int result = count_critical_windows(readings, size);
    printf("Critical windows: %d\n", result);

    return 0;
}
 */