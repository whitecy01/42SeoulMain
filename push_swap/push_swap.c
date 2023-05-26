/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:19:08 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/05/24 21:47:16 by jaeyojun         ###   ########seoul.kr  */
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


int ft_atoi_input_check(char *argv)
{
	int i;

	i = 0;
	while (argv[i] != '\0')
	{
		if ((argv[i] < '0' && argv[i] > '9') && argv[i] != 32)
			return (0);
		i++;
	}
	while(argv[i] >= '0' && argv[i] <= '9')
		i++;
	while (argv[i] != '\0')
	{
		if ((argv[i] < '0' && argv[i] > '9') && argv[i] != 32)
			return (0);
		i++;
	}
	return (1);
}

void 	*ft_atoi(int argc, char **argv)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (ft_atoi_input_check(argv + i) == 0)
			return (print_error(-1));
		i++;
	}
}

int check_input_separator(char c)
{
	if ('0' <= c && '9' >= c)
		return (0);
	return (1);
}

int check_input_size(char *argv)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while(argv[i])
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

char *i

char *check_input_spilt(int argc, char **argv, int *array_size)
{
	int i;
	int j;
	char	*str;
	
	i = 1;
	while (i < argc)
		array_size += check_input_size(argv[i++]);
	str = (char *)malloc(array_size * sizeof(char) + 1);
	i = 1;
	j = 0;
	while (i < array_size)
	{
		str[j] = input_split(argv[i]);
	}
	
}


int	main(int argc, char **argv)
{
	int		array_size;
	//int		*array;
	char	*array_split;
	if (argc < 2)
		print_error(-1);

	//1. atoi로 숫자 문자열이 잘 들어오는지 확인
	ft_atoi(argc, argv);
	//2. split으로 개수 세고 1차원 배열에 넣기 
	//입력값 처리, a에 넣어야하나?
	array_split = check_input_spilt(argc, argv, &array_size);
	printf("array : %d\n" , array_size);
	// for (int i = 0; i < argc; i++)
	// {
	// 	printf("%s\n", argv[i]);
	// }
	printf("argc : %d\n", argc);
}
