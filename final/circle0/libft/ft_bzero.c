/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 20:22:00 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/03/17 20:59:11 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *dest, size_t len)
{
	unsigned char	*temp;
	size_t			i;
	unsigned int	zero;

	zero = 0;
	temp = (unsigned char *)dest;
	i = 0;
	while (i < len)
	{
		temp[i++] = (unsigned int)zero;
	}
}
