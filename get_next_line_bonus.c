/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:23:24 by helin             #+#    #+#             */
/*   Updated: 2025/04/23 15:23:26 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*extract_line(char *stash)
{
	size_t	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	return (ft_substr(stash, 0, i));
}

char	*clean_stash(char *stash)
{
	size_t	i = 0;
	char	*rest;

	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	rest = ft_substr(stash, i + 1, ft_strlen(stash) - i - 1);
	free(stash);
	return (rest);
}

char	*read_to_stash(int fd, char *stash)
{
	char	*buf;
	ssize_t	read_bytes;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(stash, '\n') && read_bytes > 0)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buf);
			free(stash);
			return (NULL);
		}
		buf[read_bytes] = '\0';
		stash = ft_strjoin(stash, buf);
	}
	free(buf);
	return (stash);
}

char	*get_next_line(int fd)
{
	static t_fdnode	*fdlist;
	t_fdnode		*node;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = get_fd_node(&fdlist, fd);
	node->stash = read_to_stash(fd, node->stash);
	if (!node->stash || node->stash[0] == '\0')
	{
		remove_fd_node(&fdlist, fd);
		return (NULL);
	}
	line = extract_line(node->stash);
	node->stash = clean_stash(node->stash);
	if (!node->stash)
		remove_fd_node(&fdlist, fd);
	return (line);
}
