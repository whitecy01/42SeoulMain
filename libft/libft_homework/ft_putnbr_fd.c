/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:27:42 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/03/20 17:34:59 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	s;

	s = 0;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 12);
		return ;
	}
	if (n < 0)
	{
		n *= -1;
		ft_putnbr_fd(n, fd);
	}
	if (n > 0)
	{
		n = n / 10;
		if (n == 0)
			return ;
		ft_putnbr_fd(n, fd);
		s = n % 10 + '0';
		write(fd, &s, 1);
	}
}

int main()
{
	ft_putnbr_fd(1234 ,1);
}
