/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:43:43 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/20 18:15:43 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex_bonus.h"

size_t	ft_strlen( const char *theString )
{
	size_t	i;

	i = 0;
	if (!theString)
		return (0);
	while (theString[i])
		i++;
	return (i);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	s1s2len;
	size_t	i;
	size_t	j;
	char	*s1s2cpy;

	i = 0;
	j = 0;
	s1s2len = ft_strlen(s1) + ft_strlen(s2);
	s1s2cpy = malloc ((s1s2len + 1) * sizeof(char));
	if (!s1s2cpy)
		return (NULL);
	while (s1 && s1[i])
	{
		s1s2cpy[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		s1s2cpy[i] = s2[j];
		i++;
		j ++;
	}
	s1s2cpy[i] = '\0';
	return (s1s2cpy);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (NULL);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*scpy;
	size_t			i;

	i = 0 ;
	scpy = (unsigned char *) s;
	while (n > i)
	{
		scpy[i] = '\0';
		i++;
	}
}

void	*ft_calloc( size_t elementCount, size_t elementSize )
{
	void	*moncalloc;
	size_t	nbr;

	nbr = elementCount * elementSize;
	moncalloc = malloc(nbr);
	if (!moncalloc)
		return (NULL);
	ft_bzero(moncalloc, nbr);
	return (moncalloc);
}
