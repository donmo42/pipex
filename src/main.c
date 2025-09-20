/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:12:21 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/19 23:07:58 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	print_error_and_exit(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	free_split(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	start_child_process(t_data *data, char **envp)
{
	if (dup2(data->infile, 0) == -1)
		print_error_and_exit("dup2 infile");
	if (dup2(data->fd[1], 1) == -1)
		print_error_and_exit("dup2 pipe_write");
	close(data->fd[0]);
	execve(data->cmd_path, data->cmd, envp);
	perror("execve parent process");
	cleanup(data);
	exit(127);
}

void	start_parent_process(t_data *data, char **envp)
{
	int	status;

	if (waitpid(data->pid, &status, 0) == -1)
		print_error_and_exit("waitpid");
	if (dup2(data->outfile, 1) == -1)
		print_error_and_exit("dup2 outfile");
	if (dup2(data->fd[0], 0) == -1)
		print_error_and_exit("dup2 pipe_read");
	close(data->fd[1]);
	execve(data->cmd_path2, data->cmd2, envp);
	perror("execve parent process");
	cleanup(data);
	exit(127);
}

int	main(int ac, char *av[], char *envp[])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		print_error_and_exit("malloc data");
	if (ac != 5)
	{
		free(data);
		print_error_and_exit("Usage : ./pipex file1 cmd1 | cmd2 file2");
	}
	first_init(data);
	if (init_data(data, av, envp) == 0)
		return (cleanup(data), EXIT_FAILURE);
	if (data->pid == 0)
		start_child_process(data, envp);
	else
		start_parent_process(data, envp);
	cleanup(data);
	return (0);
}
