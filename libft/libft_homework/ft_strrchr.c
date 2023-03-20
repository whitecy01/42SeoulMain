/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:51:29 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/03/18 21:08:12 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
char	*ft_strrchr(const char *s, int c)
{
	char	*temp;
	int		count;

	temp = (char *)s;
	count = strlen(s);
	while (count != 0 && temp[count] != c)
		count--;
	if (temp[count] == c)
		return ((temp + count));
	return (0);
}


