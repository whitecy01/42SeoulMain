/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:19:08 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/03 03:52:03 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

void print_error(int error)
{
	if (error == -1)
		write(2, "Error\n", 6);
	exit(1);
}

int check_input_separator(char c)
{
	if (c == 32)
		return (1);
	return (0);
}

int check_input_size(char *argv)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (argv[i])
	{
		while (argv[i] && (check_input_separator(argv[i]) == 1))
			i++;
		if (argv[i] && (check_input_separator(argv[i]) == 0))
		{
			i++;
			count++;
		}
		while (argv[i] && (check_input_separator(argv[i]) == 0))
			i++;
	}
	return (count);
}

int string_check(char s)
{
	if (s == 32)
		return (1);
	return (0);
}

int ft_strlen(const char *s, int start)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[start] != '\0' && s[start] != 32)
	{
		if (s[start] == 32)
			break;
		start++;
		i++;
	}
	return (i);
}

char *ft_substr(char *s, int *start)
{
	int i;
	char *temp;

	temp = (char *)malloc((sizeof(char) * ft_strlen(s, *start)) + 1);
	if (!temp)
		return (NULL);
	i = 0;
	while (s[*start] != '\0' && s[*start] != 32)
	{
		temp[i] = s[*start];
		(*start)++;
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char **input_split_argv(char **str, char *argv, int *two_malloc_count)
{
	int i;

	i = 0;
	while (argv[i])
	{
		while (argv[i] && string_check(argv[i]) == 1)
		{
			i++;
		}
		while (argv[i] && string_check(argv[i]) == 0)
		{
			str[*two_malloc_count] = ft_substr(argv, &i);
			(*two_malloc_count)++;
		}
	}
	return (str);
}

char **input_split(char **argv, int argc, int array_size)
{
	char **str;
	int i;
	int j;

	j = 0;
	i = 1;
	str = (char **)malloc(array_size * sizeof(char *) + 1);
	printf("array_size : %d\n", array_size);
	while (i < argc)
	{
		str = input_split_argv(str, *(argv + i), &j);
		i++;
	}
	str[array_size] = 0;
	return (str);
}

char **check_input_spilt(int argc, char **argv, int *array_size)
{
	char **str;
	int i;

	i = 1;
	while (i < argc)
		*array_size += check_input_size(argv[i++]);
	// 2차원 자체를 만들고 넣어줘야함.
	str = input_split(argv, argc, *array_size);
	return (str);
}

int ft_atoi(char *str)
{
	int i;
	int result;
	int min;

	i = 0;
	min = 1;
	if (str[i] == 32)
		print_error(-1);
	if (str[i] == '-')
	{
		min = -1;
		i++;
	}
	result = 0;
	while (str[i])
	{
		if ('0' <= str[i] && str[i] <= '9')
			result = (10 * result) + str[i] - '0';
		else
			print_error(-1);
		i++;
	}
	return (result * min);
}

int *change_int(char **array_split, int *array_size)
{
	int *temp;
	int i;

	temp = (int *)malloc(sizeof(int) * (*array_size));
	i = 0;
	while (i < *array_size)
	{
		temp[i] = ft_atoi(array_split[i]);
		i++;
	}
	i = 0;
	*array_size = 0;
	while (temp[i])
	{
		(*array_size)++;
		i++;
	}
	return (temp);
}

int main(int argc, char **argv)
{
	int		array_size;
	char	**array_split;
	int		*array;
	t_stack	*a;
	t_stack	*b;

	if (argc < 2)
		print_error(-1);
	array_size = 0;
	// 1. 2차원을 말록한 후에 거기에다가 값을 넣기
	array_split = check_input_spilt(argc, argv, &array_size);
	if (array_size == 0)
		print_error(-1);
	// 2. char 2차원 배열을 1차원 배열에 넣어주기
	array = change_int(array_split, &array_size);
	printf("int_array_size : %d\n", array_size);
	// 3. a,b 스택 만들기
	a = create_stack(array_size, 'a');
	b = create_stack(array_size, 'b');
	stack_a_create_node(array, array_size, &a);
	printf("a->size : %d\n", a->size);
	// 4. int array를 a스택에 넣기

	// t_stack *pr;
	
	// pr = a->top;
	//int i = 0;
	printf("a_top :  %d  \n", a->top->content);
	// printf("a_top :  %d  \n", a->top->next->content);
	printf("a_bottom :  %d  \n", a->bottom->content);
	printf("a_bottom :  %d  \n", a->bottom->prev->content);
	// while (a->top)
	// {
	// 	printf("pr->content : %d\n", a->top->content);
	// 	a->top = a->top->next;
	// }
	
	// s_number = NULL;
	// s_number = new_s_number(array_split, array_size);
	// 1. 2차원을 말록한 후에 a 스택에 넣기

	// 2. atoi로 숫자 문자열이 잘 들어오는지 확인
	printf("-------------------\n");
	printf("argc : %d\n", argc);
}
