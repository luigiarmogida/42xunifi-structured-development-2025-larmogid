#include "get_next_line.h"

char	*ft_read_n_store(int fd, char *stored_str)
{
	char	*buff;
	int		size_read;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	size_read = 1;
	while (!ft_strchr(stored_str, '\n') && size_read != 0)
	{
		size_read = read(fd, buff, BUFFER_SIZE);
		if (size_read == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[size_read] = '\0';
		stored_str = ft_strjoin(stored_str, buff);
	}
	free(buff);
	return (stored_str);
}

char	*get_next_line(int fd)
{
	static char	*stored_str[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	stored_str[fd] = ft_read_n_store(fd, stored_str[fd]);
	if (!stored_str[fd])
		return (NULL);
	line = ft_generate_line(stored_str[fd]);
	stored_str[fd] = ft_get_next(stored_str[fd]);
	return (line);
}
