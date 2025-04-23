#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int	fd1 = open("file1.txt", O_RDONLY);
	int	fd2 = open("file2.txt", O_RDONLY);
	char *line;

	while ((line = get_next_line(fd1)) || (line = get_next_line(fd2)))
	{
		if (line)
		{
			printf("%s", line);
			free(line);
		}
	}
	close(fd1);
	close(fd2);
}
