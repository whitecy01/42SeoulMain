/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:09:17 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/25 15:19:41 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>

# define A 1
# define B 2

typedef struct s_node
{
	int				content;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct s_stack
{
	int					size;
	int					flag;
	struct s_node		*top;
	struct s_node		*bottom;
}	t_stack;

void	print_error(int error);
void	empty_string_number_check(char *argv);
void	overlap_check(int *temp, int array_size);
char	**check_input_spilt(int argc, char **argv, int *array_size);
int		check_input_size(char *argv);
char	**input_split(char **argv, int argc, int array_size);
char	**input_split_argv(char **str, char *argv, int *two_malloc_count);
int		string_check(char s);
int		check_input_separator(char c);
char	*ft_substr(char *s, int *start);
int		ft_strlen(const char *s, int start);
int		*change_int(char **array_split, int *array_size);
int		ft_atoi(char *str);
long	atoi_while(char *str);
char	**ft_free(char **word);
t_stack	*create_stack(int array_size, int flag);
t_node	*create_node(int array_answer);
void	node_pushback(t_node **pr, t_node *new);
void	stack_a_push_node(int *array, int array_size, t_stack **stack);
void	push_a(t_stack **a, t_node *change);
void	push_b(t_stack **b, t_node *change);
void	pb(t_stack **a, t_stack **b);
void	pa(t_stack **a, t_stack **b);
void	ra(t_stack **a);
void	rb(t_stack **b);
void	rr(t_stack **a, t_stack **b);
void	rra(t_stack **a);
void	rrb(t_stack **b);
void	rrr(t_stack **a, t_stack **b);
void	sa(t_stack **a);
void	sb(t_stack **b);
void	ss(t_stack **a, t_stack **b);
void	swap(int *first, int *second);
int		partiton(int *array, int start, int end);
void	quick_sort(int *array, int start, int end);
int		*ch_array_quick_sort(t_stack **a, int array_size);
void	sort_alogorithm_ra(t_stack **a, int *ra_count);
void	sort_alogorithm_pb(t_stack **a, t_stack **b, int *pb_count);
void	sort_alogorithm_rb(t_stack **b, int *rb_count);
void	ra_rb_pb_reset(int *ra_count, int *rb_count, int *pb_count);
void	sort_algorithm(t_stack **a, t_stack **b, int array_size);
int		stack_top_count(t_stack **stack);
int		pivot_answer(t_stack **stack, int count);
int		pivot_answer2(t_stack **stack, int array_size);
void	three_underonly_fuc_a(t_stack **a, int array_size);
void	three_underonly_fuc_b(t_stack **a, t_stack **b, int array_size);
void	three_only_a(t_stack **stacks, int cnt);
void	under_three_a(t_stack **a_stack, int cnt);
void	three_only_b(t_stack **stacks, int cnt);
void	under_three_b(t_stack **b_stack, int cnt);
void	a_to_b(t_stack **a, t_stack **b, int array_size);
void	ra_rb_pb_while(t_stack **a, t_stack **b, int array_size, int *count);
void	one_plus_one_rr(t_stack **a, t_stack **b, int *ra_count, int *turn);
int		ra_rb_sum_rrr(int ra_count, int rb_count, t_stack **a, t_stack **b);
void	rrb_a_to_b(int rb_count, t_stack **b, int turn);
void	rra_a_to_b(int ra_count, t_stack **a, int turn, int array_size);
void	reset_count_array(int *count);
void	b_to_a(t_stack **a, t_stack **b, int array_size);
void	ra_rb_pb_while_b(t_stack **a, t_stack **b, int array_size, int *count);
void	push_pa(t_stack **a, t_stack **b, int array_size);
void	sort_alogorithm_rb_b(t_stack **b, int *rb_count);
void	sort_alogorithm_pa_b(t_stack **a, t_stack **b, int *pa_count);
void	sort_alo_rr_b(t_stack **a, t_stack **b, int *rb_count, int *turn);
int		check_sorted(t_node *tmp, int cnt, int stack);
#endif 