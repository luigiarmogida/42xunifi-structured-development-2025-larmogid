#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>
#include "get_next_line.h"

static char	*gnl_strjoin(char *s1, char *s2)
{
	size_t	len1 = 0;
	size_t	len2 = 0;
	char	*res;
	size_t	i = 0, j = 0;

	while (s1 && s1[len1]) len1++;
	while (s2 && s2[len2]) len2++;

	res = malloc(len1 + len2 + 1);
	if (!res)
		return (NULL);

	while (s1 && s1[i]) { res[i] = s1[i]; i++; }
	while (s2 && s2[j]) { res[i + j] = s2[j]; j++; }
	res[i + j] = '\0';
	free(s1);
	return (res);
}

static int	has_newline(const char *s)
{
	if (!s)
		return (0);
	while (*s)
		if (*s++ == '\n')
			return (1);
	return (0);
}

static char	*extract_line(char *buf)
{
	int		i = 0;
	char	*line;

	if (!buf || !buf[0])
		return (NULL);

	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n') i++;

	line = malloc(i + 1);
	if (!line)
		return (NULL);
	for (int j = 0; j < i; j++)
		line[j] = buf[j];
	line[i] = '\0';
	return (line);
}

static char	*trim_buffer(char *buf)
{
	int		i = 0, j = 0;
	char	*new_buf;

	while (buf[i] && buf[i] != '\n')
		i++;
	if (!buf[i])
	{
		free(buf);
		return (NULL);
	}
	i++; // salta il '\n'
	new_buf = malloc(strlen(buf + i) + 1);
	if (!new_buf)
		return (NULL);
	while (buf[i])
		new_buf[j++] = buf[i++];
	new_buf[j] = '\0';
	free(buf);
	return (new_buf);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		tmp[BUFFER_SIZE + 1];
	ssize_t		bytes;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	bytes = 1;
	while (!has_newline(buf) && bytes > 0)
	{
		bytes = read(fd, tmp, BUFFER_SIZE);
		if (bytes < 0)
			return (free(buf), buf = NULL, NULL);
		tmp[bytes] = '\0';
		buf = gnl_strjoin(buf, tmp);
	}
	line = extract_line(buf);
	buf = trim_buffer(buf);
	return (line);
}
