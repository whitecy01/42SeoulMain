/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sorted_sor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 06:56:13 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/18 07:00:11 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../head/push_swap.h"

int	check_sorted(t_node *tmp, int cnt, int stack)
{
	int	i;

	if (cnt == 1)
		return (1);
	i = 1;
	if (stack == A)
	{
		while (i++ < cnt && tmp->next)
		{
			if (tmp->content > tmp->next->content)
				return (0);
			tmp = tmp->next;
		}
	}
	else if (stack == B)
	{
		while (i++ < cnt && tmp->next)
		{
			if (tmp->content < tmp->next->content)
				return (0);
			tmp = tmp->next;
		}
	}
	return (1);
}