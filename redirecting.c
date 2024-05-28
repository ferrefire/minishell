/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirecting.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 21:25:11 by ferre         #+#    #+#                 */
/*   Updated: 2024/05/28 07:04:16 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_output(char **result)
{
	int pid;
	int p[2];
	pipe(p);
	int saved_out = dup(1);
	dup2(p[1], 1);
	pid = fork();
	if (pid == 0)
		return (0);
	waitpid(pid, NULL, 0);
	close(p[1]);
	dup2(saved_out, 1);
	close(saved_out);
	//char *result = NULL;
	char *temp;
	temp = get_next_line(p[0]);
	while (temp)
	{
		if (!*result) *result = ft_strdup(temp);
		else *result = str_join_free(*result, temp);
		//free(temp);
		temp = get_next_line(p[0]);
	}
	close(p[0]);
	return (-1);
}

int	redirect_output(int fd)
{
	int	saved_out;
	int	pid;

	saved_out = dup(1);
	dup2(fd, 1);
	pid = fork();
	if (pid == 0)
		return (0);
	waitpid(pid, NULL, 0);
	close(fd);
	dup2(saved_out, 1);
	close(saved_out);
	return (-1);
}

int direct(char **command, char **piped_args)
{
	int i;
	int pid;

	i = -1;
	while (command[++i] && command[i + 1])
	{
		if (ft_strncmp(command[i], RE_OUT, 0) == 0)
			return (redirect_output(open(command[i + 1], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)));
		else if (ft_strncmp(command[i], RE_OUT_APP, 0) == 0)
			return (redirect_output(open(command[i + 1], O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR)));
		else if (ft_strncmp(command[i], PIPE, 0) == 0)
			return (pipe_output(piped_args));
	}
	pid = fork();
	if (pid == 0)
		return (0);
	waitpid(pid, NULL, 0);
	return (-1);
}
