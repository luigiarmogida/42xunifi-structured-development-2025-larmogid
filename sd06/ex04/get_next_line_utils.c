#include "get_next_line.h"
#include "utils.h"

char	*ft_generate_line(char *stored_str)
{
	char	*str;
	int		i;

	i = 0;
	if (!stored_str[i])
		return (NULL);
	while (stored_str[i] && stored_str[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (stored_str[i] && stored_str[i] != '\n')
	{
		str[i] = stored_str[i];
		i++;
	}
	if (stored_str[i] == '\n')
	{
		str[i] = stored_str[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_get_next(char *stored_str)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (stored_str[i] && stored_str[i] != '\n')
		i++;
	if (!stored_str[i])
	{
		free(stored_str);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_strlen(stored_str) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (stored_str[i])
		str[j++] = stored_str[i++];
	str[j] = '\0';
	free(stored_str);
	return (str);
}
