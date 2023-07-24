/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:54:22 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/24 18:48:32 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# include <stdio.h>

typedef struct s_game{
	int		x;
	int		y;
	char	*map_line;
	int		map_all_col;
	int		map_all_row;
	int		e_index;
	int		p_index;
	int		c;
	int		e;
	int		p;
	void	*mlx;
	void	*win;
	//DFS count
	int		count_dfs;
	
	int		c_check;
}				t_game;

# define X_EVENT_KEY_PRESS			2
# define X_EVENT_KEY_RELEASE		3

# define KEY_ESC		53
# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2

# define BUFFER_SIZE 42

//get_next_line.c
char	*ft_readline(int fd, char *buff, char *backup);
int		len_check(char *line);
char	*change_line(char **line, char **backup);
char	*get_next_line(int fd);

//get_next_line_utils.c
int		ft_strlen(const char *s);
char	*ft_substr(char *s, unsigned int start, unsigned int len);
char	*ft_strdup(char *string);
char	*ft_strjoin(char *s1, char *s2, int s2_len, int count);
char	*ft_strchr(const char *s, int c);

//so_long_map_read.c
int		line_string_count(char *line);
int		check_line(char *line, int line_len, t_game *game, int i);
char	*read_map(t_game *game, char *filename);

//so_long_error_free.c
int		error(char *s);

//so_long_DFS.c
int		check_move(int up, t_game *game);
void	DFS(t_game *game, int p_index, char *map);
void	check_map_DFS(t_game *game);
void	error_dfs(char *tmp);

//so_long_show_map.c

void	show_map(t_game *game);
void	categorize_case(t_game *game, int x, int y, int index);
void	put_img(t_game *game, int y, int x, char *file);

//so_long.c
void	init_game(t_game *game);
int		check_argc_argv(int argc, char *argv);
int		key_press(int keycode, t_game *game);

int		goodbye_game(t_game *game);
#endif