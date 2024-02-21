/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minslee <minslee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:34:13 by minslee           #+#    #+#             */
/*   Updated: 2022/06/23 19:34:49 by minslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	div_cases(t_stack *a, t_stack *b)
{
	if (a->len == 2)
		if_case_two(a, 0, 1);
	else if (a->len == 3)
		if_case_three(a, 0);
	else if (a->len == 4)
		if_case_four(a, b);
	else if (a->len == 5)
		if_case_five(a, b);
	else
		if_case_over_five(a, b);
}

static int	set_list(t_stack *a, char **argv)
{
	char	**str;
	int		index;

	while (*(++argv) != NULL)
	{
		if (check_if_valid(*argv) == 0)
			return (0);
		else
		{
			if (if_in_space(*argv) == 1)
			{
				str = ft_split(*argv);
				index = 0;
				while (str[index] != NULL)
					ft_lstadd_back(a, ft_lstnew(ft_atoi(str[index++])));
				free_str(str, a->len);
			}
			else
				ft_lstadd_back(a, ft_lstnew(ft_atoi(*argv)));
		}
	}
	return (1);
}

static int	init_list(t_stack *a, t_stack *b, char **argv)
{
	a->lst = (t_list *)malloc(sizeof(t_list));
	a->len = 1;
	b->lst = (t_list *)malloc(sizeof(t_list));
	b->len = 1;
	ft_lstdel_front(&a);
	ft_lstdel_front(&b);
	if (set_list(a, argv) == 0)
		return (0);
	else
		return (1);
}

static void	free_list(t_stack *st)
{
	t_list	*tmp;

	while (st->lst != NULL)
	{
		tmp = st->lst->next;
		free(st->lst);
		st->lst = tmp;
	}
}

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	if (argc == 1)
		return (0);
	a = (t_stack *)malloc(sizeof(t_stack));
	b = (t_stack *)malloc(sizeof(t_stack));
	if (init_list(a, b, argv) == 0)
		return (0);
	if (check_if_sorted(*a) == 0 || check_if_double(*a) == 0)
		return (0);
	if (a->len == 1)
		return (0);
	numbering_stack(a);
	div_cases(a, b);
	free_list(a);
	free_list(b);
	free(a);
	a = NULL;
	free(b);
	b = NULL;
	return (0);
}
