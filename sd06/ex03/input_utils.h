#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H

#include <stddef.h>

void input_string(const char *prompt, char *buffer, size_t size);
int input_int(const char *prompt, int min, int max);

#endif
