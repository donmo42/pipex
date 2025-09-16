/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 18:14:17 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/16 20:02:42 by macoulib         ###   ########.fr       */
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

void	print_error_and_exit(const char *msg);
char	*find_path(char **env, char *cmd);
void	exe_cmd(char *av, int pipe_in, int pipe_out, char **envp);
void	free_split(char **tab);

#endif