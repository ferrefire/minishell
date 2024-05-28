/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_handling.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 19:24:18 by ferre         #+#    #+#                 */
/*   Updated: 2024/05/28 02:40:20 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_file(char **command)
{
	char	*file_path;

	if (access(command[0], X_OK) == 0)
	{
		if (execve(command[0], copy_args(command, 0, 1), NULL) == -1)
			printf("Error when executing\n");
	}
	else
	{
		file_path = find_file(command[0]);
		if (file_path && access(file_path, X_OK) == 0)
		{
			if (execve(file_path, copy_args(command, 0, 1), NULL) == -1)
				printf("Error when executing\n");
		}
		else
		{
			printf("file is not a valid executable: %s\n", command[0]);
			return (0);
		}
	}
	return (1);
}

int print_working_dir(void)
{
	char	*cdir;

	cdir = getcwd(NULL, 0);
	printf("%s\n", cdir);
	free(cdir);
	return (1);
}

int	echo(char **command)
{
	int		start;
	int		amount;
	char	*standard;
	int		i;

	start = 1;
	amount = 0;
	standard = "\n";
	if (command[start] && ft_strncmp(command[start], "-n", 0) == 0 && ++start)
		standard = "";
	while (command[start + amount])
	{
		if (is_metachar(command[start + amount]))
			break ;
		amount++;
	}
	i = -1;
	while (++i < amount)
	{
		if (i > 0)
			printf(" ");
		printf("%s", command[start + i]);
	}
	printf("%s", standard);
	return (1);
}

int handle_command(char **command, int count)
{
	int p;

	if (count == 0)
		return (1);

	if (ft_strncmp(command[0], "cd", 0) == 0)
		chdir(command[1]);
	else if (ft_strncmp(command[0], "exit", 0) == 0)
		exit(EXIT_SUCCESS);
	p = direct(command);
	if (p > -1)
	{
		if (ft_strncmp(command[0], "echo", 0) == 0)
			echo(command);
		else if (ft_strncmp(command[0], "pwd", 0) == 0)
			print_working_dir();
		else if (!is_metachar(command[p]))
			exec_file(command + p);
		exit(EXIT_SUCCESS);
	}
	return (1);
}