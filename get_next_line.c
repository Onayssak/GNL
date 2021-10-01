#include "get_next_line.h"

static char	*make_backup(int fd, char *backup, char *buffer)
{
	int		readbuffer;
	int		limit_line;
	char	*temporary;

	readbuffer = 1;
	limit_line = 0;
	while (limit_line == 0 && readbuffer != 0)
	{
		readbuffer = read(fd, buffer, BUFFER_SIZE);
		if (readbuffer == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[readbuffer] = '\0';
		if (!backup)
			backup = ft_strdup("");
		temporary = backup;
		backup = ft_strjoin(backup, buffer);
		free(temporary);
		temporary = NULL;
		if (ft_strchr(backup, '\n'))
			limit_line = 1;
	}
	free(buffer);
	return (backup);
}

static char	*make_line(char *backup)
{
	int		i;
	char	*line;

	i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	ft_strlcpy(line, backup, i + 2);
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static char	*make_new_backup(char *backup)
{
	int		i;
	char	*new_backup;

	i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	if (!backup[i])
	{
		free(backup);
		return (NULL);
	}
	new_backup = (char *)malloc(sizeof(char) * (ft_strlen(backup) - i + 1));
	if (!new_backup)
		return (NULL);
	ft_strlcpy(new_backup, backup + i + 1, ft_strlen(backup) - i + 1);
	free(backup);
	return (new_backup);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*backup;
	char		*buffer;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	backup = make_backup(fd, backup, buffer);
	if (!backup)
		return (NULL);
	line = make_line(backup);
	backup = make_new_backup(backup);
	return (line);
}
