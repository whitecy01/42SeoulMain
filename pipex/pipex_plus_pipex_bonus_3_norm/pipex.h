/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:46:32 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/16 15:05:02 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_info
{
	int		infile;
	int		outfile;
	char	**argv_command_one;
	char	**argv_command_two;
	char	**path;
	char	*com_path_combine1;
	char	*com_path_combine2;
	int		pid;
	int		pipe_fds[2];
}	t_info;

char	*ft_strjoin(char *s1, char *s2);
char	*combine_command(char *first_loc_command, char **path);
void	error(char *error);
char	**ft_free(char **word);
void	ft_putstr_fd(char *str, int fd);
int		number_compare(const char *str1, const char *str2, size_t n);
char	**find_path(char **envp);
int		count_str(char *str);
int		separator_slash(char tmp);
int		separator_colon(char tmp);
char	*word_split(char *envp_path);
int		ma_count(char *envp_path);
char	**envp_split(char *envp_path);
void	pipe_start(t_info loc, char **envp);
void	child_process(t_info loc, char **envp);
void	parents_process(t_info loc, char **envp);
int		string_check(char s, char c);
int		malloc_count(char const *s, char c);
char	*word_input(char const *s, char c);
char	**ft_split(char const *s, char c);



#endif 