/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arg_functions.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 21:14:39 by ferre         #+#    #+#                 */
/*   Updated: 2024/12/20 07:08:10 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <stdlib.h>

char	**copy_args(char **args, int size)
{
	char	**new_args;
	int		args_len;
	int		i;

	args_len = args_size(args);
	if (size == -1)
		size = args_len;
	new_args = malloc(sizeof(void *) * (size + 1));
	if (!new_args)
		exit(EXIT_FAILURE);
	new_args[size] = NULL;
	i = 0;
	while (i < size)
	{
		if (i < args_len && args[i])
			new_args[i] = ft_strdup(args[i]);
		else
			new_args[i] = NULL;
		i++;
	}
	return (new_args);
}

int	clear_args(void *address)
{
	char	**args;
	int		i;

	if (!address)
		return (0);
	args = *(char ***)address;
	if (!args)
		return (0);
	i = args_size(args);
	while (--i >= 0)
	{
		if (args[i])
			free(args[i]);
	}
	free(args);
	*(char ***)address = NULL;
	return (1);
}

int	resize_args(void *address, int size)
{
	char	**new_args;
	char	**args;

	if (!address)
		return (0);
	args = *(char ***)address;
	new_args = copy_args(args, size);
	clear_args(&args);
	*(char ***)address = new_args;
	return (1);
}

int	add_to_args(void *address, char *arg)
{
	char	**args;
	int		size;

	if (!address)
		return (0);
	args = *(char ***)address;
	size = args_size(args);
	resize_args(address, size + 1);
	args = *(char ***)address;
	args[size] = arg;
	return (1);
}

int	remove_from_args(void *address, char *arg)
{
	char	**args;
	int		size;
	int		i;

	if (!address || !arg)
		return (0);
	args = *(char ***)address;
	size = args_size(args);
	i = 0;
	while (i < size)
	{
		if (str_equals(args[i], arg))
			break ;
		i++;
	}
	if (i >= size)
		return (0);
	clear(&args[i]);
	while (i < size - 1)
	{
		args[i] = args[i + 1];
		i++;
	}
	args[i] = NULL;
	return (0);
}
