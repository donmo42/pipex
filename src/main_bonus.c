/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:23:49 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/16 20:07:11 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exe_cmd(char *av, int pipe_in, int pipe_out, char **envp)
{
	char	**cmd;
	char	*path;

	if (dup2(pipe_in, 0) == -1)
		print_error_and_exit("dup2 failed for input");
	if (dup2(pipe_out, 1) == -1)
		print_error_and_exit("dup2 failed for output");
	cmd = ft_split(av, ' ');
	if (!cmd)
	{
		ft_printf("Error: ft_split failed\n");
		exit(EXIT_FAILURE);
	}
	path = find_path(envp, cmd[0]);
	if (!path)
	{
		ft_printf("pipex: command not found: %s\n", cmd[0]);
		free_split(cmd);
		exit(EXIT_FAILURE);
	}
	execve(path, cmd, envp);
	perror("execve failed");
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av, char **envp)
{
	int	i;
	int	pipe_in;
	int	pipe_fd[2];
	int	pid;
	int	outfile;
	int	st;

	i = 2;
	if (ac < 5)
		print_error_and_exit("Usage: you need more than 5 arguments!");
	pipe_in = open(av[1], O_RDONLY);
	if (pipe_in < 0)
		print_error_and_exit("pipe_in faile");
	while (i < ac - 2)
	{
		if (pipe(pipe_fd) == -1)
			print_error_and_exit("pipe failed");
		pid = fork();
		if (pid == -1)
			print_error_and_exit("fork failed");
		if (pid == 0)
		{
			close(pipe_fd[0]);
			exe_cmd(av[i], pipe_in, pipe_fd[1], envp);
		}
		else
		{
			close(pipe_fd[1]);
			close(pipe_in);
			pipe_in = pipe_fd[0];
		}
		i++;
	}
	outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		print_error_and_exit("outfile failed");
	pid = fork();
	if (pid == 0)
		exe_cmd(av[i], pipe_in, outfile, envp);
	else
	{
		close(pipe_in);
		close(outfile);
		waitpid(pid, &st, 0);
	}
	return (0);
}
