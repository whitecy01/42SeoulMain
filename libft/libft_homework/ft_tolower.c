/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:35:01 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/03/18 18:45:50 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	char	change;

	change = (char)c;
	// if (change >= 'a' && change <= 'z')
	// 	return (change - 32);
	if (change >= 'a' && change <= 'z')
		return (change - 32);
	return (change);
}
int main()
{
	char str1 = 'a';
	// char str2[15] = "abc";
	printf("%d\n", ft_tolower(str1));
	
	// char str3[10] = "abc";
	// char str4[15] = "abc";
	// printf("%d\n", strncmp(str3, str4, 3));

}
