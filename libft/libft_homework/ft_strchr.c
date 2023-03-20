/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:41:07 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/03/18 19:49:59 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	char *temp = (char *)s;
	while(temp)
	{
		if(*temp == c)
			return (temp);
		temp++;
	}
	return (0);
}
#include <stdio.h>

int main()
{
	char dest[] = "abcdefgabcd";
    char *first;
    // char *last;

	/* dest 문자열에서 첫번째 나오는 'b'문자를 찾습니다. */
	first = ft_strchr(dest, 'b');

	// /* dest 문자열에서 마지막 나오는 'b'문자를 찾습니다. */
	// last = strrchr(dest, 'b');
	
	 printf("first : %s \n", first);
	// printf("last : %s", last);
    
	return 0;
	
	}