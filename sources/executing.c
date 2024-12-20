/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executing.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/10 02:34:46 by ferre         #+#    #+#                 */
/*   Updated: 2024/12/20 18:08:57 by ferre         ########   odam.nl         */
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

int	args_size(char **args)
{
	int	i;

	if (!args)
		return (0);
	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	direct_repeat(int next, int forced, t_data *data)
{
	int	result;

	data->error = ((0) << 8) & 0xff00;
	if (str_equals(data->commands[next], RE_OUT))
		result = (redirect_stream(open(data->commands[next + 1],
						O_RDWR | O_CREAT | O_TRUNC, S_IRWXU),
					STDOUT_FILENO, forced, data));
	else if (str_equals(data->commands[next], RE_OUT_APP))
		result = (redirect_stream(open(data->commands[next + 1],
						O_RDWR | O_CREAT | O_APPEND, S_IRWXU),
					STDOUT_FILENO, forced, data));
	else if (str_equals(data->commands[next], RE_IN))
		result = (redirect_stream(open(data->commands[next + 1],
						O_RDONLY), STDIN_FILENO, forced, data));
	else if (str_equals(data->commands[next], RE_IN_LIM))
		result = (read_until_del(data->commands[next + 1], data));
	else if (str_equals(data->commands[next], PIPE))
		result = (pipe_output(data));
	else
		return (0);
	if ((((data->error) & 0xff00) >> 8) != 0)
		perror(NULL);
	return (result);
}
