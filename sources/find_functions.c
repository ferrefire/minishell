/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 21:18:28 by ferre         #+#    #+#                 */
/*   Updated: 2024/12/20 15:56:29 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <stdlib.h>

int	find_chr(char *haystack, char needle, int offset, int not)
{
	int	i;

	i = offset;
	while (haystack[i])
	{
		if (!not && haystack[i] == needle)
			return (i);
		else if (not && haystack[i] != needle)
			return (i);
		i++;
	}
	if (not)
		return (offset);
	return (-1);
}

int	find_meta(char *haystack, int offset)
{
	int	i;
	int	j;

	i = offset;
	if (haystack == NULL)
		return (-1);
	while (haystack[i])
	{
		j = 0;
		while (META[j])
		{
			if (haystack[i] == META[j])
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

int	find_non_alnum(char *haystack, int offset)
{
	int	i;

	i = offset;
	if (haystack == NULL)
		return (-1);
	while (haystack[i])
	{
		if (!ft_isalnum(haystack[i]) && haystack[i] != '_')
			return (i);
		i++;
	}
	return (-1);
}

t_quote	find_quote_type(char *str, int start, int type)
{
	t_quote	quote;

	quote.start = find_chr(str, type, start, 0);
	quote.end = find_chr(str, type, quote.start + 1, 0);
	quote.type = type;
	quote.complete = 1;
	if (quote.start == -1 || quote.end == -1)
		quote.complete = 0;
	return (quote);
}

t_quote	find_quote(char *str, int start)
{
	t_quote	single_quotes;
	t_quote	double_quotes;

	single_quotes = find_quote_type(str, start, 39);
	double_quotes = find_quote_type(str, start, 34);
	if (!single_quotes.complete)
		return (double_quotes);
	if (!double_quotes.complete)
		return (single_quotes);
	if (single_quotes.start < double_quotes.start)
		return (single_quotes);
	return (double_quotes);
}
