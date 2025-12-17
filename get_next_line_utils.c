/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:19:00 by mzouhir           #+#    #+#             */
/*   Updated: 2025/12/09 17:54:31 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	newline_chr(t_gnl_list *stash)
{
	int			i;
	t_gnl_list	*current;

	if (stash == NULL)
		return (0);
	current = ft_get_last(stash);
	i = 0;
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_gnl_list	*ft_get_last(t_gnl_list *stash)
{
	if (!stash)
		return (NULL);
	while (stash->next)
		stash = stash->next;
	return (stash);
}

void	ft_malloc_line(char **line, t_gnl_list *stash)
{
	int	i;
	int	len;

	len = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				len++;
				break ;
			}
		len++;
		i++;
		}
	stash = stash->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

void	free_stash(t_gnl_list **stash)
{
	t_gnl_list	*current;
	t_gnl_list	*next;

	current = *stash;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
	*stash = NULL;
}
