/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:12:21 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/11 20:51:31 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

char	*find_path(char **env)
{
	while (ft_strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

void	child_process(t_data *data, char **env, char **av)
{
	data->pid1 = fork();
}

void	parent_process(t_data *data, char **env, char **av)
{
	data->pid2 = fork();
}

int	main(int ac, char *av[], char *env[])
{
	t_data data;
	int i;

	i = 1;
	if (ac != 5)
		exit_msg();
	data.infile = open(av[1], O_RDONLY);
	data.outfile = open(av[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (data.outfile < 0 || data.infile < 0)
		exit(0);
	if (pipe(data.fd) < 0)
		exit(0);
	data.env_paths = find_path(env);
}