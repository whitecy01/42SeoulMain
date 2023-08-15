/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:19:09 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/08 18:21:15 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_H
# define GET_H


#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

typedef struct timevala
{
    long tv_sec;       // 초
    long tv_usec;      // 마이크로초
}t_time;



#endif