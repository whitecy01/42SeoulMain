/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:09:17 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/15 03:13:01 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>

# include <stdio.h>

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
	char				name;
	struct s_node		*top;
	struct s_node		*bottom;
}	t_stack;

void	print_error(int error);

//split
char	**check_input_spilt(int argc, char **argv, int *array_size);
int		check_input_size(char *argv);
char	**input_split(char **argv, int argc, int array_size);
char	**input_split_argv(char **str, char *argv, int *two_malloc_count);
int		string_check(char s);
int		check_input_separator(char c);
char	*ft_substr(char *s, int *start);
int		ft_strlen(const char *s, int start);
void	empty_string_number_check(char *argv);
void	overlap_check(int *temp, int array_size);

//free
char	**ft_free(char **word);

int		*change_int(char **array_split, int *array_size);
int		ft_atoi(char *str);

t_stack	*create_stack(int array_size, char name);
t_node	*create_node(int array_answer);
void	stack_a_push_node(int *array, int array_size, t_stack **stack);
void	node_pushback(t_node **pr, t_node *new);

void    sort_algorithm(t_stack **a, t_stack **b, int array_size);
void	sa(t_stack **a);
void	sb(t_stack **b);
void	ss(t_stack **a, t_stack **b);

void    pb(t_stack **a, t_stack **b);
void	pa(t_stack **a, t_stack **b);

void	ra(t_stack **a);
void	rb(t_stack **b);
void	rr(t_stack **a, t_stack **b);

void	rra(t_stack **a);
void	rrb(t_stack **b);
void	rrr(t_stack **a, t_stack **b);

int	partiton(int *array, int start, int end);
void	swap(int *first, int *second);
void	quick_sort(int *array, int start, int end);
int		*ch_array_quick_sort(t_stack **a, int array_size);
int	pivot_answer(t_stack **stack, int count);
int	pivot_answer2(t_stack **stack, int array_size);
void	a_to_b(t_stack **a, t_stack **b, int array_size);


//pr
void    check_list(t_stack **a, t_stack **b);


void    under_cnt_three_a(t_stack **a_stack, t_stack **b_, int cnt);
int	check_sorted(t_node *tmp, int cnt, int stack);
#endif 