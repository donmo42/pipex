/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:14:02 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/13 17:58:10 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./librairie/ft_libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	pid_t	pid1;
	int		fd[2];
	int		infile;
	int		outfile;
	char	*env_paths;
	char	**cmd_path;
	char	**cmd;

}			t_data;

void		exit_msg(void);
void		func_exe(t_data data, char *av, char **env);

char		*find_path(char **envp);

#endif