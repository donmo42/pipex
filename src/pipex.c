/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:12:24 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/14 14:32:07 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*find_path(char **env, char *cmd)
{
	int		i;
	char	**paths;
	char	*good_path;
	char	*path_find;

	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
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
			return (good_path);
		free(good_path);
		i++;
	}
	i = -1;
	while (paths[i++])
		free(paths[i]);
	free(paths);
	return (NULL);
}

int	init_data(t_data data, char **av, char **envp)
{
	data.cmd = ft_split(av[2], ' ');
	if (!data.cmd)
		return (0);
	data.cmd_path = find_path(envp, data.cmd[0]);
	if (data.cmd_path == NULL)
		return (0);
	data.infile = open(av[1], O_RDONLY);
	if (data.infile < 0)
		return (0);
	data.outfile = open(av[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (data.outfile < 0)
		return (0);
	if (pipe(data.fd) < 0)
		return (0);
	data.pid = fork();
	if (data.pid < 0)
		return (0);
	return (1);
}

void	func_exe(t_data data, char *av, char **envp)
{
	if (execve(av,data.cmd,envp) == -1)
	{
		free(data.cmd);
		exit(0);
	}
}