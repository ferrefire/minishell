/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 16:36:46 by ferre         #+#    #+#                 */
/*   Updated: 2024/05/26 21:35:45 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_join_free(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (str);
}

char	**clean_args(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

int	args_count(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		++i;
	return (i);
}