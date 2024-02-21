/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:35:17 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/04/05 20:57:28 by jaeyojun         ###   ########seoul.kr  */
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

char	*ft_substr(char *s, unsigned int start, size_t len)
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
	{
		//free(s);
		//s = NULL;
		return (NULL);
	}
	i = 0;
	while (s[start] != '\0' && i < len)
	{
		temp[i] = s[start];
		start++;
		i++;
	}
	temp[i] = '\0';
	//free(s);
	return (temp);
}


char	*ft_substrab(char *s, unsigned int start, size_t len)
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
	{
		//free(s);
		// s = NULL;
		return (NULL);
	}
	i = 0;
	while (s[start] != '\0' && i < len)
	{
		temp[i] = s[start];
		start++;
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*ft_strdup(char *string)
{
	char	*temp;
	int		i;
	int		count;

	i = 0;
	if (!string)
		return (0);
	count = ft_strlen(string);
	temp = (char *)malloc(sizeof(char) * (count + 1));
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

char	*ft_strjoin(char *s1, char *s2, int s2_len)
{
	int		count;
	char	*temp;
	int		i;

	i = 0;
	count = ft_strlen(s1);
	temp = (char *)malloc(sizeof(char) * (count + s2_len + 1));
	if (!temp)
	{
		free(s1);
		s1 = NULL;
		return (0);
	}
	while (i < count)
	{
		temp[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2_len)
	{
		temp[count + i] = s2[i];
		i++;
	}
	temp[count + i] = '\0';
	free(s1);
	s1 = NULL;
	return (temp);
}

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	int		count;
// 	char	*temp;

// 	count = ft_strlen(s1);
// 	count += ft_strlen(s2);
// 	temp = (char *)malloc(sizeof(char) * count + 1);
// 	if (!temp)
// 		return (0);
// 	while (*s1)
// 	{
// 		*temp = *s1;
// 		s1++;
// 		temp++;
// 	}
// 	while (*s2)
// 	{
// 		*temp = *s2;
// 		s2++;
// 		temp++;
// 	}
// 	*temp = '\0';
// 	return ((temp - count));
// }

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