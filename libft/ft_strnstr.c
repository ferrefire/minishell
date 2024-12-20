/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 14:26:57 by fmolenbe      #+#    #+#                 */
/*   Updated: 2024/05/27 22:17:41 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (needle && haystack && haystack[i] && (i < len || len == 0))
	{
		j = 0;
		while (needle[j] && haystack[i + j] && needle[j] == haystack[i + j])
		{
			if (len != 0 && i + j >= len)
				break ;
			j++;
		}
		if (!needle[j])
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
