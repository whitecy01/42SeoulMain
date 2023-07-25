/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:54:22 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/25 17:47:25 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./mlx/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_game{
	int				x;
	int				y;
	char			*map_line;
	int				map_all_col;
	int				map_all_row;
	int				e_index;
	int				p_index;
	int				c;
	int				e;
	int				p;
	void			*mlx;
	void			*win;
	int				count_dfs;
	int				c_check;
	unsigned int	move_count;
}				t_game;

# define X_EVENT_KEY_PRESS			2
# define X_EVENT_KEY_RELEASE		3
# define X_EVENT_KEY_EXIT			17

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
char	*read_map(t_game *game, int fd);

//so_long_error_free.c
int		error(char *s);
void	ft_free(char *tmp);
char	*boom_map_buff(char *line, char *map_buf);

//so_long_DFS.c
int		check_move(int up, t_game *game);
void	dfs(t_game *game, int p_index, char *map);
void	check_map_dfs(t_game *game);
void	error_dfs(char *tmp);

//so_long_show_map.c
void	show_map(t_game *game);
void	categorize_case(t_game *game, int x, int y, int index);
void	put_img(t_game *game, int y, int x, char *file);

//so_long.c
void	init_game(t_game *game);
int		check_argc_argv(int argc, char *argv);

//so_long_key_press.c
int		goodbye_game(t_game *game);
int		key_press(int keycode, t_game *game);
void	move_player(t_game *game, int index);
void	move_write(unsigned int move);
void	move_func(t_game *game);

//so_long_check_wall_count.c
void	check_map_count(t_game *game);
void	check_map_wall(t_game *game);
void	check_map_wall_count(t_game *game);
#endif