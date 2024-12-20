/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils_bonus.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/25 14:03:37 by fmolenbe      #+#    #+#                 */
/*   Updated: 2024/05/26 17:25:22 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

char	*gnl_strdup(char *s1)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	ptr = malloc(i + 1);
	if (!ptr)
		return (NULL);
	while (j < i)
	{
		ptr[j] = s1[j];
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}

size_t	gnl_len(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*clean_pointers(char *s1, char *s2, int re)
{
	char	*return_s;

	if (re == 1)
		return_s = gnl_strdup(s1);
	if (re != -1 && s1 != NULL)
		free(s1);
	if (s2 != NULL)
		free(s2);
	if (re == 1)
		return (return_s);
	return (NULL);
}

char	*comb(char *s1, char *s2)
{
	char	*p;
	int		i;
	int		j;

	if (s2)
		p = malloc(gnl_len(s1) + gnl_len(s2) + 1);
	else
		p = malloc(gnl_len(s1) + 1);
	if (!p)
		return (clean_pointers(s1, s2, 0));
	i = -1;
	while (s1[++i])
		p[i] = s1[i];
	j = 0;
	while (s2 && s2[j])
	{
		p[i + j] = s2[j];
		j++;
	}
	p[i + j] = '\0';
	clean_pointers(s1, s2, 0);
	return (p);
}

char	*prep(char *s, char *return_s, int end_index)
{
	char	*new_s;
	int		i;

	if (!return_s)
		return (clean_pointers(s, NULL, 0));
	i = -1;
	end_index += 1;
	return_s[end_index] = '\0';
	new_s = malloc(gnl_len(s) - end_index + 1);
	if (!new_s)
		return (clean_pointers(s, NULL, 0));
	while (s[++i])
	{
		if (i < end_index)
			return_s[i] = s[i];
		else
			new_s[i - end_index] = s[i];
	}
	new_s[gnl_len(s) - end_index] = '\0';
	if (s)
		free(s);
	if (!new_s[0])
		return (clean_pointers(new_s, NULL, 0));
	return (new_s);
}
