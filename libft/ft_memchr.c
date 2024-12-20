/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 13:34:29 by fmolenbe      #+#    #+#                 */
/*   Updated: 2024/05/26 17:25:22 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memchr(const void *s1, int c, size_t n)
{
	unsigned char	*p;
	unsigned int	i;
	unsigned char	val;

	i = 0;
	p = (unsigned char *)s1;
	val = c;
	while ((int)n-- > 0)
	{
		if (p[i] == val)
			return (p + i);
		i++;
	}
	return (NULL);
}
