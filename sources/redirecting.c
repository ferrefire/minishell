/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirecting.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/02 17:43:29 by ferre         #+#    #+#                 */
/*   Updated: 2024/12/20 16:01:55 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int	redirect_stream(int fd, int redirect_fd, int forced, t_data *data)
{
	int	original_out;
	int	pid;

	if (fd == -1 || forced)
	{
		if (fd == -1)
			data->error = ((1) << 8) & 0xff00;
		else
			close(fd);
		return (0);
	}
	original_out = dup(redirect_fd);
	dup2(fd, redirect_fd);
	pid = fork();
	if (pid == 0)
	{
		add_to_args(&data->open_fds, ft_itoa(original_out));
		add_to_args(&data->open_fds, ft_itoa(fd));
		return (2);
	}
	waitpid(pid, NULL, 0);
	close(fd);
	dup2(original_out, redirect_fd);
	close(original_out);
	return (0);
}

int	pipe_output(t_data *data)
{
	int	pid;
	int	pid2;
	int	p[2];

	pid = fork();
	if (pid == 0)
	{
		pipe(p);
		pid2 = fork();
		if (pid2 == 0)
		{
			close(p[1]);
			dup2(p[0], STDIN_FILENO);
			add_to_args(&data->open_fds, ft_itoa(p[0]));
			return (1);
		}
		close(p[0]);
		dup2(p[1], STDOUT_FILENO);
		add_to_args(&data->open_fds, ft_itoa(p[1]));
		return (2);
	}
	waitpid(pid, NULL, 0);
	return (0);
}

int	check_repeat(int next, t_data *data)
{
	int	repeat;
	int	type;

	type = 0;
	if (str_equals(data->commands[next], RE_IN))
		type = 1;
	else if (find_chr(data->commands[next], '>', 0, 0) != -1)
		type = 2;
	if (type)
	{
		repeat = 1;
		while (next_direct(repeat, data) != -1
			&& (int)ft_strlen(data->commands[next_direct(repeat, data)]) <= type
			&& find_chr(data->commands[next_direct(repeat, data)],
				data->commands[next][0], 0, 0) != -1)
			if (direct_repeat(next_direct(repeat, data), 1, data) == 2
				|| ++repeat == -1)
				clean(EXIT_SUCCESS, data);
		next = direct_repeat(next, 0, data);
		while (--repeat > 0)
			iterate_commands(data);
		return (next);
	}
	return (direct_repeat(next, 0, data));
}

//Creates a child to be used for executing files.
//The function returns 1 for a child and 0 for a parent.
int	direct(t_data *data)
{
	int	pid;
	int	next;

	next = next_direct(0, data);
	if (next != -1)
		return (check_repeat(next, data));
	pid = fork();
	if (pid == 0)
		return (1);
	waitpid(pid, &data->error, 0);
	return (0);
}

int	next_direct(int offset, t_data *data)
{
	int	i;

	i = (args_size(data->commands) - 1);
	while (i >= 0)
	{
		if (valid_meta(i, data) && offset-- <= 0)
			return (i);
		i--;
	}
	return (-1);
}
