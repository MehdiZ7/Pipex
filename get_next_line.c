/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:19:02 by mzouhir           #+#    #+#             */
/*   Updated: 2025/12/09 18:06:56 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

char	*get_next_line(int fd)
{
	static t_gnl_list	*stash = NULL;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (free_stash(&stash), NULL);
	line = NULL;
	read_stash(fd, &stash);
	if (stash == NULL)
		return (NULL);
	create_line(stash, &line);
	if (line == NULL)
		return (free_stash(&stash), NULL);
	clean_stash(&stash);
	if (line[0] == '\0')
	{
		free_stash(&stash);
		free(line);
		return (NULL);
	}
	return (line);
}

void	read_stash(int fd, t_gnl_list **stash)
{
	char	*buff;
	int		pos;

	pos = 1;
	while (!newline_chr(*stash) && pos != 0)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buff == NULL)
			return (free_stash(stash));
		pos = read(fd, buff, BUFFER_SIZE);
		if (pos <= 0)
		{
			free(buff);
			if (pos == -1)
				free_stash(stash);
			return ;
		}
		buff[pos] = '\0';
		if (!add_stash(stash, buff, pos))
			return (free(buff), free_stash(stash));
		free(buff);
	}
}

int	add_stash(t_gnl_list **stash, char *buff, int pos)
{
	t_gnl_list	*new;
	t_gnl_list	*last;
	int			i;

	new = malloc(sizeof(t_gnl_list));
	if (!new)
		return (0);
	new->next = NULL;
	new->content = malloc(sizeof(char) * (pos + 1));
	if (!new->content)
		return (free(new), 0);
	i = -1;
	while (++i < pos)
		new->content[i] = buff[i];
	new->content[i] = '\0';
	if (*stash == NULL)
	{
		*stash = new;
		return (1);
	}
	last = ft_get_last(*stash);
	last->next = new;
	return (1);
}

void	create_line(t_gnl_list *stash, char **line)
{
	int	i;
	int	j;

	if (stash == NULL)
		return ;
	ft_malloc_line(line, stash);
	if (*line == NULL)
		return ;
	i = 0;
	while (stash)
	{
		j = 0;
		while (stash->content[j])
		{
			if (stash->content[j] == '\n')
			{
				(*line)[i++] = stash->content[j++];
				break ;
			}
			(*line)[i++] = stash->content[j++];
		}
		stash = stash->next;
	}
	(*line)[i] = '\0';
}

void	clean_stash(t_gnl_list **stash)
{
	t_gnl_list	*new;
	t_gnl_list	*last;
	int			i;
	int			j;

	new = malloc(sizeof(t_gnl_list));
	if (!new)
		return (free_stash(stash));
	last = ft_get_last(*stash);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content[i] == '\n')
		i++;
	new->content = malloc(sizeof(char) * (ft_strlen(last->content) - i + 1));
	if (!new->content)
		return (free(new), free_stash(stash));
	j = 0;
	while (last->content[i])
		new->content[j++] = last->content[i++];
	new->content[j] = '\0';
	new->next = NULL;
	free_stash(stash);
	*stash = new;
}
/*
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("error \n");
		return (-1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		else
		{
			printf("%s", line);
			free(line);
		}
	}
	return (0);
}*/
