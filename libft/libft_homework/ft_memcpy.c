/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 20:30:21 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/03/17 21:17:31 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*temp;
	const char	*s;

	if (!n || dest == src)
		return (dest);
	if (dest == NULL && src == NULL)
		return (NULL);
	temp = dest;
	s = src;
	while (n--)
	{
		*temp++ = *s++;
	}
	return (dest);
}
