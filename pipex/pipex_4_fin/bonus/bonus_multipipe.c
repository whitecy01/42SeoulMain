/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_multipipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:08:16 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/30 17:53:59 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./bonus_head/pipex.h"

void	open_outfile__infile_multipipe(t_info loc, int argc, char **argv)
{
	if (argc < 5)
		error("argument error\n");
	loc.infile = open(argv[1], O_RDONLY);
	if (loc.infile == -1)
		perror("infile error");
	loc.outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
}

void	multipipex_child_first(t_info loc, int i, char **envp)
{
	close(loc.pipe_fds_to_next[0]);
	dup2(loc.infile, STDIN_FILENO);
	dup2(loc.pipe_fds_to_next[1], STDOUT_FILENO);
	close(loc.pipe_fds_to_next[1]);
	close(loc.infile);
	loc.argv_command_one = ft_split(loc.argv[i], ' ');
	loc.com_path_combine1 = combine_command(loc.argv_command_one[0], loc.path);
	if (execve(loc.com_path_combine1, loc.argv_command_one, envp) == -1)
		ft_putstr_fd("bash : command not found\n", 2);
}

void	pipe_start(t_info loc, char **envp, int argc)
{
	int	fork_count;
	int	start;

	fork_count = argc - 1;
	start = 2;
	while (start < fork_count)
	{
		if (start > 3)
			close_prev(loc);
		loc.pipe_fds_from_prev[0] = loc.pipe_fds_to_next[0];
		loc.pipe_fds_from_prev[1] = loc.pipe_fds_to_next[1];
		if (start < fork_count -1)
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
