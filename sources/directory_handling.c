/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   directory_handling.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/08 22:28:16 by ferre         #+#    #+#                 */
/*   Updated: 2024/12/20 07:09:55 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

char	*str_token(char **str, char token)
{
	int		i;
	int		len;
	char	*old_str;
	char	*tok_str;

	old_str = *str;
	len = ft_strlen(old_str);
	if (len == 0)
		return (NULL);
	i = find_chr(old_str, token, 0, 0);
	if (i == -1)
		i = len;
	tok_str = ft_substr(old_str, 0, i);
	*str = ft_substr(old_str, i + 1, len - i - 1);
	free(old_str);
	return (tok_str);
}

char	*build_full_path(char *dir_path, char *file_name)
{
	int		path_len;
	int		needs_slash;
	char	*full_path;

	path_len = (int)ft_strlen(dir_path);
	needs_slash = 0;
	if (dir_path[path_len - 1] != '/')
		needs_slash = 1;
	full_path = ft_strdup(dir_path);
	if (full_path == NULL)
		return (NULL);
	if (needs_slash != 0)
		str_append(&full_path, "/");
	str_append(&full_path, file_name);
	return (full_path);
}

char	*search_dir(char *file_name, char *dir_path)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*full_path;

	dir = opendir(dir_path);
	if (dir == NULL)
		return (NULL);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (str_equals(entry->d_name, file_name))
		{
			full_path = build_full_path(dir_path, file_name);
			if (full_path == NULL)
			{
				closedir(dir);
				return (NULL);
			}
			closedir(dir);
			return (full_path);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (NULL);
}

char	*find_file(char *file_name, t_data *data)
{
	char	*path_env;
	char	*path_copy;
	char	*dir;
	char	*result;

	path_env = get_env("PATH", 1, data);
	if (path_env == NULL)
		return (NULL);
	path_copy = strdup(path_env);
	result = NULL;
	dir = str_token(&path_copy, ':');
	while (dir != NULL)
	{
		result = search_dir(file_name, dir);
		free(dir);
		if (result != NULL)
			break ;
		dir = str_token(&path_copy, ':');
	}
	if (path_copy)
		free(path_copy);
	return (result);
}

int	modify_directory(char *dir, t_data *data)
{
	char	**pwd;

	pwd = (char **)get_env("OLDPWD", 0, data);
	clear(pwd);
	*pwd = add_str("OLDPWD=", get_env("PWD", 1, data));
	pwd = (char **)get_env("PWD", 0, data);
	clear(pwd);
	free(dir);
	dir = getcwd(NULL, 0);
	*pwd = add_str("PWD=", dir);
	free(dir);
	return (0);
}
