#include "get_next_line.h"

static char	*extract_line(char **stash)
{
	char	*line;
	char	*new_stash;
	char	*newline_ptr;
	size_t	len;

	newline_ptr = ft_strchr(*stash, '\n');
	if (newline_ptr)
		len = newline_ptr - *stash + 1;
	else
		len = ft_strlen(*stash);
	line = ft_substr(*stash, 0, len);
	new_stash = ft_substr(*stash, len, ft_strlen(*stash) - len);
	free(*stash);
	*stash = new_stash;
	if (line && *line == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		buf[BUFFER_SIZE + 1];
	ssize_t		bytes_read;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(stash[fd], '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(stash[fd]), stash[fd] = NULL, NULL);
		buf[bytes_read] = '\0';
		stash[fd] = ft_strjoin(stash[fd], buf);
	}
	if (!stash[fd])
		return (NULL);
	line = extract_line(&stash[fd]);
	return (line);
}
