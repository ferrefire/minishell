/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_handling.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/18 19:37:13 by ferre         #+#    #+#                 */
/*   Updated: 2024/12/20 18:24:07 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

void	iterate_commands(t_data *data)
{
	int	end;

	end = next_direct(0, data);
	if (end == -1)
		resize_args(&data->commands, 0);
	else
		resize_args(&data->commands, end);
}

void	clip_commands(t_data *data)
{
	int	i;
	int	end;
	int	len;

	if (args_size(data->commands) == 1 && str_equals(data->commands[0], PIPE))
		resize_args(&data->commands, 0);
	end = next_direct(0, data);
	if (end == -1)
		return ;
	else if (++end)
	{
		i = 0;
		len = args_size(data->commands);
		while (i < len)
		{
			if (i < end)
				free(data->commands[i]);
			if (i + end < len)
				data->commands[i] = data->commands[i + end];
			else
				data->commands[i] = NULL;
			i++;
		}
		resize_args(&data->commands, len - end);
	}
}

int	run_command(t_data *data)
{
	int	result;

	if (args_size(data->commands) <= 0)
		return (0);
	result = run_built_in(data);
	if (result >= 0)
		return (0);
	if (str_equals(data->commands[0], "echo"))
		result = (echo(data));
	else if (str_equals(data->commands[0], "pwd"))
	{
		printf("%s\n", get_env("PWD", 1, data));
		result = 0;
	}
	else
		result = (execute(data));
	data->error = ((result) << 8) & 0xff00;
	return (0);
}

int	run_built_in(t_data *data)
{
	int	result;

	result = -1;
	if (str_equals(data->commands[0], "exit"))
		result = (exit_shell(data));
	else if (str_equals(data->commands[0], "cd"))
		result = (cd(data));
	else if (str_equals(data->commands[0], "export"))
		result = (export(data));
	else if (str_equals(data->commands[0], "unset"))
		result = (unset(data));
	if (result >= 0)
		data->error = ((result) << 8) & 0xff00;
	return (result);
}

int	process_commands(t_data *data)
{
	int	child;

	if (args_size(data->commands) <= 0)
		return (1);
	if (next_direct(0, data) == -1 && run_built_in(data) != -1)
		return (1);
	child = direct(data);
	if (child != 0)
	{
		if (child == 1)
		{
			clip_commands(data);
			run_command(data);
			clean(((data->error) & 0xff00) >> 8, data);
		}
		if (child == 2)
		{
			iterate_commands(data);
			process_commands(data);
			clean(((data->error) & 0xff00) >> 8, data);
		}
	}
	return (1);
}
