/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_handling.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 19:24:18 by ferre         #+#    #+#                 */
/*   Updated: 2024/05/26 21:59:46 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_file(char **command)
{
	struct stat st;
	int			ppid;

	if (stat(command[0], &st) == 0 && st.st_mode & S_IXUSR)
	{
		ppid = getpid();
		fork();
		if (getpid() != ppid && execve(command[0], command, NULL) == -1)
			printf("Error when executing\n");
		wait(NULL);
	}
	else
	{
		printf("file is not a valid executable: %s\n", command[0]);
		return (0);
	}
	return (1);
}

int print_working_dir()
{
	char	*cdir;

	cdir = getcwd(NULL, 0);
	printf("%s\n", cdir);
	free(cdir);
	return (1);
}

int handle_command(char **command, int count)
{
	int	p[2];
	char *output;
	char *temp;

	if (count == 2 && ft_strncmp(command[1], "|", ft_strlen(command[1])) == 0)
	{
		pipe(p);
		p[1] = dup(1);
	}

	if (ft_strncmp(command[0], "cd", ft_strlen(command[0])) == 0)
		chdir(command[1]);
	else if (ft_strncmp(command[0], "echo", ft_strlen(command[0])) == 0 && ft_strncmp(command[1], "-n", ft_strlen(command[1])) == 0)
		printf("%s", command[2]);
	else if (ft_strncmp(command[0], "echo", ft_strlen(command[0])) == 0)
		printf("%s\n", command[1]);
	else if (ft_strncmp(command[0], "pwd", ft_strlen(command[0])) == 0)
		print_working_dir();
	else if (ft_strncmp(command[0], "exit", ft_strlen(command[0])) == 0)
		exit(EXIT_SUCCESS);
	else
		exec_file(command);

	if (count == 2 && ft_strncmp(command[1], "|", ft_strlen(command[1])) == 0)
	{
		temp = get_next_line(p[0]);
		while (temp)
		{
			output = str_join_free(output, temp);
			temp = get_next_line(p[0]);
		}
		close(p[1]);
		//close(p[0]);
		printf("Gathered output: %s", output);
		free(output);
	}

	return (1);
}