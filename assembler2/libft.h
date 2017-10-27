/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 16:51:21 by yrobotko          #+#    #+#             */
/*   Updated: 2017/08/24 18:31:46 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFF_SIZE 32

# include "string.h"
# include "string.h"
# include "stdlib.h"
# include "unistd.h"
# include <inttypes.h>
# include <wchar.h>
# include <stdarg.h>

typedef struct			s_gnl
{
	char				*buff;
	int					fdiscriptor;
	struct s_gnl		*next;
}						t_gnl;

typedef struct			s_list
{
	void				*content;
	size_t				content_size;
	struct s_list		*next;
}						t_list;

typedef struct			s_print
{
	char				*flags;
	int					width;
	int					precision;
	int					size;
	char				convers;
	int					prec_fl;
	int					star;
}						t_print;

typedef struct			s_print_list
{
	t_print				*lst;
	struct s_print_list	*next;
}						t_print_list;

char					*newstr(int n, char s);
t_print					*new_struc();
t_print_list			*new_struc_list();
char					*up_or(int up);
char					*ft_itoa_base(uintmax_t value, int base, int up);
char					*ft_uitoa(uintmax_t value);
int						parse_star(char *str);
int						print_some(char **str);
void					pass_some(char **str);
char					is_convers(char c, char *str);
void					pass_this(char **str);
char					*parse_flags(char *str);
int						parse_width(char *str);
int						parse_precision(char *str, t_print **l);
int						parse_size(char *str);
char					parse_convers(char *str);
t_print					*do_parse(char **str);
t_print_list			*parse_this(char **str);
int						app_flags_ddi(int size, char *strn, char l,
		t_print *ls);
int						app_flags_ddi2(int size, char *strn, char l,
		t_print *ls);
int						apply_w_p_ddi(t_print *lst, char *strnum, char lb);
int						apply_w_p_ddi2(t_print *lst, char *strnum, char lb,
		char *str);
int						next_step_for_ddi(t_print *list, va_list ptr);
int						app_flags_uu(int size, char *strn, t_print *ls);
int						apply_w_p_uu(t_print *lst, char *strnum);
int						next_step_for_uu(t_print *list, va_list ptr);
void					ft_putstr_my(char *str, size_t num, char st);
int						app_flags_cc(int size, char *strn, t_print *ls,
		char st);
int						apply_w_p_cc(t_print *lst, char st);
int						next_step_for_cc(t_print *list, va_list ptr);
int						wchar_strlen(wchar_t *s);
char					*make_norm_str(wchar_t *str);
int						app_flags_ss(int size, char *strn, t_print *ls);
int						apply_w_p_ss(t_print *lst, char *st);
int						next_step_for_ss(t_print *list, va_list ptr);
int						app_flags_oo(int size, char *strn, t_print *ls);
int						app_flags_oo2(int size, char *strn, t_print *ls,
		int size1);
int						apply_w_p_oo(t_print *lst, char *strnum);
int						next_step_for_oo(t_print *list, va_list ptr);
int						app_flags_xx(int size, char *strn, t_print *ls,
		int size2);
int						app_flags_xx2(int size, char *strn, t_print *ls,
		int size1);
int						apply_w_p_xx(t_print *lst, char *strnum);
int						next_step_for_x(t_print *list, va_list ptr);
int						next_step_for_xx(t_print *list, va_list ptr);
int						app_flags_p(int size, char *strn, t_print *ls);
int						next_step_for_p(t_print *list, va_list ptr);
int						next_step_for_p2(t_print *list,
		char *str, int sn);
int						print_param(t_print *list, va_list ptr);
int						ft_printf(char *tmp_format, ...);
int						get_next_line(const int fd, char **line);
void					ft_bzero(void *s, size_t n);
void					*ft_memset(void *p, int c, size_t len);
void					*ft_memcpy(void *dst, const void *src, size_t len);
size_t					ft_strlen(const char *s);
char					*ft_strdup(const char *str);
void					*ft_memmove(void *dst, const void *src, size_t len);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
void					*ft_memchr(const void *s, int c, size_t n);
void					*ft_memccpy(void *lst, const void *src, int c,
		size_t n);
char					*ft_strcpy(char *dst, const char *src);
char					*ft_strcat(char *s1, const char *s2);
char					*ft_strncat(char *s1, const char *s2, size_t len);
char					*ft_strncpy(char *dst, const char *src, size_t len);
size_t					ft_strlcat(char *dst, const char*src, size_t size);
char					*ft_strchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);
char					*ft_strstr(const char *big, const char *little);
char					*ft_strnstr(const char *big, const char *little,
		size_t len);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_atoi(const char *str);
int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isalnum(int c);
int						ft_isascii(int c);
int						ft_isprint(int c);
int						ft_toupper(int c);
int						ft_tolower(int c);
void					ft_memdel(void **ap);
void					*ft_memalloc(size_t size);
char					*ft_strnew(size_t size);
void					ft_strdel(char **as);
void					ft_strclr(char *c);
void					ft_striter(char *s, void (*f)(char *));
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
char					*ft_strmap(char const *s, char (*f)(char));
char					*ft_strmapi(char const *s, char (*f)(unsigned int,
		char));
int						ft_strequ(char const *s1, char const *s2);
int						ft_strnequ(char const *s1, char const *s2, size_t n);
char					*ft_strsub(char const *s, unsigned int start,
		size_t len);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strtrim(char const *s);
int						ft_isspace(char c);
char					**ft_strsplit(char const *s, char c);
char					*ft_itoa(intmax_t value);
void					ft_putnbr(int n);
void					ft_putchar(char c);
void					ft_putstr(char const *s);
void					ft_putendl(char const *s);
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char const *s, int fd);
void					ft_putnbr_fd(int n, int fd);
void					ft_putendl_fd(char const *s, int fd);
t_list					*ft_lstnew(void const *content, size_t content_size);
void					ft_lstdelone(t_list **alst, void(*del)(void *, size_t));
void					ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void					ft_lstadd(t_list **alst, t_list *new);
void					ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list					*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int						ft_islow(int c);
int						ft_isnull(void *c);
int						ft_isup(int c);
void					ft_lstpushback(t_list *list, void *data, size_t size);
#endif
