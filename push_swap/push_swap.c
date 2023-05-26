/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:19:08 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/05/26 21:25:26 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#include <stdio.h>






// void	print_error(int error)
// {
// 	if (error == -1)
// 		write(2, "Error\n", 6);
// 	exit(1);
// }

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
	if ('0' <= c && '9' >= c)
		return (0);
	return (1);
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

// char	*input_split_argv(char **argv, int array_size)
// {

// }

int	split_len(char **s, int start, int two_start)
{
	int i;
	int len;

	len = 0;
	while (s[start][two_start])
	{
		if (s[start][two_start] >= '0' && '9' >= s[start][two_start])
			len++;
	}
	return (len);
}

char	*ft_substr(char **s, unsigned int start, int two_start)
{
	size_t			i;
	char			*temp;
	size_t			cou;

	cou = ft_strlen(s);
	len = split_len(s, start);
	if (cou <= start)
		return (ft_strdup(""));
	if (len >= cou - start)
		len = cou - start;
	temp = (char *)malloc(sizeof(char) * (len + 1));
	if (!temp)
		return (0);
	i = 0;
	while (s[start][two_start] != '\0' && i < len)
	{
		temp[i] = s[start][two_start];
		start++;
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char	**input_split(char **argv, int array_size)
{
	char	**str;
	int 	i;
	int		j;

	j = 0;
	i = 0;
	str = (char **)malloc(array_size * sizeof(char *) + 1);
	while (i < array_size)
	{
		while (argv[i][j])
		{
			str[i] = ft_substr(argv, i, j);
			j += split_len(argv, i, j);
			if (!(argv[i][j]))
				break ;
			j++;
		}
		i++;
	}
	str[i] = 0;
	return (str);
}




char	**check_input_spilt(int argc, char **argv, int *array_size)
{
	char	**str;

	i = 1;
	while (i < argc)
	array_size += check_input_size(argv[i++]);
	// str = (char **)malloc(array_size * sizeof(char *) + 1);
	//2차원 자체를 만들고 넣어줘야함.
	str = input_split(argv, array_size);
}



int	main(int argc, char **argv)
{
	//int		array_size;
	//int		*array;
	char	**array_split;
	

	// if (argc < 2)
	// 	print_error(-1);

	//1. split으로 개수 세고 1차원 배열에 넣기 
	//입력값 처리, a에 넣어야하나?
	array_split = check_input_spilt(argc, argv, &array_size);
	
	// 2. atoi로 숫자 문자열이 잘 들어오는지 확인
	input_check(argc, argv);

	// printf("array : %d\n" , array_size);
	// for (int i = 0; i < argc; i++)
	// {
	// 	printf("%s\n", argv[i]);
	// }
	printf("argc : %d\n", argc);
}
