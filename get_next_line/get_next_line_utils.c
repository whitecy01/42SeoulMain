
#include "get_next_line.h"

size_t	ft_strlen(const char *s);

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