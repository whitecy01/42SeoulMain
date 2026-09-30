/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_key_press.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:12:31 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/25 17:35:38 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_write(unsigned int move)
{
	char	i;

	if (move / 10 > 0)
		move_write(move / 10);
	i = move % 10 + '0';
	write(1, &i, 1);
}

void	move_func(t_game *game)
{
	write(1, "move_count:", 12);
	move_write(++game->move_count);
	write(1, "\n", 1);
}

void	move_player(t_game *game, int index)
{
	if (game->map_line[index] == '0')
	{
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
		game->map_line[index] = 'P';
		game->map_line[game->p_index] = '0';
		game->p_index = index;
	}
	move_func(game);
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
	if (keycode == KEY_W)
		move_player(game, game->p_index - game->map_all_col);
	else if (keycode == KEY_S)
		move_player(game, game->p_index + game->map_all_col);
	else if (keycode == KEY_A)
		move_player(game, game->p_index - 1);
	else if (keycode == KEY_D)
		move_player(game, game->p_index + 1);
	else if (keycode == KEY_ESC)
		goodbye_game(game);
	return (0);
}
