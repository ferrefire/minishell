/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_handling.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 19:24:18 by ferre         #+#    #+#                 */
/*   Updated: 2024/05/28 07:18:31 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_file(char **command)
{
    if (execve(command[0], command, NULL) == -1)
    {
        printf("Error when executing\n");
        return (0);
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
    int     i;
    int		start;
	char	*standard;

	start = 1;
	standard = "\n";
	if (command[start] && ft_strncmp(command[start], "-n", 0) == 0)
	{
        start++;
        standard = "";
    }
	i = 0;
	while (command[start + i])
	{
		if (i > 0)
			printf(" ");
		printf("%s", command[start + i]);
        i++;
	}
	printf("%s", standard);
	return (1);
}

int built_in(char **command)
{
    if (ft_strncmp(command[0], "cd", 0) == 0)
        chdir(command[1]);
    else if (ft_strncmp(command[0], "echo", 0) == 0)
        echo(command);
    else if (ft_strncmp(command[0], "pwd", 0) == 0)
        print_working_dir();
    exit(EXIT_SUCCESS);
}

int handle_command(char **command)
{
    char    **cmd_args;
	int     p;

    if (ft_strncmp(command[0], "exit", 0) == 0)
        exit(EXIT_SUCCESS);
    else if (ft_strncmp(command[0], "cd", 0) == 0)
        return (chdir(command[1]) + 1);
    p = direct(command);
	if (p != 0)
    {
        if (p == 1)
            cmd_args = copy_args(command, 0, 1);
        else if (p == 2)
        {
            cmd_args = copy_args(command + args_count(command, 1) + 1, -1, 0);
            handle_command(cmd_args);
            clean_args(cmd_args);
            exit(EXIT_SUCCESS);
        }
        if (in_str(cmd_args[0], BUILT_IN_CMD) == 1)
            built_in(cmd_args);
        else if (get_exec(cmd_args))
            exec_file(cmd_args);
        if (cmd_args)
            clean_args(cmd_args);
        exit(EXIT_SUCCESS);
    }
	return (1);
}
