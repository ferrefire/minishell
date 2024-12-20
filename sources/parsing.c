/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/20 15:28:25 by ferre         #+#    #+#                 */
/*   Updated: 2024/12/20 16:00:09 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <unistd.h>
#include <stdlib.h>

void	parse_command(char **parsed, char *command, int start, t_data *data)
{
	char	*add;
	t_quote	next_quote;
	int		offset;
	int		i;

	while (start < (int)ft_strlen(command))
	{
		offset = 0;
		next_quote = find_quote(command, start);
		i = (int)ft_strlen(command);
		if (next_quote.complete)
		{
			i = next_quote.start;
			if (start == next_quote.start && ++offset)
				i = next_quote.end;
		}
		data->ignore_commands[ft_strlen(data->ignore_commands) - 1]
			= offset + '0';
		add = ft_substr(command, start + offset, i - start - offset);
		if (!offset || next_quote.type == 34)
			replace_env(&add, data);
		start = i + offset;
		str_append(parsed, add);
		free(add);
	}
}

int	setup_command(int start, int end, t_data *data)
{
	char	*command;
	char	*parsed;
	int		index;

	if (end - start <= 0)
		return (1);
	command = ft_substr(data->prompt, start, end - start);
	parsed = ft_strdup("");
	start = 0;
	str_append(&data->ignore_commands, "0");
	parse_command(&parsed, command, start, data);
	free(command);
	add_to_args(&data->commands, parsed);
	index = args_size(data->commands) - 1;
	if (index > 0 && data->ignore_commands[index] == '0'
		&& find_str(RE, data->commands[index],
			ft_strlen(data->commands[index])) != -1
		&& valid_meta(index - 1, data)
		&& (str_equals(data->commands[index], PIPE)
			|| !str_equals(data->commands[index - 1], PIPE)))
		return (0);
	return (1);
}

int	start_parse(int start, int size, t_data *data)
{
	int		meta;
	t_quote	quote;

	while (start < size)
	{
		meta = find_meta(data->prompt, start);
		quote = find_quote(data->prompt, start);
		if (meta != -1 && quote.complete && quote.start < meta)
			meta = find_meta(data->prompt, quote.end);
		if (meta == -1)
			meta = size;
		if (!setup_command(start, meta, data))
			return (0);
		start = meta + 1;
		if (data->prompt[meta] != ' ' && data->prompt[meta] != '\t'
			&& find_chr(META, data->prompt[meta], 0, 0) != -1)
		{
			start = find_chr(data->prompt, data->prompt[meta], meta, 1);
			if (start == meta)
				start = meta + 1;
			if (!setup_command(meta, start, data))
				return (0);
		}
	}
	return (1);
}

int	parse_commands(t_data *data)
{
	int	start;
	int	size;
	int	index;

	resize_args(&data->commands, 0);
	start = 0;
	size = ft_strlen(data->prompt);
	if (!start_parse(start, size, data))
		return (0);
	index = args_size(data->commands) - 1;
	if (index > 0 && data->ignore_commands[index] == '0'
		&& find_str(RE, data->commands[index],
			ft_strlen(data->commands[index])) != -1
		&& !str_equals(data->commands[index], PIPE))
		return (0);
	return (1);
}

int	valid_meta(int next, t_data *data)
{
	if (find_str(RE, data->commands[next],
			ft_strlen(data->commands[next])) == -1)
		return (0);
	if (next >= args_size(data->commands)
		|| (next == args_size(data->commands) - 1
			&& !str_equals(data->commands[next], PIPE)))
		return (0);
	if (data->ignore_commands[next] != '0')
		return (0);
	return (1);
}
