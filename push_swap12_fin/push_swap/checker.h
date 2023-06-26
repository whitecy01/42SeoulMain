/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:31:25 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/25 21:38:34 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

long	atoi_while(char *str);
void	check_two_command(char *temp);
void	check_three_command(char *temp);
void	check_temp(char *temp);
void	check_command(char *temp, t_stack **a, t_stack **b);
void	command_rr(char *temp, t_stack **a, t_stack **b);
void	command_r(char *temp, t_stack **a, t_stack **b);
void	command_s(char *temp, t_stack **a, t_stack **b);
void	command_p(char *temp, t_stack **a, t_stack **b);
t_stack	*create_stack(int array_size, int flag);
t_node	*create_node(int array_answer);
void	node_pushback(t_node **pr, t_node *new);
void	stack_a_push_node(int *array, int array_size, t_stack **stack);
void	empty_string_number_check(char *argv);
void	overlap_check(int *temp, int array_size);
void	print_error(int error);
char	**ft_free(char **word);
int		ft_strlen_gnl(const char *s);
char	*ft_substr_gnl(char *s, unsigned int start, unsigned int len);
char	*ft_strdup(char *string);
char	*ft_strjoin(char *s1, char *s2, int s2_len, int count);
char	*ft_strchr(const char *s, int c);
char	*readline(int fd, char *line);
int		len_check(char *line);
char	*change_line(char **line, char **backup);
char	*get_next_line(int fd);
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
int		count_array(char *temp);
int		check_newline(char *temp);
int		sort_check_stack(t_stack **a);
void	checker_yes(t_stack **a, t_stack **b);
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
int		check_b(t_stack **b);

#endif 