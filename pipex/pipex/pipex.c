/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:24:58 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/05 12:59:14 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include <stdio.h>

int	count_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
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



char	*combine_command(char *first_loc_command, char **path)
{
	char	*combine;
	int		i;
	char	*tmp;
	int		fd;

	combine = ft_strjoin("/", first_loc_command);
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], combine);
		fd = access(tmp, X_OK);
		if (fd != -1)
		{
			free(combine);
			return (tmp);
		}
		close(fd);
		free(tmp);
		i++;
	}
	free(combine);
	return (NULL);
}

void	pipe_start(t_info loc, char **envp)
{
	if (pipe(loc.pipe_fds) < 0)
		perror("pipe error");

	printf("loc.pipe_fds[0] -> %d, loc.pipe_fds[1] -> %d\n", loc.pipe_fds[0], loc.pipe_fds[1]);
	loc.pid = fork();
			printf("loc.com_path_combine : %s, loc.argv_command_one : %s\n" , loc.com_path_combine1, loc.argv_command_one[1]);
	// pid 값을 이용하여 에러와 자식 프로세스와 부모 프로세스를 분기한다
	if (loc.pid == -1)
		perror("fork error");
	else if (loc.pid == 0)
	{
		// 표준 입력을 infile로 바꾸고, 표준 출력을 pipe 로 바꾼 다음 명령어를 실행한다
		close(loc.pipe_fds[0]);
		dup2(loc.infile, STDIN_FILENO);
		dup2(loc.pipe_fds[1], STDOUT_FILENO);
		close(loc.pipe_fds[1]);
		close(loc.infile);

		execve(loc.com_path_combine1, loc.argv_command_one, envp);
	}
	else
	{
		// 표준 입력을 pipe로 바꾸고, 표준 출력을 outfile 로 바꾼다
		close(loc.pipe_fds[1]);
		dup2(loc.pipe_fds[0], STDIN_FILENO);
		dup2(loc.outfile, STDOUT_FILENO);
		close(loc.pipe_fds[0]);
		close(loc.outfile);
		// 자식 프로세스가 끝나기를 기다려서 pipe에 값을 받아온 다음 명령어를 실행한다
		waitpid(loc.pid, NULL, 0);
		execve(loc.com_path_combine2, loc.argv_command_two, envp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_info	loc;

    //infile open
	if (argc != 5)
		error("argument error");
	loc.infile = open(argv[1], O_RDONLY);
	if (loc.infile == -1)
		error("infile error");
	loc.outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (loc.outfile == -1)
		error("outfile error");

	printf("argc : %d\n", argc);
	loc.PATH = find_path(envp);
	//command split
	loc.argv_command_one = ft_split(argv[2], ' ');
	loc.argv_command_two = ft_split(argv[3], ' ');
	if (loc.argv_command_one  == NULL || loc.argv_command_two  == NULL)
		error("cmd missing error");
	// int i = 0;
	// while (loc.argv_command_one[i])
	// {
	// 	printf("loc.argv_command_one -> %s\n", loc.argv_command_one[i]);
	// 	i++;
	// }
	// i = 0;
	// while (loc.argv_command_two[i])
	// {
	// 	printf("loc.argv_command_two -> %s\n", loc.argv_command_two[i]);
	// 	i++;
	// }
	
	printf("loc.infile -> %d loc.outfile -> %d\n", loc.infile, loc.outfile);

	//acces를 하기 위해 인자들을 각 loc.argv_command_숫자[0]를 붙여주어야함.
	loc.com_path_combine1 = combine_command(loc.argv_command_one[0], loc.PATH);
	loc.com_path_combine2 = combine_command(loc.argv_command_two[0], loc.PATH);

	//printf("loc.com_path_combine1 : %s\n", loc.com_path_combine1);
	//printf("loc.com_path_combine2 : %s\n", loc.com_path_combine2);
	
	pipe_start(loc, envp);
	
	printf("loc.infile2 -> %d\n", loc.infile);
}
