/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_in.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/18 20:29:22 by ferre         #+#    #+#                 */
/*   Updated: 2024/12/20 15:51:32 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

//Prints its arguments. It also handles redirections like > >> < <<.
int	echo(t_data *data)
{
	int	i;
	int	newline;
	int	check_option;

	i = 0;
	newline = 1;
	check_option = 1;
	while (++i < args_size(data->commands) && data->commands[i])
	{
		if (check_option && ft_strncmp(data->commands[i], "-n", 2) == 0)
			newline = 0;
		else if (ft_strlen(data->commands[i]) > 0)
		{
			check_option = 0;
			if (i + 1 < args_size(data->commands))
				printf("%s ", data->commands[i]);
			else
				printf("%s", data->commands[i]);
		}
	}
	if (newline)
		printf("\n");
	return (0);
}

// Changes the current working directory.
int	cd(t_data *data)
{
	char	*dir;

	if (args_size(data->commands) > 2)
		return (1);
	if (args_size(data->commands) == 1)
		dir = ft_strdup(get_env("HOME", 1, data));
	else if (data->commands[1][0] == '/')
		dir = ft_strdup(data->commands[1]);
	else
	{
		dir = ft_strdup(get_env("PWD", 1, data));
		str_append(&dir, "/");
		str_append(&dir, data->commands[1]);
	}
	if (chdir(dir) == 0)
		return (modify_directory(dir, data));
	free(dir);
	return (1);
}

//Checks if the file exists and if the user has acces to it.
//Then executes the file.
int	execute(t_data *data)
{
	char	*full_path;

	if (access(data->commands[0], X_OK) != 0)
	{
		full_path = find_file(data->commands[0], data);
		if (full_path == NULL && access(data->commands[0], F_OK) != 0)
			return (error_message(127,
					"error: file or directory does not exist\n", NULL));
		else if (full_path != NULL && access(full_path, X_OK) == 0)
		{
			free(data->commands[0]);
			data->commands[0] = full_path;
		}
		else
			return (error_message(126,
					"error: cannot access file\n", full_path));
	}
	if (execve(data->commands[0], data->commands, data->environment) == -1)
		return (error_message(1, "error: execution failed\n", NULL));
	return (0);
}

int	export(t_data *data)
{
	char	*key;
	int		equals;

	if (args_size(data->commands) == 1)
		return (print_env(data));
	equals = find_chr(data->commands[1], '=', 0, 0);
	if (equals > 0)
	{
		key = ft_substr(data->commands[1], 0, equals);
		if (find_non_alnum(key, 0) == -1)
		{
			set_env(key, data);
			free(key);
			return (0);
		}
		free(key);
		return (1);
	}
	return (1);
}

int	unset(t_data *data)
{
	char	**env_var;

	if (args_size(data->commands) == 1)
		return (0);
	env_var = (char **)get_env(data->commands[1], 0, data);
	if (env_var == NULL)
		return (0);
	return (remove_from_args(&data->environment, *env_var));
}
