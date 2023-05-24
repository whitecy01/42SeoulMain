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

int	check_input_size(int argc, char **argv)
{
	int	i;
	int	j;
	int	count;
	int	check;

	count = 0;
	i = 0;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if ('0' <= argv[i][j] && argv[i][j] <= '9')
			{
				check = j;
				check++;
				count++;
				printf("i : %d check : %d\n", i, check);
				while ('0' <= check && check <= '9')
				{
					if ('0' > check && check > '9')
					{
						j = check;
						break ;
					}
					check++;
					printf("check : %d", check);
				}
			}
			j++;
		}
		i++;
	}
	return (count);
}


int	main(int argc, char **argv)
{
	int		array_size;
	//char	*sp;
	if (argc < 2)
		print_error(-1);
	//입력값 처리, a에 넣어야하나?
	array_size = check_input_size(argc, argv);
	printf("array : %d\n" , array_size);
	// for (int i = 0; i < argc; i++)
	// {
	// 	printf("%s\n", argv[i]);
	// }
	printf("argc : %d", argc);
}
