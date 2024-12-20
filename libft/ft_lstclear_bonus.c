/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 18:56:17 by fmolenbe      #+#    #+#                 */
/*   Updated: 2024/05/26 17:36:30 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*temp_next;

	if (!lst)
		return ;
	temp = *lst;
	while (temp)
	{
		temp_next = temp->next;
		if (del)
			(*del)(temp->content);
		free(temp);
		temp = temp_next;
	}
	*lst = NULL;
	lst = NULL;
}
