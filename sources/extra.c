/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extra.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/16 17:59:51 by ferre         #+#    #+#                 */
/*   Updated: 2024/12/20 15:56:10 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

int	str_is_num(char *str)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = 0;
	while (i < len)
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exit_shell(t_data *data)
{
	if (args_size(data->commands) == 1)
		clean(EXIT_SUCCESS, data);
	else if (args_size(data->commands) > 2)
		return (error_message(1, "error: too many arguments\n", NULL));
	else if (!str_is_num(data->commands[1]))
		return (error_message(2, "error: argument is not a digit\n", NULL));
	clean(ft_atoi(data->commands[1]), data);
	return (0);
}

void	read_del(char *delimiter, int p[2], t_data *data)
{
	char	*temp;

	dup2(p[1], STDOUT_FILENO);
	temp = get_next_line(STDIN_FILENO);
	while (temp)
	{
		if (ft_strnstr(temp, delimiter, 0) != NULL)
			break ;
		printf("%s", temp);
		free(temp);
		temp = get_next_line(STDIN_FILENO);
	}
	if (temp)
		free(temp);
	close(p[0]);
	close(p[1]);
	clean(EXIT_SUCCESS, data);
}

int	read_until_del(char *delimiter, t_data *data)
{
	int	pid;
	int	pid2;
	int	p[2];

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		pipe(p);
		pid2 = fork();
		if (pid2 == 0)
			read_del(delimiter, p, data);
		else
		{
			waitpid(pid2, NULL, 0);
			close(p[1]);
			add_to_args(&data->open_fds, ft_itoa(p[0]));
			dup2(p[0], STDIN_FILENO);
			return (2);
		}
	}
	waitpid(pid, NULL, 0);
	return (0);
}
