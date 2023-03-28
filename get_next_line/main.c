/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 19:45:17 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/03/26 20:00:37 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

char *get_next_line(int fd);
int ft_strlen(char *str);


int main()
{
	int fd;
	char *temp;

	fd = open("test.txt", O_RDONLY);
	temp = get_next_line(fd);
	printf("%s", temp);
	close(fd);
}