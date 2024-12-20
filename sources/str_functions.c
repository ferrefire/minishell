/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_functions.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 21:11:15 by ferre         #+#    #+#                 */
/*   Updated: 2024/12/19 03:41:36 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <stdlib.h>

// Allocates a new string and appends s2 to s1.
char	*add_str(const char *s1, const char *s2)
{
	char	*str;
	int		i;
	int		len1;
	int		len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = malloc((len1 + len2 + 1) * sizeof(char));
	if (!str)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < len1 + len2)
	{
		if (i < len1)
			str[i] = s1[i];
		else
			str[i] = s2[i - len1];
		i++;
	}
	str[i] = '\0';
	return (str);
}

// Returns 1 if s1 exactly matches s2, 
//otherwise the function returns 0.
int	str_equals(const char *s1, const char *s2)
{
	int	i;
	int	len;

	if (s1 == NULL || s2 == NULL)
		return (0);
	len = ft_strlen(s1);
	if (len != (int)ft_strlen(s2))
		return (0);
	i = 0;
	while (i < len)
	{
		if (s1[i] - s2[i] != 0)
			return (0);
		i++;
	}
	return (1);
}

int	find_str(char *haystack, char *needle, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (haystack == NULL || ft_strlen(needle) == 0)
		return (-1);
	while (haystack[i + j])
	{
		if (haystack[i + j] == needle[j])
			j++;
		else
		{
			j = 0;
			i++;
		}
		if (j == size || j == (int)ft_strlen(needle))
			return (i);
	}
	return (-1);
}

int	str_append(char **address, char *str)
{
	char	*new_str;
	char	*old_str;
	int		len;
	int		i;
	int		j;

	if (!address || !str)
		return (0);
	old_str = *address;
	len = ft_strlen(old_str) + ft_strlen(str);
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		exit(EXIT_FAILURE);
	i = -1;
	j = -1;
	while (old_str[++j])
		new_str[++i] = old_str[j];
	j = -1;
	while (str[++j])
		new_str[++i] = str[j];
	new_str[++i] = '\0';
	free(old_str);
	*address = new_str;
	return (1);
}

void	str_replace(char **address, char *replace, int start, int end)
{
	char	*old_str;
	char	*new_str;
	int		len;
	int		i;

	old_str = *address;
	if (end == -1)
		end = ft_strlen(old_str);
	len = ft_strlen(old_str) - (end - start) + ft_strlen(replace);
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		exit(EXIT_FAILURE);
	i = -1;
	while (++i < len)
	{
		if (i < start)
			new_str[i] = old_str[i];
		else if (i - start < (int)ft_strlen(replace))
			new_str[i] = replace[i - start];
		else
			new_str[i] = old_str[i - ft_strlen(replace) + (end - start)];
	}
	new_str[i] = '\0';
	free(old_str);
	*address = new_str;
}
