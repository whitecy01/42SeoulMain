/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:24:58 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/30 18:04:56 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(t_info loc, char **envp)
{
	close(loc.pipe_fds[0]);
	dup2(loc.infile, STDIN_FILENO);
	dup2(loc.pipe_fds[1], STDOUT_FILENO);
	close(loc.pipe_fds[1]);
	close(loc.infile);
	if (execve(loc.com_path_combine1, loc.argv_command_one, envp) == -1)
		ft_putstr_fd("bash : command not found\n", 2);
}

void	parents_process(t_info loc, char **envp)
{
	close(loc.pipe_fds[1]);
	dup2(loc.pipe_fds[0], STDIN_FILENO);
	dup2(loc.outfile, STDOUT_FILENO);
	close(loc.pipe_fds[0]);
	close(loc.outfile);
	//waitpid(loc.pid, NULL, WNOHANG);
	if (execve(loc.com_path_combine2, loc.argv_command_two, envp) == -1)
		ft_putstr_fd("bash : command not found\n", 2);
}

void	pipe_start(t_info loc, char **envp)
{
	if (pipe(loc.pipe_fds) < 0)
		perror("pipe error");
	loc.pid = fork();
	if (loc.pid == -1)
		perror("fork error");
	else if (loc.pid == 0)
		child_process(loc, envp);
	else
		parents_process(loc, envp);
	while (wait(NULL) > 0)
		;
}

int	main(int argc, char **argv, char **envp)
{
	t_info	loc;

	if (argc != 5)
		error("argument error\n");
	loc.infile = open(argv[1], O_RDONLY);
	if (loc.infile == -1)
		perror("infile error");
	loc.outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (loc.outfile == -1)
		error("outfile error");
	loc.path = find_path(envp);
	loc.argv_command_one = ft_split(argv[2], ' ');
	loc.argv_command_two = ft_split(argv[3], ' ');
	loc.com_path_combine1 = combine_command(loc.argv_command_one[0], loc.path);
	loc.com_path_combine2 = combine_command(loc.argv_command_two[0], loc.path);
	pipe_start(loc, envp);
}
