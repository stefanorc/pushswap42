/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbuonvin <vbuonvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:33:54 by vbuonvin          #+#    #+#             */
/*   Updated: 2021/05/19 16:52:52 by vbuonvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		(*lst)->next = NULL;
		(*lst)->previous = NULL;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	new->previous = tmp;
	tmp->next = new;
	free(new->next);
	new->next = NULL;
}
