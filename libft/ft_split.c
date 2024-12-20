/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 17:05:54 by fmolenbe      #+#    #+#                 */
/*   Updated: 2024/05/26 17:25:22 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	create_collumn(char **arr, char const *s, int *j, char c)
{
	int		k;
	char	*p;

	p = (char *)s;
	k = 0;
	while (*p && *p != c)
	{
		k++;
		p++;
	}
	*j = *j + 1;
	arr[*j] = malloc(k + 1);
	if (!arr[*j])
		return (0);
	arr[*j][k] = '\0';
	return (1);
}

char	**create_arr(char const *s, char c)
{
	char	**arr;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (s[++i])
		if ((s[i] != c && s[i + 1] == c) || (s[i] != c && !s[i + 1]))
			j++;
	arr = malloc((1 + j) * sizeof(char *));
	return (arr);
}

char	**clean_arr(char **arr, int i)
{
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;
	int		j;
	int		k;

	i = -1;
	j = -1;
	k = 0;
	arr = create_arr(s, c);
	if (!arr)
		return (clean_arr(arr, j));
	while (s[++i])
	{
		if (s[i] == c && k > 0)
			k = 0;
		else if (s[i] != c)
		{
			if (k == 0)
				if (!create_collumn(arr, s + i, &j, c))
					return (clean_arr(arr, j));
			arr[j][++k - 1] = s[i];
		}
	}
	arr[++j] = NULL;
	return (arr);
}
