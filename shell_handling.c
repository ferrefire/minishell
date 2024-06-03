/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferrefire <ferrefire@student.42.fr>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/31 14:18:51 by ferrefire     #+#    #+#                 */
/*   Updated: 2024/06/03 22:06:46 by ferrefire     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int clamp(int i, int max)
{
    if (i > max)
        return (max);
    return (i);
}

int check_commands(t_data *data)
{
    char    **commands;
    char    *new_command;
    int     i;
    int     max;
    int     in_quotes;

    i = -1;
    max = ft_strlen(data->command_line) * 2 + 1;
    new_command = malloc(max);
    new_command[0] = '\0';
    commands = NULL;
    in_quotes = 0;
    while (i == -1 || data->command_line[i])
    {
        while (data->command_line[++i] && (in_quotes || data->command_line[i] != ' '))
        {
            if (data->command_line[i] == '"')
                in_quotes = 1 - in_quotes;
            else
            {
                if (!in_quotes && in_str(data->command_line + i, METACHARS, 1) == 1)
                    ft_strlcat(new_command, "$", clamp(ft_strlen(new_command) + 2, max));
                ft_strlcat(new_command, data->command_line + i, clamp(ft_strlen(new_command) + 2, max));
            }
        }
        if (ft_strlen(new_command) > 0)
        {
            if (ft_strlen(new_command) > 2 && new_command [0] == '$' && new_command[1] == '$' && getenv(new_command + 2))
                commands = add_to_args(getenv(new_command + 2), commands);
            else
                commands = add_to_args(new_command, commands);
            new_command[0] = '\0';
        }
    }
    data->commands = commands;
    if (new_command)
        free(new_command);
    return (1);
}

int edit_commands(t_data *data, int mode)
{
    char **new_commands;

    if (mode == CLIP)
        new_commands = copy_args(data->commands, -1, 1);
    else if (mode == ITERATE)
        new_commands = copy_args(data->commands + args_count(data->commands, 1) + 1, -1, 0);
    else
        return (0);
    clean_args(data->commands);
    data->commands = new_commands;
    return (1);
}

//int iterate_commands(t_data *data)
//{
//    char    **new_commands;
//
//    new_commands = copy_args(data->commands + args_count(data->commands, 1) + 1, -1, 0);
//    clean_args(data->commands);
//    data->commands = new_commands;
//    return (1);
//}

int quit_shell(int exit_code, char *error, t_data *data)
{
    if (error)
        printf("%s\n", error);
    //clean_shell(data);
    if (data)
    {
        if (data->command_line)
            free(data->command_line);
        if (data->cdir)
            free(data->cdir);
        if (data->commands)
            clean_args(data->commands);
        if (data->envp)
            clean_args(data->envp);
        free(data);
    }
    clear_history();
    exit(exit_code);
}

//int clean_shell(t_data *data)
//{
//    if (data)
//    {
//        if (data->command_line)
//            free(data->command_line);
//        if (data->cdir)
//            free(data->cdir);
//        if (data->commands)
//            clean_args(data->commands);
//        free(data);
//    }
//    return (1);
//}

int export(t_data *data)
{
    if (!data->commands[1])
        return (print_env(data));
    data->envp = add_to_args(data->commands[1], data->envp);
    return (1);
}
