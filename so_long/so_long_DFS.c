/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_DFS.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:01:53 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/24 20:41:03 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./head/so_long.h"

int	check_move(int up, t_game *game)
{
	int end_index;

	end_index = (game->map_all_col * game->map_all_row) - 1;
	if (0 <= up && up <= end_index)
	{
		return (1);
	}
	return (0);
}

void DFS(t_game *game, int p_index, char *map)
{
	int up;
	int down;
	int left;
	int right;

	up = p_index - game->map_all_col;
	down = p_index + game->map_all_col;
	left = p_index - 1;
	right = p_index + 1;
	if (map[p_index] == 'E' || map[p_index] == 'C')
		game->count_dfs++;
	if (map[p_index] != 'E')
	{
		map[p_index] = '1';
		if (check_move(up, game) && map[up] != '1')
			DFS(game, up, map);
		if (check_move(down, game) && map[down] != '1')
			DFS(game, down, map);
		if (check_move(left, game) && map[left] != '1')
			DFS(game, left, map);
		if (check_move(right, game) && map[right] != '1')
			DFS(game, right, map);
	}
	else
		map[p_index] = '1';
}

void	error_dfs(char *tmp)
{
	int i;

	i = 0;
	while (tmp[i])
	{
		write(2, &tmp[i], 1);
		i++;
	}
	exit(2);
}

void	check_map_DFS(t_game *game)
{
	char *map_dfs;

	map_dfs = ft_strdup(game->map_line);
	if (!map_dfs)
		exit(1);
	DFS(game, game->p_index, map_dfs);
	free(map_dfs);
	if (game->count_dfs != (game->c + game->e))
		error_dfs("map error\n");
}
