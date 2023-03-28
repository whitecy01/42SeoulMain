
#include "get_next_line_pr.h"

char *get_next_line(int fd);
size_t	ft_strlen(const char *s);


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


char *get_next_line(int fd)
{
	char *buff;
	int reada;
	char *backup;
	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);

	while((reada = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[reada] = '\0';
		if (backup == NULL)
			backup = ft_strdup("");
		backup = ft_strjoin(backup, buff);
	}
	free(buff);
	return (backup);
}
