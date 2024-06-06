/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferrefire <ferrefire@student.42.fr>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 16:36:46 by ferre         #+#    #+#                 */
/*   Updated: 2024/06/06 19:48:19 by ferrefire     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int in_str(char *s, char *str, int size)
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
        if (ft_strncmp(strs[i], s, size) == 0)
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

char	*str_add(char *s1, char *s2, int f1, int f2)
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
		if (meta_break && in_str(args[i], ARG_METACHARS, 0) == 1)
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

char    **add_to_args(char *add, char **args)
{
    char    **new_args;
    int     new_count;
    int     i;

    new_count = args_count(args, 0) + 1;
        new_args = malloc(sizeof(void *) * (new_count + 1));
    i = -1;
    while (++i < (new_count - 1))
        new_args[i] = ft_strdup(args[i]);
    new_args[i] = ft_strdup(add);
    new_args[++i] = NULL;
    if (args)
        clean_args(args);
    //free(add);
    return (new_args);
}

char **rem_from_args(char *add, char **args)
{
    char **new_args;
    int new_count;
    int i;
    int j;

    new_count = args_count(args, 0);
    new_args = malloc(sizeof(void *) * (new_count + 1));
    i = -1;
    j = 0;
    while ((++i + j) < (new_count - 1))
    {
        if (cmp_str(add, args[i], -1))
            j = -1;
        else
            new_args[i + j] = ft_strdup(args[i]);
    }
    new_args[i + j] = NULL;
    if (args)
        clean_args(args);
    // free(add);
    return (new_args);
}

int char_index(char *str, char c)
{
    int i;

    i = 0;
    while (str && str[i])
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (-1);
}

int cmp_str(const char *s1, const char *s2, int len)
{
    int i;

    if (!s1 || !s2)
        return (0);
    i = 0;
    while (s1[i] && s2[i] && (i < len || len == -1))
    {
        if (s1[i] != s2[i])
            return (0);
        i++;
        if (i == len)
            return (1);
    }
    if (len == -1 && (!s1[i] && !s2[i]))
        return (1);
    return (0);
}
