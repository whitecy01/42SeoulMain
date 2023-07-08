/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:24:58 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/08 22:00:17 by jaeyojun         ###   ########seoul.kr  */
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

	fd = access(first_loc_command, X_OK);
	if (fd != -1)
		return (first_loc_command);
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

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	exit(127);
}


// void	pipe_start(t_info loc, char **envp, char **argv, int argc)
// {
// 	int i = 2;
// 	int fork_count = argc - 5;
// 	int start = 0;

// 	if (pipe(loc.pipe_fds) < 0)
// 		perror("pipe error");
// 	//loc.pid = fork();
// 	printf("argv : %s\n", argv[1]);
// 	printf("envp : %s\n", envp[1]);
// 	printf("fork_count : %d\n", fork_count);
// 	//if (loc.pid == -1)
// 	//	perror("fork error");
// 	// while (start < fork_count - 1)
// 	// {
// 		//if (loc.pid != 0)
// 		loc.pid = fork();
// 		if (loc.pid == -1)
// 			perror("fork error");
// 		if (loc.pid == 0)
// 		{
// 			while (fork_count--)
// 				loc.pid = fork();
// 			if (start == 0)
// 			{
// 				printf("자식 프로세스 %d에서 자식 프로세스 %d로 파일 목록 전송\n", getpid(), loc.pid);
// 				close(loc.pipe_fds[0]);
// 				dup2(loc.infile, STDIN_FILENO);
// 				dup2(loc.pipe_fds[1], STDOUT_FILENO);
// 				close(loc.pipe_fds[1]);
// 				close(loc.infile);
// 			}
// 			else
// 			{
// 				// ft_free(loc.argv_command_one);
// 				// ft_free_one(loc.com_path_combine1);
// 				close(loc.pipe_fds[1]);
// 				dup2(loc.pipe_fds[0], STDIN_FILENO);
// 				dup2(loc.pipe_fds[1], STDOUT_FILENO);
// 				close(loc.pipe_fds[0]);
// 				close(loc.pipe_fds[1]);
// 			}
// 			loc.argv_command_one = ft_split(argv[i++], ' ');
// 			loc.com_path_combine1 = combine_command(loc.argv_command_one[0], loc.PATH);
// 			if (execve(loc.com_path_combine1, loc.argv_command_one, envp) == -1)
// 				ft_putstr_fd("bash : command not found\n", 2);
// 		}
// 		// else if (start > 0 && loc.pid == 0)
// 		// {
// 		// 	// ft_free(loc.argv_command_one);
// 		// 	// ft_free_one(loc.com_path_combine1);
// 		// 	// close(loc.pipe_fds[1]);
// 		// 	// dup2(loc.pipe_fds[0], STDIN_FILENO);
// 		// 	// dup2(loc.pipe_fds[1], STDOUT_FILENO);
// 		// 	// // dup2(loc.outfile, STDOUT_FILENO);
// 		// 	// close(loc.pipe_fds[0]);
// 		// 	// close(loc.pipe_fds[1]);
// 		// 	// loc.argv_command_one = ft_split(argv[i++], ' ');
// 		// 	// loc.com_path_combine1 = combine_command(loc.argv_command_one[0], loc.PATH);
// 		// 	// if (execve(loc.com_path_combine1, loc.argv_command_one, envp) == -1)
// 		// 	// 	ft_putstr_fd("bash : command not found\n", 2);
// 		// }
// 		else
// 		{
// 			// waitpid(loc.pid, NULL, WNOHANG);
// 			 printf("부모 프로세스 %d에서 자식 프로세스 %d로 파일 목록 전송\n", getpid(), loc.pid);
// 			// close(loc.pipe_fds[1]);
// 			// dup2(loc.pipe_fds[0], STDIN_FILENO);
// 			// dup2(loc.outfile, STDOUT_FILENO);
// 			// close(loc.pipe_fds[0]);
// 			// close(loc.outfile);
			
// 			waitpid(loc.pid, NULL, 0);
			
// 			// loc.argv_command_two = ft_split(argv[argc - 2], ' ');
// 			// loc.com_path_combine2 = combine_command(loc.argv_command_two[0], loc.PATH);
// 			// if (execve(loc.com_path_combine2, loc.argv_command_two, envp) == -1)
// 			// 	ft_putstr_fd("bash : command not found\n", 2);
// 		}
// 	// 	start++;
// 	// }
// }



