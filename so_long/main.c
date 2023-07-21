/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:25:53 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/21 18:08:34 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

# define X_EVENT_KEY_PRESS			2
# define X_EVENT_KEY_RELEASE		3

# define KEY_ESC		53
# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2

typedef struct s_param{
	int		x;
	int		y;
}				t_param;

void			param_init(t_param *param)
{
	param->x = 3;
	param->y = 4;
}


int				key_press(int keycode, t_param *param)
{
	static int a = 0;

	if (keycode == KEY_W)
		param->y++;
	else if (keycode == KEY_S)
		param->y--;
	else if (keycode == KEY_A)
		param->x--;
	else if (keycode == KEY_D)
		param->x++;
	else if (keycode == KEY_ESC)
		exit(0);
	printf("x: %d, y: %d\n", param->x, param->y);
	return (0);
}


int main()
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_param		param;

	param_init(&param);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "mlx 42");
	mlx_hook(win_ptr, X_EVENT_KEY_RELEASE, 0, &key_press, &param);
	mlx_loop(mlx_ptr);
}
