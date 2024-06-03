/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirecting.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 21:25:11 by ferre         #+#    #+#                 */
/*   Updated: 2024/06/03 14:59:49 by ferrefire     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pipe_output()
{
    int pid = fork();
    if (pid == 0)
    {
        int p[2];
        pipe(p);
        int pid2 = fork();
        if (pid2 == 0)
        {
            dup2(p[1], STDOUT_FILENO);
            return (1);
        }
        else
        {
            waitpid(pid2, NULL, 0);
            close(p[1]);
            dup2(p[0], STDIN_FILENO);
            return (2);
        }
    }
    waitpid(pid, NULL, 0);
    return (0);
}

//int	pipe_output(char **result)
//{
//	int pid;
//	int p[2];
//	pipe(p);
//	int saved_out = dup(1);
//	dup2(p[1], 1);
//	pid = fork();
//	if (pid == 0)
//		return (1);
//	waitpid(pid, NULL, 0);
//	close(p[1]);
//	dup2(saved_out, 1);
//	close(saved_out);
//	char *temp;
//	temp = get_next_line(p[0]);
//	while (temp)
//	{
//		if (!*result) *result = ft_strdup(temp);
//		else *result = str_join_free(*result, temp, 1, 1);
//		temp = get_next_line(p[0]);
//	}
//	close(p[0]);
//	return (0);
//}

int redirect_stream(int fd, int redirect_fd)
{
    int saved_out;
    int pid;

    if (fd == -1)
        return (0);
    saved_out = dup(redirect_fd);
    dup2(fd, redirect_fd);
    pid = fork();
    if (pid == 0)
        return (1);
    waitpid(pid, NULL, 0);
    close(fd);
    dup2(saved_out, redirect_fd);
    close(saved_out);
    return (0);
}

int read_until_del(char *delimiter)
{
    int pid = fork();
    if (pid == 0)
    {
        int p[2];
        pipe(p);
        int pid2 = fork();
        if (pid2 == 0)
        {
            dup2(p[1], STDOUT_FILENO);
            char *temp;
            temp = get_next_line(STDIN_FILENO);
            while (temp)
            {
                if (ft_strnstr(temp, delimiter, 0) != NULL)
                    break;
                printf("%s", temp);
                free(temp);
                temp = get_next_line(STDIN_FILENO);
            }
            if (temp)
                free(temp);
            exit(EXIT_SUCCESS);
        }
        else
        {
            waitpid(pid2, NULL, 0);
            close(p[1]);
            dup2(p[0], STDIN_FILENO);
            return (1);
        }
    }
    waitpid(pid, NULL, 0);
    return (0);
}

//int	redirect_output(int fd)
//{
//	int	saved_out;
//	int	pid;
//
//	saved_out = dup(1);
//	dup2(fd, 1);
//	pid = fork();
//	if (pid == 0)
//		return (1);
//	waitpid(pid, NULL, 0);
//	close(fd);
//	dup2(saved_out, 1);
//	close(saved_out);
//	return (0);
//}

int direct(char **command)
{
	int i;
	int pid;

	i = -1;
	while (command[++i] && command[i + 1])
	{
        if (ft_strncmp(command[i], RE_OUT, 0) == 0)
            return (redirect_stream(open(command[i + 1], O_RDWR | O_CREAT | O_TRUNC, S_IRWXU), STDOUT_FILENO));
        else if (ft_strncmp(command[i], RE_OUT_APP, 0) == 0)
            return (redirect_stream(open(command[i + 1], O_RDWR | O_CREAT | O_APPEND, S_IRWXU), STDOUT_FILENO));
        else if (ft_strncmp(command[i], RE_IN, 0) == 0)
            return (redirect_stream(open(command[i + 1], O_RDONLY), STDIN_FILENO));
        else if (ft_strncmp(command[i], RE_IN_DEL, 0) == 0)
            return (read_until_del(command[i + 1]));
        else if (ft_strncmp(command[i], PIPE, 0) == 0)
            return (pipe_output());
	}
	pid = fork();
	if (pid == 0)
		return (1);
	waitpid(pid, NULL, 0);
	return (0);
}
