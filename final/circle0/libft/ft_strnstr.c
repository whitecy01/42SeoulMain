/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:42:37 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/03/23 19:52:19 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *substr, size_t len)
{
	char	*s1;
	char	*s2;
	size_t	count;

	if (*substr == 0 && *str == 0)
		return ((char *)str);
	if (*substr == 0)
		return ((char *)str);
	while (*str && len != 0)
	{
		s1 = (char *)str;
		s2 = (char *)substr;
		count = len;
		while (*s1 && *s2 && (*s1 - *s2 == 0) && count != 0)
		{
			s1++;
			s2++;
			count--;
		}
		if (!*s2)
			return ((char *)str);
		str++;
		len--;
	}
	return (0);
}
