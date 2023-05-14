/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 17:11:55 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/05/14 16:32:05 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>

#include <stdio.h>
#include <stdarg.h>

void f(int n, ...)
{
	va_list v1;
	va_start(v1, n);


	printf("%d", va_arg(v1, int));
	va_end(v1);
}

int	main()
{
	//char 형
	char ch = 'c';
	
	f(1, ch);

}
// void f(int n, ...)
// {
// 	va_list v1;
// 	va_start(v1, n);

	
// 	printf("%s", va_arg(v1, char *));
// 	printf("%c", *(va_arg(v1, char *)));
// 	printf("%f", va_arg(v1, double));
// 	printf("%d", va_arg(v1, int));
// 	va_end(v1);
// }

// int	main()
// {
// 	//포인터
// 	char *p = "awd";
	
// 	//char 형(char로 뽑을 때)
// 	char aa = 'a';
// 	char *p1 = &aa;

// 	//char 형
// 	char ch = 'c';
	
// 	f(4, p, p1, 10.2, ch);

// }

	//int a;
	
	
	// for (int i = 0; i < n; i++)
	// {
	// 	a = va_arg(v1, int);
	// 	printf("%d", a);
	// }