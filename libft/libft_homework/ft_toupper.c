/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:15:06 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/03/18 19:19:27 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	char	change;

	change = (char)c;
	if (change >= 'A' && change <= 'Z')
		return (change + 32);
	return (change);
}

int main()
{
	char str1 = 'a';
	// char str2[15] = "abc";
	printf("%d\n", ft_toupper(str1));
	
	// char str3[10] = "abc";
	// char str4[15] = "abc";
	// printf("%d\n", strncmp(str3, str4, 3));
}