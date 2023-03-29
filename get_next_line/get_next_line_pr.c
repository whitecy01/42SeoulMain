
#include "get_next_line.h"

char *get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strcat(char *buff, char *prev);

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

// char	*ft_strcat(char *buff, char *prev)
// {
// 	char	*rst;
// 	int		len;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = i;
// 	len = ft_strlen(buff) + ft_strlen(prev);
// 	rst = (char *)malloc(sizeof(char) * (len + 1));
// 	while (prev[j])
// 		rst[i++] = prev[j++];
// 	j = 0;
// 	while (buff[j])
// 		rst[i++] = buff[j++];
// 	free(prev);
// 	rst[i] = 0;
// 	return (rst);
// }

// char	*get_next_line(int fd)
// {
// 	char	*buff;
// 	char	*prev;
// 	int		rd_size;

// 	if (fd < 0)
// 		return (0);
// 	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
// 	prev = (char *)malloc(sizeof(char) * 1);
// 	prev[0] = 0;
// 	rd_size = 1;
// 	while (0 < rd_size)
// 	{
// 		rd_size = read(fd, buff, BUFFER_SIZE);
// 		buff[rd_size] = '\0';
// 		prev = ft_strcat(buff, prev);
// 	}
// 	free(buff);
// 	return (prev);
// }

size_t	ft_strlen(const char *s);

char	*ft_strdup(const char *string)
{
	char	*temp;
	int		i;
	int		count;

	i = 0;
	count = ft_strlen(string);
	temp = (char *)malloc(count * sizeof(char) + 1);
	if (!temp)
		return (0);
	while (string[i])
	{
		temp[i] = string[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
 
size_t	ft_strlen(const char *s);

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		count;
	char	*temp;

	count = ft_strlen(s1);
	count += ft_strlen(s2);
	temp = (char *)malloc(sizeof(char) * count + 1);
	if (!temp)
		return (0);
	while (*s1)
	{
		*temp = *s1;
		s1++;
		temp++;
	}
	while (*s2)
	{
		*temp = *s2;
		s2++;
		temp++;
	}
	*temp = '\0';
	return ((temp - count));
}


char	*ft_strcat(char *buff, char *prev)
{
	char	*rst;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = i;
	len = ft_strlen(buff) + ft_strlen(prev);
	rst = (char *)malloc(sizeof(char) * (len + 1));
	while (prev[j])
		rst[i++] = prev[j++];
	j = 0;
	while (buff[j])
		rst[i++] = buff[j++];
	free(prev);
	rst[i] = 0;
	return (rst);
}


char	*ft_strchr(const char *s, int c)
{
	char			*temp;
	int				count;
	unsigned char	ca;

	temp = (char *)s;
	ca = (unsigned char)c;
	if (ca == '\0')
	{
		count = ft_strlen(s);
		return (temp + count);
	}
	while (*temp)
	{
		if (*temp == ca)
			return (temp);
		temp++;
	}
	return (0);
}



static char	*ft_line_check(char *line)
{
	int i;
	char *backup;

	i = 0;
	backup = ft_strdup("");
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	i++;
	int line_count = ft_strlen(line);
	int line_count_second = ft_strlen(line + i);
	int count = line_count - line_count_second;
	int j = 0;
	while (line[i] != '\0' && count)
	{
		backup[j] = line[i]; 
		count--;
		j++;
		i++;
	}
	backup[j] = '\0';
	return (backup);

}

char *ft_nonewline(char *line)
{
	char *newline;

	int i = 0;
	newline = NULL;
	if (!newline)
		newline = ft_strdup("");
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
		{
			newline[i] = line[i];
			break;
		}
		newline[i] = line[i];
		i++; 
	}
	newline[i] = '\0';
	return (newline);
}

char	*get_next_line(int fd)
{
	char		*buff;
	int			reada;
	static char	*backup;
	char		*line;

	reada = 1;
	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (0);
	line = NULL;
	if (!line)
		line = ft_strdup("");
	while (reada > 0)
	{
		reada = read(fd, buff, BUFFER_SIZE);
		if (reada <= -1)
			return (0);
		if (reada == 0)
			break ;
		buff[reada] = '\0';
		line = ft_strjoin(line, buff);
		//printf("line : %s", line);
		free (buff);
		buff = NULL;
		if (!line)
			return (0);
		if (ft_strchr(line, '\n'))
		{
			break ;
		}
	}

	backup = ft_line_check(line);
	line = ft_nonewline(line);
	//printf("line : %s\n", line);
	//printf("backup : %s", backup);
	return (line);
}
