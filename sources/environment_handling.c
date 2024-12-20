/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment_handling.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 15:36:53 by ferre         #+#    #+#                 */
/*   Updated: 2024/12/20 06:43:12 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <stdlib.h>

int	print_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->environment[i])
	{
		printf("%s\n", data->environment[i]);
		i++;
	}
	return (0);
}

char	*get_env(char *key, int val, t_data *data)
{
	int	i;
	int	j;

	i = -1;
	if (str_equals(key, "?"))
		return (ft_itoa((((data->error) & 0xff00) >> 8)));
	while (data->environment[++i])
	{
		j = find_chr(data->environment[i], '=', 0, 0);
		if (j == -1 || j != (int)ft_strlen(key))
			continue ;
		if (ft_strncmp(data->environment[i], key, j) == 0)
		{
			if (val)
				return (data->environment[i] + j + 1);
			return ((char *)&data->environment[i]);
		}
	}
	return (NULL);
}

void	set_env(char *key, t_data *data)
{
	char	**env_address;

	env_address = (char **)get_env(key, 0, data);
	if (env_address == NULL)
		add_to_args(&data->environment, ft_strdup(data->commands[1]));
	else
	{
		free(*env_address);
		*env_address = ft_strdup(data->commands[1]);
	}
}

void	replace_next_env(char **addres, int offset, t_data *data)
{
	char	*str;
	char	*envvar;
	int		i;
	int		j;

	str = *addres;
	i = offset;
	if (str[i + 1] == '?')
		j = i + 2;
	else
		j = find_non_alnum(str, i + 1);
	if (j == -1)
		j = ft_strlen(str);
	str = ft_substr(*addres, i, j - i);
	envvar = get_env(str + 1, 1, data);
	if (envvar == NULL)
		envvar = "";
	str_replace(addres, envvar, i, j);
	if (str_equals(str, "$?"))
		free(envvar);
	free(str);
}

void	replace_env(char **address, t_data *data)
{
	int	i;

	i = find_env_char(*address);
	while (i != -1)
	{
		replace_next_env(address, i, data);
		i = find_env_char(*address);
	}
}
