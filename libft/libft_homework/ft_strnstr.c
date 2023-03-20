/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:42:37 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/03/19 17:04:58 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *substr, size_t len)
{
	char	*temp;
	char	*s1;
	char	*s2;
	size_t	count;

	temp = (char *)str;
	if (!substr)
		return (temp);
	while (*temp && len != 0)
	{
		s1 = temp;
		s2 = (char *)substr;
		count = len;
		while (*s1 && *s2 && (*s1 - *s2 == 0) && count != 0)
		{
			s1++;
			s2++;
			count--;
		}
		if (!*s2)
			return (temp);
		temp++;
		len--;
	}
	return (0);
}

#include <stdio.h>

int main()
{

	char *haystack = "123456123";
	char * needle = "";

	printf("return = %s", ft_strnstr(haystack, needle, 20));
}
