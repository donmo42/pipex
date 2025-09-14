/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:12:21 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/14 14:38:02 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exit_msg(void)
{
	ft_printf("Usage : ./pipex file1 cmd1 | cmd2 file2");
	exit(1);
}
void	start_child_process(t_data data, char **envp)
{
	dup2(data.fd[1], 1);
	dup2(data.infile, 0);
	close(data.fd[0]);
	func_exe(data, data.cmd_path, envp);
}

void	start_parent_process(t_data data, char **envp)
{
	dup2(data.fd[0], 0);
	dup2(data.outfile, 1);
	close(data.fd[1]);
	func_exe(data, data.cmd_path, envp);
}

int	main(int ac, char *av[], char *envp[])
{
	t_data	data;

	data.pid = 0;
	if (ac != 5)
		exit_msg();
	if (init_data(data, av, envp) != 1)
		exit(0);
	if (!data.pid)
		start_child_process(data, envp);
	start_parent_process(data, envp);
}
