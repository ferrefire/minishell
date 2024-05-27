/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 16:36:46 by ferre         #+#    #+#                 */
/*   Updated: 2024/05/27 23:41:37 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_metachar(char *command)
{
	char **commands;
	int i;
	int found;

	if (!command || ft_strlen(command) == 0)
		return (-1);
	commands = ft_split(METACHARS, ' ');
	found = 0;
	i = -1;
	while (commands[++i])
	{
		if (ft_strncmp(commands[i], command, ft_strlen(commands[i])) == 0)
		{
			found = 1;
			break;
		}
	}
	clean_args(commands);
	return (found);
}

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

int	args_count(char **args, int meta_break)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (meta_break && is_metachar(args[i]) == 1)
			break ;
		++i;
	}
	return (i);
}

char	**copy_args(char **args, int amount, int meta_break)
{
	char	**new_args;
	int	i;

	if (meta_break || args_count(args, 0) < amount)
		amount = args_count(args, meta_break);
	new_args = malloc(sizeof(void *) * (amount + 1));
	i = -1;
	while (++i < amount)
		new_args[i] = ft_strdup(args[i]);
	new_args[i] = NULL;
	return (new_args);
}