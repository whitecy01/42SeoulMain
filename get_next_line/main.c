/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 19:45:17 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/03/29 14:44:39 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

char *get_next_line(int fd);
int ft_strlen(char *str);
char	*ft_strcat(char *buff, char *prev);
char	*ft_strchr(const char *s, int c);

int main()
{
	int fd;
	char *temp;

	fd = open("test.txt", O_RDONLY);
	int a = 2;
	while(a)
	{
		temp = get_next_line(fd);
		printf("%s\n", temp);
		a--;
	}
	//printf("%s", temp);
	close(fd);
}