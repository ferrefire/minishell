/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_handling.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferrefire <ferrefire@student.42.fr>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 19:24:18 by ferre         #+#    #+#                 */
/*   Updated: 2024/06/03 21:56:59 by ferrefire     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_file(t_data *data)
{
    if (execve(data->commands[0], data->commands, data->envp) == -1)
        quit_shell(0, "error when executing file", data);
    return (quit_shell(EXIT_SUCCESS, NULL, data));
}

//int print_working_dir(t_data *data)
//{
//	printf("%s\n", data->cdir);
//	return (1);
//}

int print_env(t_data *data)
{
    int i;

    i = 0;
    while (data->envp[i])
    {
        printf("%s\n", data->envp[i]);
        i++;
    }
    return (1);
}

int	echo(t_data *data)
{
    int     i;
    int		start;
	char	*standard;

	start = 1;
	standard = "\n";
    if (data->commands[start] && ft_strncmp(data->commands[start], "-n", 0) == 0)
    {
        start++;
        standard = "";
    }
	i = 0;
    while (data->commands[start + i])
    {
		if (i > 0)
			printf(" ");
		printf("%s", data->commands[start + i]);
        i++;
	}
	printf("%s", standard);
	return (1);
}

int built_in(t_data *data)
{
    if (ft_strncmp(data->commands[0], "echo", 0) == 0)
        echo(data);
    else if (ft_strncmp(data->commands[0], "pwd", 0) == 0)
        printf("%s\n", data->cdir);
    else if (ft_strncmp(data->commands[0], "env", 0) == 0)
        print_env(data);
    return (quit_shell(EXIT_SUCCESS, NULL, data));
}

int handle_command(t_data *data)
{
	int     p;

    if (ft_strncmp(data->commands[0], "exit", 0) == 0)
        quit_shell(EXIT_SUCCESS, NULL, data);
    else if (ft_strncmp(data->commands[0], "cd", 0) == 0)
        return (chdir(data->commands[1]) + 1);
    else if (ft_strncmp(data->commands[0], "export", 0) == 0)
        return (export(data));
    p = direct(data->commands);
	if (p != 0)
    {
        if (p == 1)
            edit_commands(data, CLIP);
        if (p == 2)
        {
            edit_commands(data, ITERATE);
            handle_command(data);
            return quit_shell(EXIT_SUCCESS, NULL, data);
        }   
        if (in_str(data->commands[0], BUILT_IN_CMD, 0) == 1)
            built_in(data);
        else if (get_exec(data))
            exec_file(data);
        return quit_shell(EXIT_SUCCESS, NULL, data);
    }
	return (1);
}
