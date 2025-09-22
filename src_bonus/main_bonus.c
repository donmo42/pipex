/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:48:36 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/22 18:43:53 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	exe_cmd(char *cmd, char **envp)
{
	char	**split_cmd;
	char	*cmd_path;

	split_cmd = ft_split(cmd, ' ');
	if (!split_cmd[0] || !split_cmd)
		print_error_and_exit("Error split command");
	cmd_path = find_path(envp, split_cmd[0]);
	if (cmd_path == NULL)
		ft_putstr_fd("pipex: command not found: ", 2);
	execve(cmd_path, split_cmd, envp);
	print_error_and_exit("execve");
}

void	exe_each_cmd(char *av, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		exe_cmd(av, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
	}
}

void	here_doc2(char **av, int *fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(0);
		if (!line || ft_strncmp(line, av[2], ft_strlen(av[2])) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
}

void	here_doc(char **av, char **envp)
{
	pid_t	pid;
	int		fd[2];

	(void)envp;
	if (pipe(fd) == -1)
		print_error_and_exit("pipe error");
	pid = fork();
	if (pid == -1)
		print_error_and_exit("pid fork error");
	if (!pid)
	{
		close(fd[0]);
		here_doc2(av, fd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		waitpid(pid, NULL, 0);
	}
}

int	main(int ac, char **av, char **envp)

{
	int i;
	int outfile;
	int infile;

	if (ac < 5)
		return (ft_printf("Usage: file1 cmd1 cmd2 \n"), 1);
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		i = 3;
		if (ac < 6)
			return (ft_printf("Usage: here_doc LIMITER cmd1 cmd2 filee\n"), 1);
		outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (outfile == -1)
			print_error_and_exit("error open outifle ");
		here_doc(av, envp);
	}
	else
	{
		i = 2;
		outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile == -1)
			print_error_and_exit("Error opening outfile");
		infile = open(av[1], O_RDONLY);
		if (infile == -1)
			print_error_and_exit("Error opening infile");
		dup2(infile, 0);
		close(infile);
	}
	while (i < ac - 3)
	{
		exe_each_cmd(av[i], envp);
		i++;
	}
	dup2(outfile, 1);
	exe_cmd(av[ac - 2], envp);
	return (0);
}
