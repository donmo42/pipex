/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:14:02 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/14 19:20:56 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../librairie/ft_libft/libft.h"
# include "../librairie/printf/ftprint/ft_printf.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	pid_t	pid;
	int		fd[2];
	int		infile;
	int		outfile;
	char	*cmd_path;
	char	*cmd_path2;
	char	**cmd;
	char	**cmd2;

}			t_data;

void		argv_error(void);
char		*find_path(char **env, char *cmd);
int			init_data(t_data *data, char **argv, char **envp);

#endif