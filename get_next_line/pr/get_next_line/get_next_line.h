/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 11:38:30 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/03/29 22:14:33 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# define BUFFER_SIZE 1

char	*ft_strdup(const char *string);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strcat(char *buff, char *prev);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_nonewline(char *line);
char	*ft_readline(int fd, char *buff, char *backup);
char	*ft_check_null(char *line);
char	*get_next_line(int fd);

#endif