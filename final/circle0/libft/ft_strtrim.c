/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 21:28:12 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/03/22 18:09:58 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *string);
size_t	ft_strlen(const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	fin;
	char	*temp;

	start = 0;
	if (s1 == NULL || set == NULL)
		return (0);
	fin = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (fin && s1[fin - 1] && ft_strchr(set, s1[fin - 1]))
		fin--;
	if (start > fin)
		return (ft_strdup(""));
	temp = ft_substr(s1, start, fin - start);
	return (temp);
}
