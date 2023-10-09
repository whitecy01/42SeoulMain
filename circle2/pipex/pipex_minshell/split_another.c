/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_another.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:01:50 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/07 15:18:11 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	string_check_two(char s, char c)
{
	if (s == c)
		return (1);
	return (0);
}

int	quote_check(char s)
{
	if (s == '\'')
		return (0);
	return (1);
}

int	another_malloc_count(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] && (string_check_two(s[i], c) == 1))
			i++;
		if (s[i])
		{
			count++;
			if (s[i] == '\'')
			{
				i++;
				while (quote_check(s[i]) == 1)
					i++;
			}
			else
				i++;
		}
		while (s[i] && (string_check_two(s[i], c) == 0))
			i++;
	}	
	return (count);
}

char	*one_char_input(int count, char const *s, char c)
{
	char	*temp;
	int		tmp;
	int		i;
	int		x;

	temp = (char *)malloc(sizeof(char) * count + 1);
	if (!temp)
		return (0);
	tmp = 0;
	if (s[0] == '\'')
		tmp = 1;
	i = 0;
	x = 0;
	if (tmp == 1)
	{
		i++;
		while ((s[i] != '\0' && quote_check(s[i]) == 1))
		{
			temp[x] = s[i];
			i++;
			x++;
		}
	}
	else
	{
		while ((s[i] != '\0' && string_check_two(s[i], c) == 0))
		{
			temp[i] = s[i];
			i++;
		}
	}
	temp[count] = '\0';
	return (temp);
}

int	one_char_count(char const *s, char c)
{
	int	i;
	int	temp;
	int	count;

	temp = 0;
	i = 0;
	if (s[0] == '\'')
	{
		temp = 1;
	}
	count = 0;
	i = 0;
	if (temp == 1)
	{
		i++;
		while ((s[i] != '\0' && quote_check(s[i]) == 1))
		{
			i++;
			count++;
		}
		return (count);
	}
	while ((s[i] != '\0' && string_check_two(s[i], c) == 0))
	{
		i++;
		count++;
	}
	return (count);
}

char	*word_input_two(char const *s, char c)
{
	int		i;
	char	*temp;
	int		count;

	count = 0;
	i = 0;
	count = one_char_count(s, c);
	temp = one_char_input(count, s, c);
	return (temp);
}

char	**another_split(char *s, char c)
{
	char	**temp;
	int		count;
	int		size;

	count = 0;
	size = another_malloc_count(s, c);
	temp = (char **)malloc(sizeof(char *) * (size + 1));
	if (!temp)
		return (0);
	while (*s)
	{
		while (*s && string_check_two(*s, c) == 1)
			s++;
		if (*s)
		{
			temp[count++] = word_input_two(s, c);
			if (temp[count - 1] == 0)
				return (ft_free(temp));
			if (*s == '\'')
			{
				s++;
				while (quote_check(*s) == 1)
					s++;
			}
			else
				s++;
		}
		while (*s && (string_check_two(*s, c) == 0))
			s++;
	}
	temp[count] = 0;
	return (temp);
}
