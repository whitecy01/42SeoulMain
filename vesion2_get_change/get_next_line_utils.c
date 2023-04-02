/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:35:17 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/04/02 21:32:58 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	char			*temp;
	size_t			cou;

	cou = ft_strlen(s);
	if (cou <= start)
		return (ft_strdup(""));
	if (len >= cou - start)
		len = cou - start;
	temp = (char *)malloc(sizeof(char) * len + 1);
	if (!temp)
		return (0);
	i = 0;
	while (s[start] != '\0' && i < len)
	{
		//printf("%zu", i);
		temp[i] = s[start];
		start++;
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*ft_strdup(const char *string)
{
	char	*temp;
	int		i;
	int		count;

	i = 0;
	// if (!string)
	// 	return (0);
	count = ft_strlen(string);
	temp = (char *)malloc(sizeof(char) * count + 1);
	if (!temp)
		return (0);
	while (string[i])
	{
		temp[i] = string[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

int ft_strlen_new_line(const char *s2)
{
	int i;
	int count;
	
	count = 0;
	i = 0;
	while (s2[i] != '\0')
	{
		if (s2[i] == '\n')
			count++;
		i++;
	}
	return (count);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		count;
	char	*temp;
	// int		count_new_line;

	// count_new_line = ft_strlen_new_line(s2);
	// if (count_new_line >= 2)
	// {
	// 	temp = (char *)malloc(sizeof(char) * 2);
	// 	temp[1] = '\0';
	// 	return (temp);
	// }
	// if (s2[0] == '\n')
	// {
	// 	temp = (char *)malloc(sizeof(char) * 2);
	// 	temp[0] = s2[0];
	// 	temp[1] = '\0';
	// 	return (temp);
	// }
	count = ft_strlen(s1);
	count += ft_strlen(s2);
	temp = (char *)malloc(sizeof(char) * count + 1);
	if (!temp)
		return (0);
	while (*s1)
	{
		*temp = *s1;
		s1++;
		temp++;
	}
	while (*s2)
	{
		*temp = *s2;
		s2++;
		temp++;
	}
	*temp = '\0';
	return ((temp - count));
}

char	*ft_strchr(const char *s, int c)
{
	char			*temp;
	int				count;
	unsigned char	ca;

	temp = (char *)s;
	ca = (unsigned char)c;
	if (ca == '\0')
	{
		count = ft_strlen(s);
		return (temp + count);
	}
	while (*temp)
	{
		if (*temp == ca)
			return (temp);
		temp++;
	}
	return (0);
}
