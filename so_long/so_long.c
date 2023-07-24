/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:25:53 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/24 18:49:11 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./head/so_long.h"

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
	game->count_dfs = 0;
	game->c_check = 0;
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

void	move_player(t_game* game, int index)
{
	printf("fuck\n");
	printf("game->map_line : %s", game->map_line);
	printf("game->map_line[index] : %d\n", game->map_line[index]);
	printf("p_index : %d, index : %d\n", game->p_index, index);
	
	printf("c : %d\n", game->c);
	//printf("game->map_line[p_index] : %d\n", game->map_line[game->p_index]);
	if (game->map_line[index] == '0')
	{
		printf("fuck1\n");
		game->map_line[index] = 'P';
		game->map_line[game->p_index] = '0';
		game->p_index = index;
	}
	else if (game->map_line[index] == '1')
		return ;
	else if (game->map_line[index] == 'C')
	{
		game->c_check++;
		game->map_line[index] = 'P';
		game->map_line[game->p_index] = '0';
		game->p_index = index;
	}
	else if (game->map_line[index] == 'E')
	{	
		if (game->c != game->c_check)
			return ;
		// else
		// 	map->line[move] = 'P';
		game->map_line[index] = 'P';
		game->map_line[game->p_index] = '0';
		game->p_index = index;
	}
	show_map(game);
}


int	goodbye_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	free(game->map_line);
	exit(0);
	return (0);

}


int	key_press(int keycode, t_game *game)
{

	printf("ss");
	if (keycode == KEY_W)
	{
		move_player(game, game->p_index - game->map_all_col);
	}
	else if (keycode == KEY_S)
		move_player(game, game->p_index + game->map_all_col);
	else if (keycode == KEY_A)
		move_player(game, game->p_index - 1);
	else if (keycode == KEY_D)
		move_player(game, game->p_index + 1);
	else if (keycode == KEY_ESC)
		goodbye_game(game);
	//printf("x: %d, y: %d\n", game->x, game->y);
	return (0);
}

int main(int argc, char **argv)
{
	// void	*mlx_ptr;
	// void	*win_ptr;
	t_game	game;

	if (check_argc_argv(argc, argv[1]) == 0)
		return (0);
	//1. game_초기화, x y 초기화
	init_game(&game);
	//2. ber 읽기
	game.map_line = read_map(&game, argv[1]);
	//3. DFS로 맵 확인
	check_map_DFS(&game);
	// check_map(&game);
	// if (!(game.check_DFS))
	// 	exit(1);
	
	//4.이미지파일
	// mlx_ptr = mlx_init();
	// win_ptr = mlx_new_window(mlx_ptr, game.map_all_row * 64, game.map_all_col * 64, "mlx 42");
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, game.map_all_col * 64, game.map_all_row * 64, "mlx 42");
	show_map(&game);
	// mlx_hook(win_ptr, X_EVENT_KEY_RELEASE, 0, &key_press, &game);
	// mlx_loop(mlx_ptr);
	mlx_hook(game.win, X_EVENT_KEY_RELEASE, 0, &key_press, &game);
	//mlx_hook(game.win, X_EVENT_KEY_EXIT, 0, &goodbye_game, &game);
	mlx_loop(game.mlx);
}
