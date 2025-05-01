/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:23:17 by helin             #+#    #+#             */
/*   Updated: 2025/05/01 10:58:33 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_fdnode
{
	int				fd;
	char			*stash;
	struct s_fdnode	*next;
}					t_fdnode;

char				*get_next_line(int fd);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strchr(const char *s, int c);
size_t				ft_strlen(const char *s);
char				*ft_substr(char *s, unsigned int start, size_t len);
t_fdnode			*get_fd_node(t_fdnode **head, int fd);
void				remove_fd_node(t_fdnode **head, int fd);

#endif
