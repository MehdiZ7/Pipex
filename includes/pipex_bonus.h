/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 10:37:18 by mzouhir           #+#    #+#             */
/*   Updated: 2025/12/09 18:05:32 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft.h"
# include "get_next_line.h"

//Parsing bonus
char	**get_cmd(char *cmd);
void	free_split(char **tab);
char	*find_path(char *cmd, char **env);
char	*build_cmd_path(char *cmd, char *path);
char	*get_env(char **env);

//Utilis bonus 1
void	child_process(char *cmd, char **env, int *fd);
void	execute(char *cmd, char **env);
void	open_infile(char *filename);
void	loop_pipe(int ac, char **av, char **env);
void	open_outfile(char *filename);

//Utilis bonus 2
void	here_doc_input(char *limiter);
void	loop_pipe_heredoc(int ac, char **av, char **env);
void	open_outfile_heredoc(char *filename);

#endif
