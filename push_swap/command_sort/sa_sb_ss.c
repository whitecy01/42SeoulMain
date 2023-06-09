/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sa_sb_ss.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:36:12 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/09 17:37:08 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../head/push_swap.h"

void	sa(t_stack **a)
{
	t_node	*change;
	int		tmp;

	if (!((*a)->top))
		return ;
	change = (*a)->top;
	if (!(change->next))
		return ;
	change = change->next;
	tmp = change->content;
	change->content = (*a)->top->content;
	(*a)->top->content = tmp;
}

void	sb(t_stack **b)
{
	t_node	*change;
	int		tmp;

	if (!((*b)->top))
		return ;
	change = (*b)->top;
	if (!(change->next))
		return ;
	change = change->next;
	tmp = change->content;
	change->content = (*b)->top->content;
	(*b)->top->content = tmp;
}

void	ss(t_stack **a, t_stack **b)
{
	sa(a);
	sb(b);
}
