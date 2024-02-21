/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:59:14 by jaju              #+#    #+#             */
/*   Updated: 2023/08/07 20:29:25 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "libft/libft.h"
#include <stdlib.h>

typedef unsigned int	t_byte;

void	resize(t_list *this, int new_size);

void	list_init(t_list *this)
{
	this->length = 0;
	this->capacity = 8;
	this->data = allocate(this->capacity * sizeof(void *));
}

void	list_add(t_list *this, void *element)
{
	if (this->length == this->capacity)
		resize(this, this->capacity * 2);
	this->data[this->length++] = element;
}

void	*list_get(t_list const *this, int i)
{
	if (i < 0 || i >= this->length)
		return ((void *)0);
	return (this->data[i]);
}

void	*list_remove(t_list *this, int idx)
{
	void*const	data = list_get(this, idx);
	int			i;

	if (idx < 0 || idx >= this->length)
		ft_panic("list_remove: Index out of bounds!");
	i = idx;
	while (i < this->length)
	{
		this->data[i] = this->data[i + 1];
		i++;
	}
	this->length--;
	return (data);
}
