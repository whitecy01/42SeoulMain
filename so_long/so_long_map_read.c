/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_map_read.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:57:22 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/25 17:35:41 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	line_string_count(char *line)
{
	int	i;

	if (!line)
		return (0);
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
	if (game->map_all_col == 0)
		game->map_all_col = line_len;
	if (game->map_all_col != line_len)
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
			game->e_index = ((game->map_all_row - 1) * line_len) + i;
		}
		else if (line[i] == 'P')
		{
			game->p++;
			game->p_index = ((game->map_all_row - 1) * line_len) + i;
		}
		else
			error("invalid input map\n");
	}
	return (1);
}

char	*read_map(t_game *game, int fd)
{
	char	*line;
	char	*map_buf;
	int		line_len;

	map_buf = NULL;
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line_len = line_string_count(line);
		game->map_all_row++;
		if (check_line(line, line_len, game, -1) == 1)
			map_buf = ft_strjoin(map_buf, line, line_len, ft_strlen(map_buf));
		else
		{
			ft_free(map_buf);
			break ;
		}
		ft_free(line);
	}
	free(line);
	return (map_buf);
}
