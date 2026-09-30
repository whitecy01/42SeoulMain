/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:21:35 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/03/22 18:04:43 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlens(const char *src);

size_t	ft_strlens(const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;
	size_t	dest2_len;
	size_t	src2_len;

	i = 0;
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	dest2_len = dest_len;
	src2_len = src_len;
	while (dest2_len + i + 1 < size && src[i] != '\0')
	{
		dest[dest_len] = src[i];
		i++;
		dest_len++;
	}
	dest[dest_len] = '\0';
	if (dest2_len < size)
		return (dest2_len + src2_len);
	else if (dest_len >= size)
		return (src2_len + size);
	return (0);
}
