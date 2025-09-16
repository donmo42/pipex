/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:12:24 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/16 17:13:16 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	print_error_and_exit(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	cleanup(t_data *data)
{
	if (!data)
		return ;
	if (data->cmd_path)
		free(data->cmd_path);
	if (data->cmd_path2)
		free(data->cmd_path2);
	if (data->cmd)
		free_split(data->cmd);
	if (data->cmd2)
		free_split(data->cmd2);
	if (data->infile > 0)
		close(data->infile);
	if (data->outfile > 0)
		close(data->outfile);
	if (data->fd[0] > 0)
		close(data->fd[0]);
	if (data->fd[1] > 0)
		close(data->fd[1]);
	free(data);
}

char	*find_path(char **env, char *cmd)
{
	int		i;
	char	**paths;
	char	*good_path;
	char	*path_find;

	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	if (!env[i])
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		path_find = ft_strjoin(paths[i], "/");
		good_path = ft_strjoin(path_find, cmd);
		free(path_find);
		if (access(good_path, F_OK) == 0)
		{
			free_split(paths);
			return (good_path);
		}
		free(good_path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (NULL);
}

void	first_init(t_data *data)
{
	data->infile = -1;
	data->outfile = -1;
	data->cmd_path = NULL;
	data->cmd_path2 = NULL;
	data->cmd = NULL;
	data->cmd2 = NULL;
	data->fd[0] = -1;
	data->fd[1] = -1;
}
int	init_data(t_data *data, char **argv, char **envp)
{
	data->cmd = ft_split(argv[2], ' ');
	if (!data->cmd || !data->cmd[0])
		return (ft_printf("Error: invalid cmd1\n"), 0);
	data->cmd2 = ft_split(argv[3], ' ');
	if (!data->cmd2 || !data->cmd2[0])
		return (ft_printf("Error: invalid cmd2\n"), 0);
	data->cmd_path = find_path(envp, data->cmd[0]);
	if (!data->cmd_path)
		return (ft_printf("Error: command not found: %s\n", data->cmd[0]), 0);
	data->cmd_path2 = find_path(envp, data->cmd2[0]);
	if (!data->cmd_path2)
		return (ft_printf("Error: command not found: %s\n", data->cmd2[0]), 0);
	data->infile = open(argv[1], O_RDONLY);
	if (data->infile < 0)
		return (perror(argv[1]), 0);
	data->outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (data->outfile < 0)
		return (perror(argv[4]), 0);
	if (pipe(data->fd) == -1)
		return (perror("pipe"), 0);
	data->pid = fork();
	if (data->pid == -1)
		return (perror("fork"), 0);
	return (1);
}
