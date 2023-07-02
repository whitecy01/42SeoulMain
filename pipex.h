
#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_info
{
    //1. infile, outfile 검사
    int infile;
    int outfile;
    //2. 명령어를 공백 기준으로 split 한 다음 넣기 
    char *argv_command_one;
    char *argv_command_two;

}	t_info;

#endif 