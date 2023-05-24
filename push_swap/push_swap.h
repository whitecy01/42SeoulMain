/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:09:17 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/05/24 14:23:23 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H


# include <stdlib.h>
# include <unistd.h>

typedef struct s_number
{
	struct s_number	*prev;
	int				content;
	struct s_number	*next;
}	t_number;

typedef struct s_info
{
	int					*array;
	int					size_a;
	int					size_b;
	struct s_number		*top_a;
	struct s_number		*bottom_a;
	struct s_number		*top_b;
	struct s_number		*bottom_b;
}	t_info;

void	print_error(int error);


#endif 