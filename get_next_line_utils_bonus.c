/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:23:33 by helin             #+#    #+#             */
/*   Updated: 2025/04/23 15:23:34 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i = 0, j = 0;
	size_t	len = ft_strlen(s1) + ft_strlen(s2);
	char	*res = malloc(len + 1);
	if (!res)
		return (NULL);
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	free(s1);
	return (res);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i = 0;
	char	*res;

	if (!s || start >= ft_strlen(s))
		return (NULL);
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	while (i < len && s[start + i])
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

t_fdnode *get_fd_node(t_fdnode **head, int fd)
{
	t_fdnode *curr = *head;

	while (curr)
	{
		if (curr->fd == fd)
			return (curr);
		curr = curr->next;
	}
	curr = malloc(sizeof(t_fdnode));
	if (!curr)
		return (NULL);
	curr->fd = fd;
	curr->stash = NULL;
	curr->next = *head;
	*head = curr;
	return (curr);
}

void	remove_fd_node(t_fdnode **head, int fd)
{
	t_fdnode *curr = *head;
	t_fdnode *prev = NULL;

	while (curr)
	{
		if (curr->fd == fd)
		{
			if (prev)
				prev->next = curr->next;
			else
				*head = curr->next;
			free(curr->stash);
			free(curr);
			return;
		}
		prev = curr;
		curr = curr->next;
	}
}
