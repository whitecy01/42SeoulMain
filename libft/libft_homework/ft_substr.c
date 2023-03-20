/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 19:17:05 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/03/20 13:36:47 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*temp;

	i = 0;
	temp = (char *)malloc(sizeof(char) * len);
	if (!temp)
		return (0);
	while (s[start] && i < len)
	{
		temp[i] = s[start];
		start++;
		i++;
	}
	return (temp);
}
