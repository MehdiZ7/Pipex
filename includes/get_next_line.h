/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:18:54 by mzouhir           #+#    #+#             */
/*   Updated: 2025/12/09 18:06:05 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_gnl_list
{
	char				*content;
	struct s_gnl_list	*next;
}	t_gnl_list;

int			newline_chr(t_gnl_list *stash);
t_gnl_list	*ft_get_last(t_gnl_list *stash);
void		ft_malloc_line(char **line, t_gnl_list *stash);
void		free_stash(t_gnl_list **stash);
char		*get_next_line(int fd);
void		read_stash(int fd, t_gnl_list **stash);
int			add_stash(t_gnl_list **stash, char *buf, int pos);
void		create_line(t_gnl_list *stash, char **line);
void		clean_stash(t_gnl_list **stash);

#endif
