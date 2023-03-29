#include "get_next_line.h"

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
 


char	*ft_strdup(const char *string);
size_t	ft_strlen(const char *src);

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	char			*temp;
	size_t			cou;

	cou = ft_strlen(s);
	if (cou <= start)
		return (ft_strdup(""));
	if (len >= cou - start)
		len = cou - start;
	temp = (char *)malloc(sizeof(char) * (len + 1));
	if (!temp)
		return (0);
	i = 0;
	while (s[start] != '\0' && i < len)
	{
		temp[i] = s[start];
		start++;
		i++;
	}
	temp[i] = '\0';
	return (temp);
}



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

char *ft_read_line(int fd, char *buf, char *backup)
{
  int   count;
  char  *temp_pointer;

  count = 1;
  while (count)
  {
    count = read(fd, buf, BUFFER_SIZE);
    if (count == -1)
      return (0);
    else if (count == 0)
      break ;
    buf[count] = '\0';
    if (!backup)
      backup = ft_strdup("");
    temp_pointer = backup;
    backup = ft_strjoin(temp_pointer, buf);
    if (!backup)
      return (NULL);
    free(temp_pointer);
    temp_pointer = NULL;
    if (ft_strchr(buf, '\n'))
      break ;
  }
  return (backup);
}

static char *ft_extract(char *line)
{
  int   i;
  char  *result;

  i = 0;
  while (line[i] != '\n' && line[i] != '\0')
    i++;
  if (line[i] == '\0')
    return (0);
  result = ft_substr(line, i + 1, ft_strlen(line) - i);
  if (!result)
    return (NULL);
  if (result[0] == '\0')
  {
    free(result);
    result = NULL;
    return (NULL);
  }
  line[i + 1] = '\0';
  return (result);
}

char  *get_next_line(int fd)
{
  char    *line;
  char    *buf;
  static char *backup;

  if (fd < 0 || BUFFER_SIZE <= 0)
    return (NULL);
  buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
  if (!buf)
    return (NULL);
  line = ft_read_line(fd, buf, backup);
  free(buf);
  buf = NULL;
  if (!line)
    return (NULL);
  backup = ft_extract(line);
  //printf("%s ", backup);
  return (line);
}

#include <fcntl.h>
#include <stdio.h>

int main(void)
{
  int fd;

  fd = 0;
  fd = open("./test.txt", O_RDONLY);
  char *line;
	int a = 2;
  while (a--)
  {
	line  = get_next_line(fd);
	printf("%s", line);
  }

//   printf("%p\n", line);
//   printf("%s", line);

  return (0);
}