/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:58:07 by slambert          #+#    #+#             */
/*   Updated: 2025/12/09 16:42:17 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cur;
	t_list	*next;

	if (lst && del)
	{
		cur = *lst;
		while (cur)
		{
			next = cur->next;
			del(cur->content);
			free(cur);
			cur = next;
		}
		*lst = NULL;
	}
}
