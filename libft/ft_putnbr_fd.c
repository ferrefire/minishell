/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 16:32:18 by fmolenbe      #+#    #+#                 */
/*   Updated: 2024/05/26 17:25:22 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	char				a[100];
	long long int		j;
	int					i;

	i = -1;
	j = n;
	if (j < 0)
		write(fd, "-", 1);
	if (j < 0)
		j *= -1;
	a[++i] = (j % 10) + '0';
	while (j >= 10)
		a[++i] = ((j /= 10) % 10) + '0';
	a[++i] = j + '0';
	while (i-- > 0)
		write(fd, &a[i], 1);
}
