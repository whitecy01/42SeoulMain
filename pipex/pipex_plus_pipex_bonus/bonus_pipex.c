/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:24:58 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/13 18:05:38 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */


#include "./bonus_head/pipex.h"


int	count_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

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

char	*combine_command(char *first_loc_command, char **path)
{
	char	*combine;
	int		i;
	char	*tmp;
	int		fd;

	fd = access(first_loc_command, X_OK);
	if (fd != -1)
		return (first_loc_command);
	combine = ft_strjoin_gnl("/", first_loc_command);
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin_gnl(path[i], combine);
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

void	pipe_start(t_info loc, char **envp, char **argv, int argc)
{
	int i = 2;
	int fork_count = argc - 3;
	int start = -1;

	while (++start < fork_count)
	{
		if (start > 1)
		{
			close(loc.pipe_fds_from_prev[0]);
			close(loc.pipe_fds_from_prev[1]);
		}
		loc.pipe_fds_from_prev[0] = loc.pipe_fds_to_next[0];
		loc.pipe_fds_from_prev[1] = loc.pipe_fds_to_next[1];
		if (start < fork_count -1)
			if (pipe(loc.pipe_fds_to_next) < 0)
				perror("pipe error");
		loc.pid = fork();
		if (loc.pid == -1)
			perror("fork error");
		else if (loc.pid == 0)
		{
			if (start == 0)
			{
				close(loc.pipe_fds_to_next[0]);
				dup2(loc.infile, STDIN_FILENO);
				dup2(loc.pipe_fds_to_next[1], STDOUT_FILENO);
				close(loc.pipe_fds_to_next[1]);
			 	close(loc.infile);
				loc.argv_command_one = ft_split(argv[i], ' ');
				loc.com_path_combine1 = combine_command(loc.argv_command_one[0], loc.PATH);
				if (execve(loc.com_path_combine1, loc.argv_command_one, envp) == -1)
					ft_putstr_fd("bash : command not found\n", 2);
			}
			else if (start == fork_count - 1)
			{
				// close(loc.pipe_fds_to_next[0]); (위의 조건문으로 생생성  안안함함)
				// close(loc.pipe_fds_to_next[1]);
				close(loc.pipe_fds_from_prev[1]);
				dup2(loc.pipe_fds_from_prev[0], STDIN_FILENO);
				dup2(loc.outfile, STDOUT_FILENO);
				close(loc.pipe_fds_from_prev[0]);
				close(loc.outfile);
				loc.argv_command_one = ft_split(argv[i], ' ');
				loc.com_path_combine1 = combine_command(loc.argv_command_one[0], loc.PATH);
				if (execve(loc.com_path_combine1, loc.argv_command_one, envp) == -1)
				{
					ft_putstr_fd("bash : command not found\n", 2);

				}
			}
			else
			{
				close(loc.pipe_fds_to_next[0]);
				close(loc.pipe_fds_from_prev[1]);
				dup2(loc.pipe_fds_from_prev[0], STDIN_FILENO);
				dup2(loc.pipe_fds_to_next[1], STDOUT_FILENO);
				close(loc.pipe_fds_to_next[1]);
				close(loc.pipe_fds_from_prev[0]);
				loc.argv_command_two = ft_split(argv[i], ' ');
				loc.com_path_combine2 = combine_command(loc.argv_command_two[0], loc.PATH);
				if (execve(loc.com_path_combine2, loc.argv_command_two, envp) == -1)
				{
					ft_putstr_fd("bash : command not found\n", 2);
				}
			}
		}
		else
		{
			waitpid(loc.pid, NULL, WNOHANG);
		}
		i++;
	}
	close(loc.pipe_fds_from_prev[0]);
	close(loc.pipe_fds_from_prev[1]);
	while(wait(NULL) > 0)
			;
}






int	check_command(char *temp)
{
	
	if (number_compare(temp, "LIMITER", 7) == 0)
		return (0);
	return (1);
}

char* my_strstr(const char* haystack, const char* needle) {
    if (*needle == '\0')
        return (char*)haystack;

    while (*haystack) {
        const char* h = haystack;
        const char* n = needle;

        while (*h == *n && *n) {
            h++;
            n++;
        }

        if (*n == '\0')
            return (char*)haystack;

        haystack++;
    }

    return NULL;
}


void get_next(t_info loc)
{
	char	*buff;
	char	herefd;
	char	*endflag;

	loc.her_doc_fd = 0;
	buff = 0;
	herefd = open(".here_doc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	endflag = ft_strjoin_gnl("LIMITER", "\n");
	while (1)
	{
		write(1, "> ", 2);
		buff = get_next_line(0);
		if (number_compare(buff, endflag, ft_strlen_gnl(endflag)) == 0)
		{
			free(buff);
			free(endflag);
			close(herefd);
			return ;
		}
		write(herefd, buff, ft_strlen_gnl(buff));
		if (buff)
			free(buff);
		buff = 0;
	}
	return ;
}

//  void get_next(int fd)
// {
// 	printf("awdaw : %d", fd);
// 	//char	*temp;
//     char    buff[BUFFER_SIZE + 1];
// 	char	*line;

// 	int readcount = 1;
		
//     while (readcount )
// 	{
// 		readcount = read(0, buff, BUFFER_SIZE);
// 		if (readcount == 0)
// 			break ;
// 		else if (readcount == -1)
// 		{
// 			free(line);
// 			line = NULL;
// 			return ;
// 		}
// 		buff[readcount] = '\0';
// 		line = ft_strjoin(line, buff, readcount, ft_strlen_gnl(line));
// 		if (!line)
// 			return ;
// 		printf("biff : %s\n", buff);
// 		if (ft_strchr(buff, '\n'))
// 		{
			
// 			if(my_strstr(buff, "LIMITER") == 0)
// 			{
// 				close(fd);
// 				break;
// 			}
// 			else
// 				write(fd, buff, 1);
// 		} 

// 	}
// 	close(fd);
// 	printf("debug");
/* 	temp = get_next_line(0);
	while (temp)
	{
		if (check_command(temp) == 0)
		{
			return ; 
		}
		//printf("temp : %s\n", temp);
		write(fd, temp, 1);
		free(temp);
		temp = get_next_line(0);
	} */

/*     	
	if (sort_check_stack(a) == 0 || check_b(b) == 0)
	 	write(1, "KO\n", 3);
	else
	 	write(1, "OK\n", 3); */
	//free(temp);
//}  
 

void here_doc_pipe_start(t_info loc, char **envp, char **argv, int argc)
{
	int i = 3;
	int fork_count = argc - 4;
	int start = -1;
	int tmp_fd;

	get_next(loc);
	tmp_fd = open(".here_doc_tmp", O_RDONLY);
	while (++start < fork_count)
	{
		if (start > 1)
		{
			close(loc.pipe_fds_from_prev[0]);
			close(loc.pipe_fds_from_prev[1]);
		}
		loc.pipe_fds_from_prev[0] = loc.pipe_fds_to_next[0];
		loc.pipe_fds_from_prev[1] = loc.pipe_fds_to_next[1];
		if (start < fork_count -1)
			if (pipe(loc.pipe_fds_to_next) < 0)
				perror("pipe error");
		loc.pid = fork();
		if (loc.pid == -1)
			perror("fork error");
		else if (loc.pid == 0)
		{
			if (start == 0)
			{
				close(loc.pipe_fds_to_next[0]);
				dup2(tmp_fd, STDIN_FILENO);
				dup2(loc.pipe_fds_to_next[1], STDOUT_FILENO);
				close(loc.pipe_fds_to_next[1]);
				loc.argv_command_one = ft_split(argv[i], ' ');
				loc.com_path_combine1 = combine_command(loc.argv_command_one[0], loc.PATH);
				if (execve(loc.com_path_combine1, loc.argv_command_one, envp) == -1)
					ft_putstr_fd("bash : command not found\n", 2);
			}
			else if (start == fork_count - 1)
			{
				// close(loc.pipe_fds_to_next[0]); (위의 조건문으로 생생성  안안함함)
				// close(loc.pipe_fds_to_next[1]);
				close(loc.pipe_fds_from_prev[1]);
				dup2(loc.pipe_fds_from_prev[0], STDIN_FILENO);
				dup2(loc.outfile, STDOUT_FILENO);
				close(loc.pipe_fds_from_prev[0]);
				close(loc.outfile);
				loc.argv_command_one = ft_split(argv[i], ' ');
				loc.com_path_combine1 = combine_command(loc.argv_command_one[0], loc.PATH);
				if (execve(loc.com_path_combine1, loc.argv_command_one, envp) == -1)
				{
					ft_putstr_fd("bash : command not found\n", 2);

				}
			}
			else
			{
				close(loc.pipe_fds_to_next[0]);
				close(loc.pipe_fds_from_prev[1]);
				dup2(loc.pipe_fds_from_prev[0], STDIN_FILENO);
				dup2(loc.pipe_fds_to_next[1], STDOUT_FILENO);
				close(loc.pipe_fds_to_next[1]);
				close(loc.pipe_fds_from_prev[0]);
				loc.argv_command_two = ft_split(argv[i], ' ');
				loc.com_path_combine2 = combine_command(loc.argv_command_two[0], loc.PATH);
				if (execve(loc.com_path_combine2, loc.argv_command_two, envp) == -1)
				{
					ft_putstr_fd("bash : command not found\n", 2);
				}
			}
		}
		else
		{
			waitpid(loc.pid, NULL, WNOHANG);
		}
		i++;
	}
	close(loc.pipe_fds_from_prev[0]);
	close(loc.pipe_fds_from_prev[1]);
	while(wait(NULL) > 0)
			;	
	//
	close(tmp_fd);
	unlink(".here_doc_tmp");
} 



int	main(int argc, char **argv, char **envp)
{
	t_info	loc;
    

 	loc.check_here_doc = 0;
	if (number_compare(argv[1], "here_doc", 8) == 0 && number_compare(argv[2], "LIMITER", 7) == 0)
	{
		//get_line(loc);
		loc.outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_APPEND, 0644);
		loc.check_here_doc = 1;
	}
	else
	{
		loc.infile = open(argv[1], O_RDONLY);
		if (loc.infile == -1)
		perror("infile error");
		loc.outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	}
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
	if (loc.check_here_doc == 0)
		pipe_start(loc, envp, argv, argc);
	else if (loc.check_here_doc == 1)
	{
		here_doc_pipe_start(loc, envp, argv, argc);
	}
}
