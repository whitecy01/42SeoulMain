/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_show_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:04:03 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/25 17:35:45 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
		if (game->c_check == game->c)
			put_img(game, y, x, "./images/door_open.xpm");
		else
			put_img(game, y, x, "./images/door.xpm");
	}
	else if (game->map_line[index] == 'C')
	{
		put_img(game, y, x, "./images/back_ground.xpm");
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
	int	x;
	int	index;
	int	y;

	x = -1;
	index = 0;
	y = -1;
	mlx_clear_window(game->mlx, game->win);
	while (++x < game->map_all_row)
	{
		y = -1;
		while (++y < game->map_all_col)
		{
			categorize_case(game, x, y, index);
			index++;
		}
	}
	if (game->map_line[game->p_index] == game->map_line[game->e_index] \
		&& (game->c_check == game->c))
	{	
		goodbye_game(game);
		return ;
	}
}
