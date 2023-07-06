
#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

typedef struct s_info
{
    //1. infile, outfile 검사
    int infile;
    int outfile;
    //2. 명령어를 공백 기준으로 split 한 다음 넣기 
    char **argv_command_one;
    char **argv_command_two;
	//3. 환경변수 PATH split 한 후 가져오기
	char **PATH;
	//acces를 하기 위한 자료
	char *com_path_combine1;
	char *com_path_combine2;
	//pipe
	int	pid;
	//pipe_fds
	int pipe_fds[2];

}	t_info;


//error_free.c
void	error(char *error);
char	**ft_free(char **word);

//findpath.c
int		number_compare(const char *str1, const char *str2, size_t n);
char	**find_path(char **envp);

//path_split.c
int		separator_slash(char tmp);
int		separator_colon(char tmp);
char	*word_split(char *envp_path);
int		ma_count(char *envp_path);
char	**envp_split(char *envp_path);

//pipex.c
int		count_str(char *str);

//split.c
int		string_check(char s, char c);
int		malloc_count(char const *s, char c);
char	*word_input(char const *s, char c);
char	**ft_split(char const *s, char c);

#endif 