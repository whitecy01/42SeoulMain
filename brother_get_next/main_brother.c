#include "get_next_line.h"
#include <stdio.h>

static int	check_buff(char *buff)
{
	int	i;

	if (!buff)
		return (1);
	i = 0;
	while (buff[i] != '\0')
	{
		if (buff[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

static char	*make_buff(char *buff, int fd, int read_size)
{
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (NULL);
	tmp[BUFFER_SIZE] = '\0';
	while (check_buff(buff) == 1)
	{
		read_size = read(fd, tmp, BUFFER_SIZE);
		if (read_size == -1)
		{
			free_all(buff, tmp);
			return (NULL);
		}
		else if (read_size == 0)
			break ;
		buff = ft_strjoin(buff, tmp, read_size);
		if (!buff)
		{
			free_all(buff, tmp);
			return (NULL);
		}
	}
	free(tmp);
	return (buff);
}

// static char	*make_line(char *buff, int line_len)
// {
// 	char	*new_line;
// 	int		i;

// 	if (line_len == -1)
// 	{
// 		new_line = ft_strdup(buff);
// 		if (!new_line)
// 			return (NULL);
// 	}
// 	else
// 	{
// 		new_line = (char *)malloc(sizeof(char) * (line_len + 1));
// 		if (!new_line)
// 			return (NULL);
// 		i = 0;
// 		while (i < line_len)
// 		{
// 			new_line[i] = buff[i];
// 			i++;
// 		}
// 		new_line[i] = '\0';
// 	}
// 	return (new_line);
// }

// static char	*make_cache(char *buff, char *line, int line_len)
// {
// 	char	*new_cache;
// 	int		buff_len;
// 	int		i;
// 	int		j;

// 	buff_len = ft_strlen(buff);
// 	if (line_len == -1 || buff_len == line_len)
// 		return (NULL);
// 	new_cache = (char *)malloc(sizeof(char) * (buff_len - line_len + 1));
// 	if (!new_cache)
// 	{
// 		free(line);
// 		line = NULL;
// 		return (NULL);
// 	}
// 	i = 0;
// 	j = line_len;
// 	while (j < buff_len)
// 	{
// 		new_cache[i] = buff[j];
// 		i++;
// 		j++;
// 	}
// 	new_cache[i] = '\0';
// 	return (new_cache);
// }

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;
	char		*temp = NULL;
	//int			line_len;
	
	// 에러체크
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	// 백업을 먼저 검사
	// 있으면, 백업에 있는 문자열을 line에 복사
	// 없으면, 백업 줄게 없으니깐 널로 초기화
	if (backup)
	{
		line = ft_strdup(backup);
		if (!line)
			return (NULL);
		free(backup);
		backup = NULL;
	}
	else
		line = NULL;
	// line은 백업을 받아왔으니깐 make_buff 함수는 버퍼사이즈만큼 line 붙여주는 것
	// 백업 0123456\n7
	line = make_buff(line, fd, 0);
	if (!line)
		return (NULL);
	printf("%s" , line);
	// line_len = ft_linelen(line);
	// // line : 012345\n
	// // temp : 012345\n
	// // backup : 
	// temp = make_line(line, line_len);
	// backup = make_cache(line, temp, line_len);
	// free(line);
	 return (temp);
}

int main(void)
{
  int fd;

  fd = 0;
  fd = open("./test.txt", O_RDONLY);
  char *line;
  int a =1;
  while (a)
  {
	line  = get_next_line(fd);
	// if (line == 0)
	// 	break;
	//printf("%s", line);
	a--;
  }

	free(line);
	// while(1)
	// {

	// }
//   printf("%p\n", line);
//   printf("%s", line);

//   return (0);
}