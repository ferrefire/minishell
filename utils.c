/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferrefire <ferrefire@student.42.fr>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 16:36:46 by ferre         #+#    #+#                 */
/*   Updated: 2024/05/31 14:59:07 by ferrefire     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int in_str(char *s, char *str)
{
	char **strs;
	int i;
	int found;

	if (!s || ft_strlen(s) == 0)
		return (-1);
    strs = ft_split(str, ' ');
    found = 0;
	i = -1;
    while (strs[++i])
    {
        if (ft_strncmp(strs[i], s, ft_strlen(strs[i])) == 0)
        {
			found = 1;
			break;
		}
	}
    clean_args(strs);
    return (found);
}

int get_exec(t_data *data)
{
    char    *exec_path;

    if (access(data->commands[0], X_OK) == 0)
        return (1);
    else
    {
        exec_path = find_file(data->commands[0]);
        if (exec_path)
        {
            free(data->commands[0]);
            data->commands[0] = exec_path;
            if (access(data->commands[0], X_OK) == 0)
                return (1);
        }
    }
    return (0);
}

char	*str_join_free(char *s1, char *s2, int f1, int f2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (s1 && f1)
		free(s1);
	if (s2 && f2)
		free(s2);
	return (str);
}

char	**clean_args(char **arr)
{
	int	i;

    if (!arr)
        return (NULL);
    i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

int	args_count(char **args, int meta_break)
{
	int	i;

	i = 0;
	while (args && args[i])
	{
		if (meta_break && in_str(args[i], METACHARS) == 1)
			break ;
		++i;
	}
	return (i);
}

char	**copy_args(char **args, int amount, int meta_break)
{
	char	**new_args;
	int	i;

	if (meta_break || args_count(args, 0) < amount || amount == -1)
		amount = args_count(args, meta_break);
	new_args = malloc(sizeof(void *) * (amount + 1));
	i = -1;
	while (++i < amount)
		new_args[i] = ft_strdup(args[i]);
	new_args[i] = NULL;
	return (new_args);
}