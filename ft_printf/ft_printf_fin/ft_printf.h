/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:55:37 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/05/19 14:21:41 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);
int		ft_printf_second(va_list vl, const char *str, int *count_num);
int		check_percent(const char *str, int i, va_list vl);
int		output_char(va_list vl);
int		output_string(va_list vl);
//int		output_address_2(unsigned long long output, int *len);
int	output_address_2(unsigned int output, int *len);
int		output_address(va_list vl);
int		output_int_2(int output, int *len);
int		output_int(va_list vl);
int		output_unsignedint2(unsigned int output, int *len);
int		output_unsignedint(va_list vl);
int		output_six_smlletter(unsigned int output, int *len);
int		output_six_bigletter(unsigned int output, int *len);
int		output_six(va_list vl, char check);

#endif