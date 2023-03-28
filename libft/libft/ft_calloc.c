/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 17:19:39 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/03/24 21:12:19 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*temp;
	size_t	t;

	t = size * count;
	if (count != 0 && size != 0 && t / count != size)
		return (0);
	temp = malloc(size * count);
	if (temp == 0)
		return (0);
	ft_memset(temp, 0, size * count);
	return (temp);
}
