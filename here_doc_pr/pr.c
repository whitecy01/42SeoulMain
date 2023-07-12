
#include "pr.h"


char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		count;
	char	*temp;

	count = count_str(s1);
	count += count_str(s2);
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

int	heredoc(t_info data)
{
	char	*buff;
	char	herefd;
	char	*endflag;

	buff = 0;
	herefd = open(".here_doc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	endflag = ft_strjoin("LIMITER", "\n");
	while (1)
	{
		write(1, "> ", 2);
		buff = get_next_line(0);
		if (ft_strncmp(buff, endflag, ft_strlen(endflag)) == 0)
		{
			free(buff);
			free(endflag);
			close(herefd);
			return (0);
		}
		write(herefd, buff, ft_strlen(buff));
		if (buff)
			free(buff);
		buff = 0;
	}
	return (0);
}


int main()
{
	t_info loc;
	int fd = heredoc(loc);
}