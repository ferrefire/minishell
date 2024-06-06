/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment_handling.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferrefire <ferrefire@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/06 18:36:00 by ferrefire     #+#    #+#                 */
/*   Updated: 2024/06/06 19:50:14 by ferrefire     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int export(t_data *data)
{
    if (!data->commands[1])
        return (print_env(data));
    data->envp = add_to_args(data->commands[1], data->envp);
    return (1);
}

int unset(t_data *data)
{
    if (!data->commands[1])
        return (print_env(data));
    data->envp = rem_from_args(data->commands[1], data->envp);
    return (1);
}

char    *get_env(char *key, int val, t_data *data)
{
    int i;
    int j;

    i = 0;
    while (data->envp[i])
    {
        j = char_index(data->envp[i], '=');
        if (j == (int)ft_strlen(key))
        {
            if (cmp_str(data->envp[i], key, j))
            {
                if (val)
                    return (data->envp[i] + j + 1);
                else
                    return (data->envp[i]);
            }
        }
        i++;
    }
    return (NULL);
}
