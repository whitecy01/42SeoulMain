/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:19:08 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/05/28 21:49:50 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#include <stdio.h>






void	print_error(int error)
{
	if (error == -1)
		write(2, "Error\n", 6);
	exit(1);
}

// int	input_check_string(char *argv)
// {
// 	int	i;

// 	i = 0;
// 	//printf("argv : %s\n", argv);
// 	//공백 체크 하면서 그 부분에 이상한 문자 있는지 검사 
// 	while (argv[i] == 32)
// 	{
// 		printf("debug argv[%c]\n", argv[i]);
// 		if ((argv[i] < '0' && argv[i] > '9'))
// 		{
// 			return (0);
// 		}
// 		i++;
// 	}
// 	if ((argv[i] < '0' && argv[i] > '9'))
// 	{
// 			return (0);
// 	}
// 	while (argv[i] >= '0' && argv[i] <= '9')
// 	{
// 		if ((argv[i] < '0' && argv[i] > '9'))
// 		{
// 			return (0);
// 		}
// 		i++;
// 	}
// 	while (argv[i] == 32)
// 	{
// 		if ((argv[i] < '0' && argv[i] > '9'))
// 			return (0);
// 		i++;
// 	}
// 	printf("---------\n");
// 	return (1);
// }

// void	input_check(int argc, char **argv)
// {
// 	int	i;

// 	i = 1;
// 	while (i < argc)
// 	{
// 		if (input_check_string(*(argv + i)) == 0)
// 			return (print_error(-1));
// 		i++;
// 	}
// }

// int	check_input_size(int argc, char **argv)
// {
// 	int	i;
// 	int	j;
// 	int	count;
// 	int	check;

// 	count = 0;
// 	i = 0;
// 	while (i < argc)
// 	{
// 		j = 0;
// 		while (argv[i][j] != '\0')
// 		{
// 			if ('0' <= argv[i][j] && argv[i][j] <= '9')
// 			{
// 				check = j;
// 				check++;
// 				count++;
// 				printf("i : %d check : %d\n", i, check);
// 				while ('0' <= check && check <= '9')
// 				{
// 					if ('0' > check && check > '9')
// 					{
// 						j = check;
// 						break ;
// 					}
// 					check++;
// 					printf("check : %d", check);
// 				}
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (count);
// }


int	check_input_separator(char c)
{
	//if ('0' <= c && '9' >= c)
	if (c == 32)
		return (1);
	return (0);
}


int	check_input_size(char *argv)
{
	int	i;
	int	count;

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

int	string_check(char s)
{
	if (s == 32)
		return (1);
	return (0);
}

int	ft_strlen(const char *s, int start)
{
	int i;
	
	i = 0;
	if (!s)
		return (0);
	while (s[start] != '\0' && s[start] != 32)
	{
		if (s[start] == 32)
			break ;
		start++;
		i++;
	}
	return (i);
}


char	*ft_substr(char *s, int *start)
{
	int	i;
	char			*temp;

	//printf("start %d\n ", *start);
	// if (cou <= start)
	// 	return (ft_strdup(""));
	// if (len >= cou - start)
	// 	len = cou - start;
	//printf("start : %d , s :%s\n", *start, s);
	temp = (char *)malloc((sizeof(char) * ft_strlen(s, *start)) + 1);
	//printf("len : %d, start : %d\n", ft_strlen(s, *start), *start);
	if (!temp)
		return (NULL);
	i = 0;
	while (s[*start] != '\0' && s[*start] != 32)
	{
		temp[i] = s[*start];
		//printf("tmp : %c\n", temp[i]);
		(*start)++;
		i++;
	}
	//printf("start : %d , s :%s\n", *start, s);
	// while (i < *start)
	// {
	// 	temp[i] = s[*start];
	// 	(*start)++;
	// 	i++;
	// }
	temp[i] = '\0';
	//printf("tmp_full: %s\n", temp);
	return (temp);
}

// char	**input_split_argv(char **str, char *argv, int *two_malloc_count)
// {
// 	int i;

// 	i = 0;
// 	 //*str[i] = "awd";
// 	// printf("str %s\n", *str[i]);
// 	// printf("argv %s\n", argv);
// 	//  printf("two_malloc_count : %d\n", *two_malloc_count);
// 	while (argv[i])
// 	{
// 		while (argv[i] && string_check(argv[i]) == 1)
// 		{
// 			printf("i1 : %d\n", i);
// 			i++;
// 		}
// 		while (argv[i] && string_check(argv[i]) == 0)
// 		{
// 			printf("i : %d\n", i);
// 			printf("two_malloc_count : %d\n", *two_malloc_count);
// 			(*str)[*two_malloc_count] = ft_substr(argv, &i);
// 			//printf("str[%d] : %s\n", *two_malloc_count, *str[*two_malloc_count]);
// 			printf("str : %s\n", *str[*two_malloc_count]);
// 			(*two_malloc_count)++;
			
// 		}
// 	}
// 	return (str);
// }

char	**input_split_argv(char **str, char *argv, int *two_malloc_count)
{
	int i;

	i = 0;
	 //*str[i] = "awd";
	// printf("str %s\n", *str[i]);
	 //printf("ㄱ기모지 argv %s\n", argv);
	//  printf("two_malloc_count : %d\n", *two_malloc_count);
	while (argv[i])
	{
		while (argv[i] && string_check(argv[i]) == 1)
		{
			//printf("i1 : %d\n", i);
			i++;
		}
		while (argv[i] && string_check(argv[i]) == 0)
		{
			//printf("i : %d\n", i);
			//printf("two_malloc_count : %d\n", *two_malloc_count);
			str[*two_malloc_count] = ft_substr(argv, &i);
			//printf("str[%d] : %s\n", *two_malloc_count, *str[*two_malloc_count]);
			//printf("str : %s\n", str[*two_malloc_count]);
			(*two_malloc_count)++;
			
		}
	}
	return (str);
}

char	**input_split(char **argv, int argc, int array_size)
{
	char	**str;
	int 	i;
	int		j;

	j = 0;
	i = 1;
	str = (char **)malloc(array_size * sizeof(char *) + 1);
	// printf("%s", argv[i]);
	printf("array_size : %d\n", array_size);
	while (i < argc)
	{
		// if (!(*(argv + i)))
		// 	break ;
		//printf("i_increasing: %d\n", i);
		//input_split_argv(&str, *(argv + i), &j);
		str = input_split_argv(str, *(argv + i), &j);
		i++;
	}
	str[array_size] = 0;
	
	i= 0;
	while (i < array_size)
	{
		//printf("str: %s\n", str[i]);
		i++;
	}
	return (str);
}

char	**check_input_spilt(int argc, char **argv, int *array_size)
{
	char	**str;
	int		i;

	i = 1;
	while (i < argc)
		*array_size += check_input_size(argv[i++]);
	//2차원 자체를 만들고 넣어줘야함.
	str = input_split(argv, argc, *array_size);
	return (str);
}

int	main(int argc, char **argv)
{
	int		array_size;
	//int		*array;
	char	**array_split;

	if (argc < 2)
		print_error(-1);
	array_size = 0;
	//1. 2차원을 말록한 후에 거기에다가 값을 넣기
	array_split = check_input_spilt(argc, argv, &array_size);
	int i = 0;
	while (i < array_size)
	{
		printf("array_split: %s\n", array_split[i]);
		i++;
	}

	// 2. atoi로 숫자 문자열이 잘 들어오는지 확인
	printf("-------------------\n");
	printf("argc : %d\n", argc);
}
