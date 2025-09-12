/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:12:21 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/12 17:17:03 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

char	*find_path(char **env)
{
	while (ft_strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

void	start_child_process(t_data data, char **env)
{
	dup2(data.fd[1], 1);  // Redirige  (1) vers l’extrémité d’écriture du pipe.
	dup2(data.infile, 0);  // Redirige  (0) vers le fichier d’entrée.
	close(data.fd[0]);  // Ferme l’extrémité de lecture (inutile dans le fils).
}

void	start_parent_process(t_data data, char **env)
{
	dup2(data.fd[0], 0);  // Redirige STDIN (0) vers l’extrémité de lecture du pipe.
	dup2(data.outfile, 1);// Redirige STDOUT (1) vers le fichier de sortie.
	close(data.fd[1]); // Ferme l’extrémité d’écriture (inutile dans le parent).
}

int	main(int ac, char *av[], char *env[])
{
	t_data	data;
	int		i;

	i = 1;
	if (ac != 5)
		exit_msg();
	data.infile = open(av[1], O_RDONLY);
	data.outfile = open(av[4], O_TRUNC | O_CREAT | O_RDWR, 0644);     // ouvre/crée le fichier de sortie en lecture/écriture, vide le fichier s’il existe déjà
	if (data.outfile < 0 || data.infile < 0)
		exit(0);
	if (pipe(data.fd) < 0)
		exit(0);
	data.pid1 = fork();
	if (data.pid1 == -1)
		exit(0);
	if (data.pid1 == 0)
		start_child_process(data, env);
	else
		start_parent_process(data, env);
		
}
