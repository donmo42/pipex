/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:12:21 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/14 19:06:46 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	start_child_process(t_data data, char **envp)
{
	dup2(data.infile, 0);
	dup2(data.fd[1], 1);
	close(data.fd[0]);
	if (execve(data.cmd_path, data.cmd, envp) == -1)
	{
		free(data.cmd);
		exit(0);
	}
}

void	start_parent_process(t_data data, char **envp)
{
	dup2(data.outfile, 1);
	dup2(data.fd[0], 0);
	close(data.fd[1]);
	if (execve(data.cmd_path2, data.cmd2, envp) == -1)
	{
		free(data.cmd);
		exit(0);
	}
}

int	main(int ac, char *av[], char *envp[])
{
	t_data	data;

	if (ac != 5)
		argv_error();
	if (init_data(data, av, envp) != 1)
		exit(0);
	data.pid = fork();
	if (data.pid == -1)
		return (0);
	if (pipe(data.fd) == -1)
		return (0);
	if (data.pid == 0)
		start_child_process(data, envp);
	start_parent_process(data, envp);
}
