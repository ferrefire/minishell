/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 13:34:29 by fmolenbe      #+#    #+#                 */
/*   Updated: 2024/05/26 17:25:22 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	char	val;
	int		i;
	char	*p;

	i = 0;
	val = c;
	p = (char *)s;
	while (p[i])
	{
		if (p[i] == val)
			return (p + i);
		i++;
	}
	if (p[i] == val)
		return (p + i);
	return (NULL);
}
