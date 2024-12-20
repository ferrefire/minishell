/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 16:01:58 by fmolenbe      #+#    #+#                 */
/*   Updated: 2024/05/26 17:25:22 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

char	*ft_itoa(int n)
{
	char			a[100];
	long long int	j;
	int				i;
	char			*p;
	int				k;

	i = -1;
	k = -1;
	j = n;
	if (j < 0)
		k += ((j *= -1) * 0) + 1;
	a[++i] = (j % 10) + '0';
	while (j >= 10)
		a[++i] = ((j /= 10) % 10) + '0';
	a[++i] = j + '0';
	a[++i] = '\0';
	p = malloc(--i + k + 2);
	if (!p)
		return (NULL);
	if (k == 0)
		p[k] = '-';
	while (i-- > 0)
		p[++k] = a[i];
	p[++k] = '\0';
	return (p);
}
