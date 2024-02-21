/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_here_mult.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 20:01:48 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/05 14:11:13 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./bonus_head/pipex.h"

void	close_prev(t_info loc)
{
	close(loc.pipe_fds_from_prev[0]);
	close(loc.pipe_fds_from_prev[1]);
}

void	child_process(int start, int fork_count, t_info loc, char **envp)
{
	if (loc.check_here_doc == 1)
	{
		if (start == 3)
			here_doc_child_first(loc, start, envp);
		else if (start == fork_count - 1)
			child_last(loc, start, envp);
		else
			child_middle(loc, start, envp);
	}
	else
	{
		if (start == 2)
			multipipex_child_first(loc, start, envp);
		else if (start == fork_count - 1)
			child_last(loc, start, envp);
		else
			child_middle(loc, start, envp);
	}
}

void	child_parents_pro(t_info loc, int start, int fork_count, char **envp)
{
	if (loc.pid == -1)
		perror("fork error");
	else if (loc.pid == 0)
		child_process(start, fork_count, loc, envp);
	else
		waitpid(loc.pid, NULL, WNOHANG);
}

void	child_last(t_info loc, int i, char **envp)
{
	close(loc.pipe_fds_from_prev[1]);
	dup2(loc.pipe_fds_from_prev[0], STDIN_FILENO);
	dup2(loc.outfile, STDOUT_FILENO);
	close(loc.pipe_fds_from_prev[0]);
	close(loc.outfile);
	loc.argv_command_one = ft_split(loc.argv[i], ' ');
	loc.com_path_combine1 = combine_command(loc.argv_command_one[0], loc.path);
	if (execve(loc.com_path_combine1, loc.argv_command_one, envp) == -1)
		ft_putstr_fd("bash : command not found\n", 2);
}

void	child_middle(t_info loc, int i, char **envp)
{
	close(loc.pipe_fds_to_next[0]);
	close(loc.pipe_fds_from_prev[1]);
	dup2(loc.pipe_fds_from_prev[0], STDIN_FILENO);
	dup2(loc.pipe_fds_to_next[1], STDOUT_FILENO);
	close(loc.pipe_fds_to_next[1]);
	close(loc.pipe_fds_from_prev[0]);
	loc.argv_command_two = ft_split(loc.argv[i], ' ');
	loc.com_path_combine2 = combine_command(loc.argv_command_two[0], loc.path);
	if (execve(loc.com_path_combine2, loc.argv_command_two, envp) == -1)
		ft_putstr_fd("bash : command not found\n", 2);
}