void	pipe_start(t_info loc, char **envp, char **argv, int argc)
{
	int i = 2;
	int fork_count = argc - 3;
	int start = -1;

	//loc.pid = fork();
	printf("argv : %s\n", argv[1]);
	printf("envp : %s\n", envp[1]);
	printf("fork_count : %d\n", fork_count);
	while (++start < fork_count - 1)
	{
		printf("start : %d\n", start);
		if (pipe(loc.pipe_fds) < 0)
			perror("pipe error");
		loc.pid = fork();
		if (loc.pid == -1)
			perror("fork error");
		else if (loc.pid == 0)
		{
			//printf("자식 프로세스 %d에서 자식 프로세스 %d로 파일 목록 전송\n", getpid(), loc.pid);
			if (start == 0)
			{
				//printf("자식 프로세스 %d에서 자식 프로세스 %d로 파일 목록 전송 first\n", getpid(), loc.pid);
				close(loc.pipe_fds[0]);
				dup2(loc.infile, STDIN_FILENO);
				dup2(loc.pipe_fds[1], STDOUT_FILENO);
				close(loc.pipe_fds[1]);
				close(loc.infile);
				loc.argv_command_one = ft_split(argv[i++], ' ');
				loc.com_path_combine1 = combine_command(loc.argv_command_one[0], loc.PATH);
				if (execve(loc.com_path_combine1, loc.argv_command_one, envp) == -1)
					ft_putstr_fd("bash : command not found\n", 2);
			}
			else
			{//printf("자식 프로세스 %d에서 자식 프로세스 %d로 파일 목록 전송 second\n", getpid(), loc.pid);
				close(loc.pipe_fds[0]);
				dup2(loc.pipe_fds[0], STDIN_FILENO);
				dup2(loc.pipe_fds[1], STDOUT_FILENO);
				close(loc.pipe_fds[0]);
				close(loc.pipe_fds[1]);
				loc.argv_command_one = ft_split(argv[i++], ' ');
				loc.com_path_combine1 = combine_command(loc.argv_command_one[0], loc.PATH);
				if (execve(loc.com_path_combine1, loc.argv_command_one, envp) == -1)
					ft_putstr_fd("bash : command not found\n", 2);
			}
		}
		else
		{
			//printf("부모 프로세스 %d에서 자식 프로세스 %d로 파일 목록 전송\n", getpid(), loc.pid);
			if (start == fork_count - 2)
			{//printf("부모 프로세스 %d에서 자식 프로세스 %d로 파일 목록 전송 frist \n", getpid(), loc.pid);
				close(loc.pipe_fds[1]);
				dup2(loc.pipe_fds[0], STDIN_FILENO);
				dup2(loc.outfile, STDOUT_FILENO);
				close(loc.pipe_fds[0]);
				close(loc.outfile);
				waitpid(loc.pid, NULL, WNOHANG);
				loc.argv_command_two = ft_split(argv[argc - 2], ' ');
				loc.com_path_combine2 = combine_command(loc.argv_command_two[0], loc.PATH);
				if (execve(loc.com_path_combine2, loc.argv_command_two, envp) == -1)
					ft_putstr_fd("bash : command not found\n", 2);
			}
			else
			{//printf("부모 프로세스 %d에서 자식 프로세스 %d로 파일 목록 전송 second \n", getpid(), loc.pid);
				
				// 			loc.argv_command_two = ft_split(argv[argc - 2], ' ');
				// loc.com_path_combine2 = combine_command(loc.argv_command_two[0], loc.PATH);
				// if (execve(loc.com_path_combine2, loc.argv_command_two, envp) == -1)
				// 	ft_putstr_fd("bash : command not found\n", 2);
			    //close(loc.pipe_fds[1]);
				//waitpid(loc.pid, NULL, WNOHANG);
				dup2(loc.pipe_fds[0], STDIN_FILENO);
				dup2(loc.pipe_fds[1], STDOUT_FILENO);
				//dup2(loc.pipe_fds[1], STDOUT_FILENO);
				close(loc.pipe_fds[0]);
				close(loc.pipe_fds[1]);
				//dup2(loc.pipe_fds[0], STDIN_FILENO);
				// loc.com_path_combine2 = combine_command(loc.argv_command_two[0], loc.PATH);
				// if (execve(loc.com_path_combine2, loc.argv_command_two, envp) == -1)
				// 	ft_putstr_fd("bash : command not found\n", 2);
				//dup2(loc.outfile, STDOUT_FILENO);
			}
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_info	loc;

	// if (argc != 5)
	// 	error("argument error\n");
	loc.infile = open(argv[1], O_RDONLY);
	if (loc.infile == -1)
		perror("infile error");

	// argc를 통해 제일 마지막꺼를 들고오자 
	loc.outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (loc.outfile == -1)
		error("outfile error");
	loc.PATH = find_path(envp);
	//command split -> 인자가 여러개 들어 올 수 있기 때문에 변수를 다르게 주어야함.
	// loc.argv_command_one = ft_split(argv[2], ' ');
	// loc.argv_command_two = ft_split(argv[3], ' ');
	
	// int i = 0;
	// int j = 0;
	// while (loc.argv_command_one[i])
	// {
	// 	printf("%s\n",loc.argv_command_one[i]);
	// 	i++;
	// }
	// while (loc.argv_command_two[j])
	// {
	// 	printf("%s\n" , loc.argv_command_two[j]);
	// 	j++;
	// }
	// exit(1);
	// //acces를 하기 위해 인자들을 각 loc.argv_command_숫자[0]를 붙여주어야함.
	// loc.com_path_combine1 = combine_command(loc.argv_command_one[0], loc.PATH);
	// loc.com_path_combine2 = combine_command(loc.argv_command_two[0], loc.PATH);
	pipe_start(loc, envp, argv, argc);
}
