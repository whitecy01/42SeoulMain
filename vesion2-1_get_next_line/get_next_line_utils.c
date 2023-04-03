/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:35:17 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/04/03 21:19:12 by jaeyojun         ###   ########seoul.kr  */
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
	if (!s2)
		return (0);
	while (s2[i] != '\0')
	{
		if (s2[i] == '\n')
			count++;
		i++;
	}
	return (count);
}

char	*ft_strjoin(char *buff, char *tmp, int tmp_len)
{
	char	*join_buff;
	int		buff_len;
	int		i;

	buff_len = ft_strlen(buff);
	join_buff = (char *)malloc(sizeof(char) * (buff_len + tmp_len + 1));
	if (!join_buff)
		return (NULL);
	i = 0;
	printf("%s" , buff);
	while (i < buff_len)
	{
		join_buff[i] = buff[i];
		i++;
	}	
	i = 0;
	while (i < tmp_len)
	{
		join_buff[buff_len + i] = tmp[i];
		i++;
	}
	join_buff[buff_len + i] = '\0';
	free(buff);
	return (join_buff);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		count;
	char	*temp;
	int		i;
	int 	j;

	i = 0;
	count = ft_strlen(s1);
	count += ft_strlen(s2);
	temp = (char *)malloc(sizeof(char) * count + 1);
	if (!temp)
		return (0);
	while (s1[i] != '\0')
	{
		temp[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		temp[i] = s2[j];
		i++;
		j++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		count;
	char	*temp;

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
