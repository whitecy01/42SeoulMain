/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsoo <minslee@student.42seoul.k>              +#+  +:+       +#+   */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 23:06:36 by minslee           #+#    #+#             */
/*   Updated: 2022/07/27 22:34:12 by minslee           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_list
{
	int				data;
	struct s_list	*next;
}	t_list;

typedef struct s_stack
{
	int		len;
	t_list	*lst;
}	t_stack;

int		check_if_valid(char *str);
int		check_if_sorted(t_stack st);
int		check_if_double(t_stack st);

int		get_index(t_stack *a, int data);
void	if_case_four(t_stack *a, t_stack *b);
void	if_case_five(t_stack *a, t_stack *b);

void	free_str(char **str, int row);
char	**ft_split(char const *s);

int		ft_atoi(const char *str);
int		ft_strlen(const char *str);
int		if_in_space(char *str);
int		is_all_digit(char *str);

void	ft_lstadd_back(t_stack *st, t_list *new);
void	ft_lstadd_front(t_stack **st, t_list *new);
void	ft_lstdel_front(t_stack **st);
void	ft_lstdel_back(t_stack *st);

t_list	*ft_lstnew(int data);
t_list	*ft_lstlast(t_list *lst);

void	numbering_stack(t_stack *st);

void	b_from_a(t_stack *a, t_stack *b);
void	if_case_over_five(t_stack *a, t_stack *b);

int		push(t_stack **from, t_stack **to, char *msg);

int		rotate(t_stack **st, char *msg);
int		rr(t_stack **a, t_stack **b);
int		r_rotate(t_stack **st, char *msg);
int		rrr(t_stack **a, t_stack **b);

int		swap(t_stack **st, char *msg);
int		ss(t_stack **a, t_stack **b);

void	if_case_two(t_stack *st, int a_b, int sort);
void	if_case_three(t_stack *a, int step);

void	print_list(t_list *lst);

#endif
