/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 20:33:38 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/18 21:06:18 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc(int ac, char **av, char **envp)
{
	pid_t	pid_gnl;
	pid_t	pid_executor;
	int		fd[2];
	char	*line;
	int		outfile;

	if (pipe(fd) == -1)
		print_error_and_exit("fd error");
	pid_gnl = fork();
	if (pid_gnl == -1)
		print_error_and_exit("error fork gnl_pid");
	if (pid_gnl == 0)
	{
		close(fd[0]);
		while (1)
		{
			line = get_next_line(0);
			if (!line)
				break ;
			if (ft_strncmp(line, av[2], ft_strlen(av[2])) == 0)
			{
				free(line);
				break ;
			}
			ft_putstr_fd(line, fd[1]);
			free(line);
		}
		
		close(fd[1]);
	}
	outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile == -1)
		print_error_and_exit("error open outifle");
	pid_executor = fork();
	if (pid_executor == -1)
		print_error_and_exit("error exe pid");
	if (pid_executor == 0)
	{
		if (dup2(fd[0], 0) == -1)
			print_error_and_exit("dup2 in");
		if (dup2(outfile, 1) == -1)
			print_error_and_exit("dup2 out");
		close(fd[0]);
		close(outfile);
	}
}
int	main(int ac, char **av, char **envp)
{
	if (ac > 1 && ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		if (ac < 6)
			print_error_and_exit("Usage: ./pipex here_doc LIMITER cmd1 cmd2 file");
		here_doc(ac, av, envp);
	}

	else
	{
		if (ac < 5)
		{
			ft_putstr_fd("Usage:\n", 2);
			ft_putstr_fd("./pipex file1 cmd1 cmd2 ... cmdn file2\n", 2);
			ft_putstr_fd("./pipex here_doc LIMITER cmd1 cmd2 file\n", 2);
			return (1);
		}
		// pipe_chain(ac, av, envp);
	}
	return (0);
}