#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

size_t	ft_strlen(char *s);
char	*ft_strdup(const char *s1);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*trim_whitespace(char *str);
char	*to_lowercase(const char *str);

#endif
