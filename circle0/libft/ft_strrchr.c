/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:51:29 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/03/24 12:58:33 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s);

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	*temp;
	unsigned char	ca;
	int				count;

	temp = (unsigned char *)s;
	ca = (unsigned char)c;
	count = ft_strlen(s);
	while (count != 0 && temp[count] != ca)
		count--;
	if (temp[count] == ca)
		return ((char *)(temp + count));
	return (0);
}
