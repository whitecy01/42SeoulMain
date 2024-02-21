/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minslee <minslee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:34:13 by minslee           #+#    #+#             */
/*   Updated: 2022/06/23 19:34:49 by minslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_if_valid(char *str)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		if ((str[index] >= '0' && str[index] <= '9') || str[index] == ' ' \
			|| str[index] == '-' || str[index] == '+')
		{
			if (str[index] == '-' || str[index] == '+')
				if (str[index + 1] != '\0' && (str[index + 1] < '0' \
					|| str[index + 1] > '9'))
					exit(write(1, "Error\n", 6) || 1);
			index++;
			continue ;
		}
		else
			exit(write(1, "Error\n", 6) || 1);
	}
	return (1);
}

int	check_if_sorted(t_stack st)
{
	while (st.lst->next != NULL)
	{
		if ((st.lst->data) >= (st.lst->next->data))
			return (1);
		st.lst = st.lst->next;
	}
	return (0);
}

int	check_if_double(t_stack st)
{
	t_list	*tmp;

	while (st.lst != NULL)
	{
		tmp = st.lst->next;
		while (tmp != NULL)
		{
			if (st.lst->data == tmp->data)
			{
				write(1, "Error\n", 6);
				return (0);
			}
			tmp = tmp->next;
		}
		st.lst = st.lst->next;
	}
	return (1);
}
