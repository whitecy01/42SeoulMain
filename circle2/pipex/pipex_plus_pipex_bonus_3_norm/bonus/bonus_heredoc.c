/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:10:57 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/16 20:23:26 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./bonus_head/pipex.h"

void	open_outfile_heredoc(t_info loc, int argc, char **argv)
{
	if (argc < 6)
		error("argument error\n");
	loc.argv_two = argv[2];
	loc.outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_APPEND, 0644);
	loc.check_here_doc = 1;
}

void	get_next(t_info loc)
{
	char	*buff;
	int		herefd;
	char	*endflag;

	buff = 0;
	herefd = open(".here_doc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	endflag = ft_strjoin_gnl(loc.argv_two, "\n");
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

void	here_doc_child_first(t_info loc, int i, char **envp)
{
	int	tmp_fd;

	tmp_fd = open(".here_doc_tmp", O_RDONLY);
	close(loc.pipe_fds_to_next[0]);
	dup2(tmp_fd, STDIN_FILENO);
	dup2(loc.pipe_fds_to_next[1], STDOUT_FILENO);
	close(loc.pipe_fds_to_next[1]);
	close(tmp_fd);
	loc.argv_command_one = ft_split(loc.argv[i], ' ');
	loc.com_path_combine1 = combine_command(loc.argv_command_one[0], loc.path);
	if (execve(loc.com_path_combine1, loc.argv_command_one, envp) == -1)
		ft_putstr_fd("bash : command not found\n", 2);
}

void	here_doc_pipe_start(t_info loc, char **envp, int argc)
{
	int	fork_count;
	int	start;

	fork_count = argc - 1;
	start = 3;
	get_next(loc);
	while (start < fork_count)
	{
		if (start > 4)
			close_prev(loc);
		loc.pipe_fds_from_prev[0] = loc.pipe_fds_to_next[0];
		loc.pipe_fds_from_prev[1] = loc.pipe_fds_to_next[1];
		if (start < fork_count - 1)
			if (pipe(loc.pipe_fds_to_next) < 0)
				perror("pipe error");
		loc.pid = fork();
		child_parents_pro(loc, start, fork_count, envp);
		start++;
	}
	close_prev(loc);
	while (wait(NULL) > 0)
		;
}
