/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:55:37 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/05/16 14:22:51 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

# include <stdio.h>


int	output_char(va_list vl);
int	output_string(va_list vl);
int	output_address(va_list vl);
int	output_int(va_list vl);
int	output_unsignedint(va_list vl);

void output_six_smlletter(unsigned int output);
void output_six_bigletter(unsigned int output);
int	output_six(va_list vl, char check);

int	output_percent(va_list vl);


#endif