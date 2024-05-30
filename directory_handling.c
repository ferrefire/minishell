/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   directory_handling.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/28 01:46:17 by ferre         #+#    #+#                 */
/*   Updated: 2024/05/28 02:20:24 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_dir(char *path)
{
	DIR *dir;
	struct dirent *dent;
	char	*file_name;

	dir = opendir(path);
	if (dir)
		dent = readdir(dir);
	while (dent)
	{
		if (dent)
			file_name = dent->d_name;
		if (file_name)
			printf("%s\n", file_name);
		if (dir)
			dent = readdir(dir);
	}
	if (dir)
		closedir(dir);
	return (1);
}

char	*search_dir(char *file_name, char *dir_path)
{
	DIR *dir;
	struct dirent *dent;
	char *current_file;
	char *file_path;

	file_path = NULL;
	dir = opendir(dir_path);
	if (dir)
		dent = readdir(dir);
	while (dent)
	{
		if (dent)
			current_file = dent->d_name;
		if (current_file && ft_strncmp(current_file, file_name, 0) == 0)
		{
			file_path = ft_strjoin(dir_path, "/");
			file_path = str_join_free(file_path, file_name, 1, 0);
			break ;
		}
		if (dir)
			dent = readdir(dir);
	}
	if (dir)
		closedir(dir);
	return (file_path);
}

char	*find_file(char *file_name)
{
	char	**env_paths;
	char	*file_path;
    //char    *cdir;
	int		i;

    //cdir = str_join_free(getcwd(NULL, 0), ":", 1, 0);
    //env_paths = ft_split(str_join_free(cdir, getenv("PATH"), 1, 0), ':');
    env_paths = ft_split(getenv("PATH"), ':');
    file_path = NULL;
	i = -1;
	while (env_paths[++i])
	{
		file_path = search_dir(file_name, env_paths[i]);
		if (file_path)
			break ;
	}
	clean_args(env_paths);
	return (file_path);
}
