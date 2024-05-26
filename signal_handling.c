/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handling.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 16:03:29 by ferre         #+#    #+#                 */
/*   Updated: 2024/05/26 20:24:07 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void interrupt_shell(int signal)
{
	if (signal != SIGINT)
		return;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
