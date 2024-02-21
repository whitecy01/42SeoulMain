/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_check_wall_count.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:39:22 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/25 20:40:44 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_map_count(t_game *game)
{
	if (game->c <= 0)
		error("map C error");
	if (game->p != 1)
		error("map P error");
	if (game->e != 1)
		error("map E error");
}

void	check_map_wall(t_game *game)
{
	int	i;
	int	map_count;
	int	j;

	i = 0;
	map_count = line_string_count(game->map_line);
	while (i < game->map_all_col)
	{
		if (game->map_line[i] != '1' || \
			game->map_line[(map_count - game->map_all_col) + i] != '1')
			error("map wall error");
		i++;
	}
	i = 0;
	j = 1;
	while (i < game->map_all_row)
	{
		if (game->map_line[i * game->map_all_col] != '1')
			error("map wall error");
		if (game->map_line[(game->map_all_col * j) - 1] != '1')
			error("map wall error");
		i++;
		j++;
	}
}

void	check_map_wall_count(t_game *game)
{	
	check_map_wall(game);
	check_map_count(game);
}
