/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 15:23:37 by fmolenbe      #+#    #+#                 */
/*   Updated: 2024/05/26 17:25:22 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

int	write_val(char *p, char c, int *count, int pchr)
{
	if (pchr == 0 && p)
	{
		while (*p++ && ++*count)
			if (write(1, p - 1, 1) == -1)
				return (-1);
	}
	else if (pchr == 0 && !p)
	{
		if (write(1, "(null)", 6) == -1)
			return (-1);
		*count += 6;
	}
	else if (pchr != 0 && ++*count)
		if (write(1, &c, 1) == -1)
			return (-1);
	return (0);
}

int	itoh(__UINTPTR_TYPE__ n, int add, int pointer, int *count)
{
	char				arr[100];
	__UINTPTR_TYPE__	temp;
	int					i;

	i = 0;
	if (pointer == 1)
		if (write_val("0x", 0, count, 0) != 0)
			return (-1);
	if (n == 0)
		if (write_val(NULL, '0', count, 1) != 0)
			return (-1);
	while (n != 0)
	{
		temp = n % 16;
		if (temp < 10)
			temp = temp + 48;
		else
			temp = temp + 55 + add;
		arr[i++] = temp;
		n /= 16;
	}
	while (--i >= 0)
		if (write_val(NULL, arr[i], count, 1) != 0)
			return (-1);
	return (0);
}

int	itoa(long int n, int u, int *count)
{
	char			a[100];
	long int		j;
	int				i;
	int				k;

	i = -1;
	k = -1;
	j = n;
	if (u == 1)
		j = (unsigned int)n;
	if (j < 0)
		k += ((j *= -1) * 0) + 1;
	a[++i] = (j % 10) + '0';
	while (j >= 10)
		a[++i] = ((j /= 10) % 10) + '0';
	a[++i] = j + '0';
	if (k == 0)
		if (write_val(NULL, '-', count, 1) != 0)
			return (-1);
	while (i-- > 0)
		if (write_val(NULL, a[i], count, 1) != 0)
			return (-1);
	return (0);
}

int	check_type(va_list ptr, char c, int *count)
{
	va_list	temp;
	int		u;

	u = 0;
	va_copy(temp, ptr);
	if (c == 'c')
		return (write_val(NULL, va_arg(temp, int), count, 1));
	else if (c == 's')
		return (write_val(va_arg(temp, void *), 0, count, 0));
	else if (c == 'p')
		return (itoh(va_arg(temp, __UINTPTR_TYPE__), 32, 1, count));
	else if ((c == 'd' || c == 'i') || (c == 'u' && ++u))
		return (itoa(va_arg(temp, int), u, count));
	else if (c == 'x')
		return (itoh(va_arg(temp, unsigned int), 32, 0, count));
	else if (c == 'X')
		return (itoh(va_arg(temp, unsigned int), 0, 0, count));
	else
		return (-1);
	va_end(temp);
	return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list	ptr;
	int		i;
	int		count;

	va_start(ptr, s);
	i = -1;
	count = 0;
	while (s[++i] != '\0')
	{
		if (s[i] != '%' || (s[i + 1] == '%' && ++i))
		{
			if (write_val(NULL, s[i], &count, 1) != 0)
				return (-1);
		}
		else if (s[i + 1] != '\0' && ++i)
		{
			if (check_type(ptr, s[i], &count) != 0)
				return (-1);
			va_arg(ptr, int);
		}
	}
	va_end(ptr);
	return (count);
}
