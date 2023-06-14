/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minslee <minslee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:34:13 by minslee           #+#    #+#             */
/*   Updated: 2022/06/23 19:34:49 by minslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	swap(t_stack **st, char *msg)
{
	int	tmp;

	if ((*st)->len < 2)
		return (0);
	tmp = (*st)->lst->data;
	(*st)->lst->data = (*st)->lst->next->data;
	(*st)->lst->next->data = tmp;
	write(1, msg, ft_strlen(msg));
	return (1);
}

int	ss(t_stack **a, t_stack **b)
{
	if (swap(a, "") == 0)
		return (0);
	if (swap(b, "") == 0)
		return (0);
	write(1, "ss\n", 3);
	return (1);
}
