/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/10 13:36:47 by fmolenbe      #+#    #+#                 */
/*   Updated: 2024/05/26 17:25:22 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"

char	*get_buffer(int *fd, int *end, char *static_s)
{
	char	*temp_s;
	int		i;

	if (static_s != NULL)
		return (static_s);
	i = -1;
	temp_s = malloc(BUFFER_SIZE + 1);
	if (!temp_s)
		return (NULL);
	temp_s[BUFFER_SIZE] = '\0';
	*end = read(*fd, temp_s, BUFFER_SIZE);
	if (*end <= 0)
	{
		free(temp_s);
		return (NULL);
	}
	i = *end - 1;
	while (temp_s[++i] && i <= BUFFER_SIZE)
		temp_s[i] = '\0';
	return (temp_s);
}

int	get_nl(char *s)
{
	int	i;
	int	length;

	if (!s)
		return (-1);
	i = -1;
	length = gnl_len(s);
	while (s[++i])
		if (s[i] == '\n' && i != length)
			return (i);
	return (-1);
}

int	check_empty(char **static_arr)
{
	int	i;

	i = -1;
	while (++i < 100)
		if (static_arr[i] != NULL)
			return (-1);
	return (0);
}

char	**clean_static_arr(char **static_arr, int make)
{
	int	i;

	i = -1;
	if (make == 1)
	{
		if (static_arr != NULL)
			return (static_arr);
		static_arr = malloc(101 * sizeof(char *));
		if (!static_arr)
			return (NULL);
		while (++i <= 100)
			static_arr[i] = NULL;
		return (static_arr);
	}
	i = -1;
	while (++i <= 100)
	{
		if (static_arr[i] != NULL)
		{
			free(static_arr[i]);
			static_arr[i] = NULL;
		}
	}
	free(static_arr);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	**static_arr;
	char		*temp;
	int			end;

	temp = NULL;
	static_arr = clean_static_arr(static_arr, 1);
	if (static_arr == NULL || fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	end = 1;
	static_arr[fd] = get_buffer(&fd, &end, static_arr[fd]);
	while (end > 0 && static_arr[fd] && get_nl(static_arr[fd]) == -1)
		static_arr[fd] = comb(static_arr[fd], get_buffer(&fd, &end, NULL));
	if (end == 0 && static_arr[fd] && get_nl(static_arr[fd]) == -1)
		temp = clean_pointers(static_arr[fd], NULL, 1);
	else if (end > 0 && static_arr[fd] && get_nl(static_arr[fd]) != -1)
	{
		temp = malloc(get_nl(static_arr[fd]) + 2);
		static_arr[fd] = prep(static_arr[fd], temp, get_nl(static_arr[fd]));
	}
	if (static_arr && (static_arr[fd] && (end == -1 || end == 0)))
		static_arr[fd] = clean_pointers(static_arr[fd], NULL, end - 1);
	if (static_arr && check_empty(static_arr) == 0)
		static_arr = clean_static_arr(static_arr, 0);
	return (temp);
}
