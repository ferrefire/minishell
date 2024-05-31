/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferrefire <ferrefire@student.42.fr>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/31 14:18:51 by ferrefire     #+#    #+#                 */
/*   Updated: 2024/05/31 15:00:41 by ferrefire     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int clip_commands(t_data *data)
{
    char **new_commands;

    new_commands = copy_args(data->commands, -1, 1);
    clean_args(data->commands);
    data->commands = new_commands;
    return (1);
}

int iterate_commands(t_data *data)
{
    char    **new_commands;

    new_commands = copy_args(data->commands + args_count(data->commands, 1) + 1, -1, 0);
    clean_args(data->commands);
    data->commands = new_commands;
    return (1);
}

int quit_shell(int exit_code, char *error, t_data *data)
{
    if (error)
        printf("%s\n", error);
    clean_shell(data);
    exit(exit_code);
}

int clean_shell(t_data *data)
{
    if (data)
    {
        if (data->command_line)
            free(data->command_line);
        if (data->cdir)
            free(data->cdir);
        if (data->commands)
            clean_args(data->commands);
        free(data);
    }
    return (1);
}