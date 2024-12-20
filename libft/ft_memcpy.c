/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 17:28:53 by fmolenbe      #+#    #+#                 */
/*   Updated: 2024/05/26 17:25:22 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*s;
	char	*d;
	int		i;

	if (!src && !dst)
		return (NULL);
	s = (char *)src;
	d = (char *)dst;
	i = 0;
	while (n--)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
