/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 19:14:50 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/09/06 19:34:01 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "header/cub3d.h"

int	check_argv(char *argv)
{
	int	string;

	string = str_length(argv);
	//.cub 길이를 셈 -> 4보다 작으면 에러
	if (string <= 4)
		return (0);
	//.cub가 맞는지 확인
	if (argv[string - 1] == 'b' && argv[string - 2] == 'u'
		&& argv[string - 3] == 'c' && argv[string - 4] == '.')
		return (1);
	return (0);
}

void	init_game(t_game *game, char *file)
{
	t_map_info	*tmp;

	game->map = NULL;
	game->height = 0;
	game->width = 0;
	game->player_count = 0;
	game->fd = open(file, O_RDONLY);
	if (game->fd < 0)
	{
		perror("open Error");
		exit(1);
	}
	game->img = (t_img *)malloc(sizeof(t_img));
	// game->img->img_no = NULL;
	// game->img->img_so = NULL;
	// game->img->img_we = NULL;
	// game->img->img_ea = NULL;
	game->mlx = mlx_init();
	tmp = (t_map_info *)malloc(sizeof(t_map_info));
	tmp->max_width = 0;
	tmp->row = 0;
	tmp->head = NULL;
	tmp->tail = NULL;
	game->map_info = tmp;
}

void	check(void)
{
	system("leaks cub3d");
}

int	main(int argc, char **argv)
{
	t_game		game;

	//atexit(check);
	//1. argc 2가 아닐 때 에라
	if (argc != 2)
		error("Error\n");
	//2. .cub 체크
	if (!(check_argv(argv[1])))
		error("Error\n");
	//3. game 구조체 초기화
	init_game(&game, argv[1]);
	//4. gnl
	read_map(&game);

	//잘 들어왔는지 출력
	// printf("map : %s\n", game.map);
	// printf("player : %d\n",game.player_count);
	// for (int i = 0; i < 3; i++)
	// 	printf("ceil : %d\n" ,game.img->ceil[i]);
	// for (int i = 0; i < 3; i++)
	// 	printf("floor : %d\n" ,game.img->floor[i]);
		
	printf("game->tmp->row : %d\n", game.map_info->row);

	//5.맵 유효성 검사
	check_map(&game);
	//릭은 일단 나중에
	free(game.img->img_ea);
	free(game.img->img_no);
	free(game.img->img_so);
	free(game.img->img_we);
	free(game.img);
	free(game.mlx);
	free(game.map);
	free(game.map_info);
	exit(0);

}
