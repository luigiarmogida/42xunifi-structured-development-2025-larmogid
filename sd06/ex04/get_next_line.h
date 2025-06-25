
#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*ft_read_n_store(int fd, char *stored_str);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *stored_str, char *buff);
size_t	ft_strlen(char *s);
char	*ft_generate_line(char *stored_str);
char	*ft_get_next(char *stored_str);

#endif
