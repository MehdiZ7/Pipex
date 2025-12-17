/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:13:20 by mzouhir           #+#    #+#             */
/*   Updated: 2025/12/08 15:31:47 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	int		status;
	pid_t	pid1;
	pid_t	pid2;

	if (ac != 5)
		return (ft_printf("Invalid arguments"), 1);
	if (pipe(fd) == -1)
		return (perror("Pipe"), 1);
	pid1 = fork();
	if (pid1 == 0)
		process1(av, env, fd);
	pid2 = fork();
	if (pid2 == 0)
		process2(av, env, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
