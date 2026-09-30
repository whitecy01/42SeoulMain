/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:42:41 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/16 20:25:07 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define BUFFER_SIZE 5

typedef struct s_info
{
	int		infile;
	int		outfile;
	int		check_here_doc;
	char	**argv_command_one;
	char	**argv_command_two;
	char	**path;
	char	*com_path_combine1;
	char	*com_path_combine2;
	int		pid;
	int		pipe_fds_from_prev[2];
	int		pipe_fds_to_next[2];
	int		her_doc_fd;
	char	*argv_two;
	char	**argv;
}	t_info;

void	error(char *error);
char	**ft_free(char **word);
void	ft_putstr_fd(char *str, int fd);
void	check_argument(int argc, int check);
char	*combine_command(char *first_loc_command, char **path);
char	*ft_strjoin_gnl(char *s1, char *s2);
int		number_compare(const char *str1, const char *str2, size_t n);
char	**find_path(char **envp);
int		count_str(char *str);
int		separator_slash(char tmp);
int		separator_colon(char tmp);
char	*word_split(char *envp_path);
int		ma_count(char *envp_path);
char	**envp_split(char *envp_path);
int		ft_strlen_gnl(const char *s);
char	*ft_substr_gnl(char *s, unsigned int start, unsigned int len);
char	*ft_strdup(char *string);
char	*ft_strjoin(char *s1, char *s2, int s2_len, int count);
char	*ft_strchr(const char *s, int c);
char	*readline(int fd, char *line);
int		len_check(char *line);
char	*change_line(char **line, char **backup);
char	*get_next_line(int fd);
void	main_next(t_info loc, int argc, char **envp);
int		separator_slash(char tmp);
int		separator_colon(char tmp);
char	*word_split(char *envp_path);
int		ma_count(char *envp_path);
char	**envp_split(char *envp_path);
int		string_check(char s, char c);
int		malloc_count(char const *s, char c);
char	*word_input(char const *s, char c);
char	**ft_split(char const *s, char c);
void	open_outfile_heredoc(t_info loc, int argc, char **argv);
void	get_next(t_info loc);
void	here_doc_child_first(t_info loc, int i, char **envp);
void	here_doc_pipe_start(t_info loc, char **envp, int argc);
void	open_outfile__infile_multipipe(t_info loc, int argc, char **argv);
void	multipipex_child_first(t_info loc, int start, char **envp);
void	pipe_start(t_info loc, char **envp, int argc);
void	close_prev(t_info loc);
void	child_process(int start, int fork_count, t_info loc, char **envp);
void	child_parents_pro(t_info loc, int start, int fork_count, char **envp);
void	child_last(t_info loc, int i, char **envp);
void	child_middle(t_info loc, int i, char **envp);

#endif 