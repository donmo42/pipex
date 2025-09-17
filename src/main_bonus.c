/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:23:49 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/17 21:02:45 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc(char *av, int ac)
{
	pid_t	pid;
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		print_error_and_exit("pip here_doc failed");
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		while (get_next_line(&line))
		{
			if (!ft_strncmp(line, av, ft_strlen(av)))
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 1);
	}
}

int	main(int ac, char **av, char **envp)
{
	int i;
	int pipe_in;
	int status;
	int pipe_fd[2];
	int pid;
	int outfile;
	if (ac < 5)
		print_error_and_exit("plus de 5 argv");
	if (!ft_strncmp(av[2], "here_doc", 8))
	{
		i = 2;
		if (ac < 6)
			print_error_and_exit("plus de 5 argv");
		outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (outfile < 0)
			print_error_and_exit("outfile failed");
		here_doc(av[2], ac);
	}
	else
	{
		i = 3;
		pipe_in = open(av[1], O_RDONLY);
		if (pipe_in < 0)
			print_error_and_exit("pipe_in faile");
		outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile < 0)
			print_error_and_exit("outfile failed");
		dup2(pipe_in, 1);
	}

	return (0);
}