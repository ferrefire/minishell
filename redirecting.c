/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirecting.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 21:25:11 by ferre         #+#    #+#                 */
/*   Updated: 2024/05/28 04:19:01 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_output()
{
	char	result[1];
	int	p[2];
	int	pid;

	pipe(p);
	pid = fork();
	if (pid == 0)
		return (p[1]);
	waitpid(pid, NULL, 0);
	//result = get_next_line(p[0]);
	//while (result)
	//{
	//	printf("piped: %s\n", result);
	//	free(result);
	//	result = get_next_line(p[0]);
	//}
	printf("piped: \n");
	while (read(p[0], result, 1))
	{
		write(1, result, 1);
	}
	printf("end reached\n");
	close(p[0]);
	return (0);
}

int direct(char **command)
{
	int redirect;
	int saved_out;
	int directing;
	int i;
	int pid;
	int	piped;

	i = -1;
	redirect = 0;
	directing = 0;
	piped = 0;
	while (command[++i] && command[i + 1])
	{
		if (ft_strncmp(command[i], RE_OUT, 0) == 0)
			redirect = open(command[i + 1], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		else if (ft_strncmp(command[i], RE_OUT_APP, 0) == 0)
			redirect = open(command[i + 1], O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
		else if (ft_strncmp(command[i], PIPE, 0) == 0 && ++piped)
			redirect = pipe_output();
		if (redirect)
		{
			saved_out = dup(1);
			dup2(redirect, 1);
			directing = 1;
			break;
		}
	}
	pid = fork();
	if (pid == 0)
	{
		if (piped) return (2);
		return (0);
	}
	waitpid(pid, NULL, 0);
	if (directing)
	{
		close(redirect);
		dup2(saved_out, 1);
		close(saved_out);
		if (piped)
			exit(EXIT_SUCCESS);
	}
	return (-1);
}
