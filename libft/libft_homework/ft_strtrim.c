/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 21:28:12 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/03/20 10:44:52 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	first_word(char const *s1, char const *set)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		while (set[j] != '\0')
		{
			if (s1[i] == set[j])
			{
				break ;
			}
			j++;
		}
		if (set[j] == '\0')
			return (i);
		i++;
	}
	return (0);
}

int	second_word(char const *s1, char const *set)
{
	int	i;
	int	j;

	j = 0;
	i = strlen(s1) - 1;
	while (s1[i] != '\0')
	{
		j = 0;
		while (set[j] != '\0')
		{
			if (s1[i] == set[j])
			{
				break ;
			}
			j++;
		}
		if (set[j] == '\0')
			return (i);
		i--;
	}
	return (0);
}

int	change(int sum)
{
	if (sum < 0)
	{
		return (-sum);
	}
	return (sum);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		first;
	int		second;
	int		sum;
	char	*temp;
	int		i;

	i = 0;
	first = first_word(s1, set);
	second = second_word(s1, set);
	sum = change(first - second);
	temp = (char *)malloc(sizeof(char) * sum + 1);
	while (sum + 1)
	{
		temp[i] = s1[first];
		i++;
		first++;
		sum--;
	}
	temp[i] = '\0';
	return (temp);
}
