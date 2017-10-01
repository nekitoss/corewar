/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 15:38:31 by rhulam            #+#    #+#             */
/*   Updated: 2017/04/30 16:29:27 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <locale.h>
# include <wchar.h>
# include <inttypes.h>
# include <stdint.h>
# include <limits.h>
# include "../libft.h"

typedef struct	s_format
{
	char		flag;
	int			width;
	int			precision;
	char		modifier;
	int			mod_count;
	char		type;
	char		sign;
	int			space;
	int			nul;
	int			plus;
}				t_format;

int				ft_printf(const char *format, ...);
void			form_init(t_format *list);
char			*fill_list(char *format, va_list *ar, t_format *list);
void			compare(va_list *ar, t_format *list);
int				is_type(char c);
int				is_flag(char c);
int				is_width(char c);
int				is_precision(char c);
int				is_modifier(char c);
char			*do_flag(char *format, t_format *list);
char			*do_width(char *format, t_format *list, va_list *ar);
char			*do_presicion(char *format, t_format *list, va_list *ar);
char			*do_modifier(char *format, t_format *list);
void			do_type(char c, t_format *list);
void			print_s(va_list *ar, t_format *list);
void			print_str(char *s);
int				convert(wint_t c, int j, int v);
void			print_d(va_list *ar, t_format *list);
void			print_o(va_list *ar, t_format *list);
char			*ft_itoa_ubase(uintmax_t i, int base, int flag);
void			print_u(va_list *ar, t_format *list);
void			print_x(va_list *ar, t_format *list);
size_t			ft_wcslen(const wchar_t *s);
void			print_c(va_list *ar, t_format *list);
void			print_p(va_list *ar, t_format *list);
void			print_f(va_list *ar, t_format *lis);
void			ft_putchar(char c);
void			print_per(t_format *list);
char			*not_valid(t_format *list, char *format);
char			*ft_alloc(int len);
int				zero(va_list *ar);
int				convert_count(wchar_t c);
void			arrs(t_format *list, char *s);
intmax_t		typecheck(intmax_t i, t_format *list);
char			*fta(char *s, int n);

#endif
