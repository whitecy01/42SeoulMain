/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:24:58 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/16 20:34:41 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./bonus_head/pipex.h"

void	main_next(t_info loc, int argc, char **envp)
{
	if (loc.outfile == -1)
		error("outfile error");
	loc.path = find_path(envp);
	if (loc.check_here_doc == 0)
		pipe_start(loc, envp, argc);
	else if (loc.check_here_doc == 1)
		here_doc_pipe_start(loc, envp, argc);
	ft_free(loc.path);
	unlink(".here_doc_tmp");
}

int	main(int argc, char **argv, char **envp)
{
	t_info	loc;

	loc.argv = argv;
	loc.check_here_doc = 0;
	if (argc < 4)
		error("argument error\n");
	if (number_compare(argv[1], "here_doc", 8) == 0
		&& (count_str(argv[2]) != 0))
	{
		check_argument(argc, 6);
		loc.argv_two = argv[2];
		loc.outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_APPEND, 0644);
		loc.check_here_doc = 1;
	}
	else
	{
		check_argument(argc, 5);
		if (argc < 5)
			error("argument error\n");
		loc.infile = open(argv[1], O_RDONLY);
		if (loc.infile == -1)
			perror("infile error");
		loc.outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	}
	main_next(loc, argc, envp);
}
