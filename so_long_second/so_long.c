/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:25:53 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/25 20:50:16 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	game->move_count = 0;
}

int	check_argc_argv(int argc, char *argv)
{
	int	i;

	if (argc != 2)
		return (error("argc Error\n"));
	i = 0;
	while (argv[i] != '\0')
		i++;
	if (argv[i - 1] == 'r' && argv[i - 2] == 'e'
		&& argv[i - 3] == 'b' && argv[i - 4] == '.')
		return (1);
	return (error("ber Error\n"));
}

int	main(int argc, char **argv)
{
	t_game	game;
	int		fd;

	if (check_argc_argv(argc, argv[1]) == 0)
		return (0);
	init_game(&game);
	fd = open(argv[1], O_RDONLY);
	if (!fd)
		perror("open error\n");
	game.map_line = read_map(&game, fd);
	if (!game.map_line)
		error("map error\n");
	check_map_wall_count(&game);
	check_map_dfs(&game);
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, game.map_all_col * 64, \
		game.map_all_row * 64, argv[0]);
	show_map(&game);
	mlx_hook(game.win, X_EVENT_KEY_RELEASE, 0, &key_press, &game);
	mlx_hook(game.win, X_EVENT_KEY_EXIT, 0, &goodbye_game, &game);
	mlx_loop(game.mlx);
}
