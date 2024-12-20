/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/18 17:21:17 by ferre         #+#    #+#                 */
/*   Updated: 2024/12/20 16:07:26 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>

int	error_message(int status, char *message, char *to_free)
{
	if (to_free)
		free(to_free);
	if (message)
		ft_putstr_fd(message, STDERR_FILENO);
	return (status);
}

// Frees the memory pointed to by address and sets it to NULL.
//Also checks if it is not already NULL.
void	clear(void *address)
{
	void	**memory;

	memory = (void **)address;
	if (memory != NULL)
	{
		if (*memory != NULL)
		{
			free(*memory);
		}
		*memory = NULL;
	}
}

//Frees the program data.
void	clean(int status, t_data *data)
{
	int	i;

	i = -1;
	if (data != NULL)
	{
		clear_args(&data->commands);
		clear_args(&data->environment);
		clear(&data->ignore_commands);
		clear(&data->prompt);
		clear(&data->previous_prompt);
		clear(&data->prompt_line);
		while (++i < args_size(data->open_fds))
			close(ft_atoi(data->open_fds[i]));
		clear_args(&data->open_fds);
		free(data);
		data = NULL;
	}
	exit(status);
}

//Allocates the program data and checks for arguments.
t_data	*setup(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = NULL;
	if (argc != 1)
	{
		printf("error: no arguments allowed: %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	data = malloc(sizeof(t_data));
	if (data == NULL)
		exit(EXIT_FAILURE);
	data->commands = NULL;
	data->ignore_commands = ft_strdup("");
	data->prompt = NULL;
	data->previous_prompt = NULL;
	data->environment = NULL;
	data->environment = copy_args(envp, -1);
	data->error = 0;
	data->forked = 0;
	data->open_fds = NULL;
	data->prompt_line = NULL;
	return (data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = setup(argc, argv, envp);
	set_signals();
	while (1)
	{
		data->prompt_line = add_str(get_env("PWD", 1, data), "$ ");
		if (!handle_prompt(data))
			break ;
		clear(&data->prompt_line);
	}
	clean(EXIT_SUCCESS, data);
}
