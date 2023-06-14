/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_adddel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minslee <minslee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:34:13 by minslee           #+#    #+#             */
/*   Updated: 2022/06/23 19:34:49 by minslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_lstadd_back(t_stack *st, t_list *new)
{
	t_list	*tmp;

	if (!(st->lst))
	{
		st->lst = new;
		(st->len)++;
		return ;
	}
	tmp = st->lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (!new)
		tmp->next = NULL;
	else
		tmp->next = new;
	(st->len)++;
}

void	ft_lstadd_front(t_stack **st, t_list *new)
{
	if (!((*st)->lst))
	{
		(*st)->lst = new;
		((*st)->len)++;
		return ;
	}
	else if (!new)
		return ;
	new->next = (*st)->lst;
	(*st)->lst = new;
	((*st)->len)++;
}

void	ft_lstdel_front(t_stack **st)
{
	t_list	*tmp;

	if (!((*st)->lst))
		return ;
	tmp = (*st)->lst->next;
	free((*st)->lst);
	(*st)->lst = tmp;
	((*st)->len)--;
}

void	ft_lstdel_back(t_stack *st)
{
	t_list	*tmp;

	tmp = st->lst;
	if (!(tmp))
		return ;
	while (tmp->next->next != NULL)
		tmp = tmp->next;
	free(tmp->next);
	tmp->next = NULL;
	(st->len)--;
}
