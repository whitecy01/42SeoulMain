/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:25:53 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/22 20:31:15 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./head/so_long.h"

void	param_init(t_game *game)
{
	game->x = 3;
	game->y = 4;
}


int	key_press(int keycode, t_game *game)
{

	if (keycode == KEY_W)
		game->y++;
	else if (keycode == KEY_S)
		game->y--;
	else if (keycode == KEY_A)
		game->x--;
	else if (keycode == KEY_D)
		game->x++;
	else if (keycode == KEY_ESC)
		exit(0);
	//printf("x: %d, y: %d\n", game->x, game->y);
	return (0);
}


int	line_string_count(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			break ;
		i++;
	}
	return (i);
}

int	check_line(char *line, int line_len, t_game *game, int i)
{
	if (game->map_all_row == 0)
		game->map_all_row = line_len;
	if (game->map_all_row != line_len)
		return (0);
	while (++i < line_len)
	{
		if (line[i] == '0' || line[i] == '1')
			continue ;
		else if (line[i] == 'C')
			game->c++;
		else if (line[i] == 'E')
		{
			game->e++;
			game->e_index = ((game->map_all_col - 1) * line_len) + i;
		}
		else if (line[i] == 'P')
		{
			game->p++;
			game->p_index = ((game->map_all_col - 1) * line_len) + i;
		}
		else
			return (0);
	}
	return (1);
}

char	*read_map(t_game *game, char *filename)
{
	int		fd;
	char	*line;
	char	*map_buff;
	int		line_len;

	fd = open(filename, O_RDONLY);
	map_buff = NULL;
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line_len = line_string_count(line);
		game->map_all_col++;
		if (check_line(line, line_len, game, -1) == 1)
			map_buff = ft_strjoin(map_buff, line, line_len, \
				ft_strlen(map_buff));
		else
		{
			free(map_buff);
			map_buff = NULL;
			break ;
		}
		free(line);
		line = NULL;
	}
	free(line);
	return (map_buff);
}

void	init_game(t_game *game)
{
	game->map_line = NULL;
	game->map_all_col = 0;
	game->map_all_row = 0;
	game->e_index = 0;
	game->p_index = 0;
	game->c = 0;
	game->e = 0;
	game->p = 0;
}

int	error(char *s)
{
	write(2, "Error\n", 6);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	return (0);
}


int	check_argc_argv(int argc, char *argv)
{
	int	i;

	if (argc != 2)
		return (error("argc Error"));
	i = 0;
	while (argv[i] != '\0')
		i++;
	if (argv[i - 1] == 'r' && argv[i - 2] == 'e'
		&& argv[i - 3] == 'b' && argv[i - 4] == '.')
		return (1);
	return (error("ber Error"));
}

void	put_img(t_game *game, int y, int x, char *file)
{
	int		img_width;
	int		img_height;
	void	*img;

	img = mlx_xpm_file_to_image(game->mlx, file, &img_width, &img_height);
	if (!img)
		return ;
	mlx_put_image_to_window(game->mlx, game->win, img, y * 64, x * 64);
	mlx_destroy_image(game->mlx, img);
}

void	categorize_case(t_game *game, int x, int y, int index)
{
	if (game->map_line[index] == '0')
		put_img(game, y, x, "./images/back_ground.xpm");
	else if (game->map_line[index] == '1')
	{
		put_img(game, y, x, "./images/back_ground.xpm");
		put_img(game, y, x, "./images/tree.xpm");
	}
	else if (game->map_line[index] == 'E')
	{
		put_img(game, y, x, "./images/back_ground.xpm");
		put_img(game, y, x, "./images/door.xpm");
	}
	else if (game->map_line[index] == 'C')
	{
		put_img(game, y, x, "./images/back_ground.xpm");
		if (index % 2 == 0)
			put_img(game, y, x, "./images/eat.xpm");
		else
			put_img(game, y, x, "./images/eat.xpm");
	}
	else if (game->map_line[index] == 'P')
	{
		put_img(game, y, x, "./images/back_ground.xpm");
		put_img(game, y, x, "./images/player.xpm");
	}
}


void	show_map(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	int x = -1;
	int index = 0;
	int y = -1;
	while (++x < game->map_all_col)
	{
		y = -1;
		while (++y < game->map_all_row)
		{
			categorize_case(game, x, y, index);
			index++;
		}
	}
}


int main(int argc, char **argv)
{
	// void	*mlx_ptr;
	// void	*win_ptr;
	t_game	game;

	if (check_argc_argv(argc, argv[1]) == 0)
		return (0);
	//1. game_초기화, x y 초기화
	param_init(&game);
	init_game(&game);
	//2. ber 읽기
	game.map_line = read_map(&game, argv[1]);
	//3.이미지파일

	// printf("%s\n", game.map_line);
	// printf("e_index : %d\n", game.e_index);
	// printf("p_index : %d\n", game.p_index);
	// printf("c : %d\n", game.c);
	// printf("e : %d\n", game.e);
	// printf("p : %d\n", game.p);
	//3.x,y 초기화
	// mlx_ptr = mlx_init();
	// win_ptr = mlx_new_window(mlx_ptr, game.map_all_row * 64, game.map_all_col * 64, "mlx 42");
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, game.map_all_row * 64, game.map_all_col * 64, "mlx 42");
	show_map(&game);
	// mlx_hook(win_ptr, X_EVENT_KEY_RELEASE, 0, &key_press, &game);
	// mlx_loop(mlx_ptr);
	mlx_hook(game.win, X_EVENT_KEY_RELEASE, 0, &key_press, &game);
	mlx_loop(game.mlx);
}
