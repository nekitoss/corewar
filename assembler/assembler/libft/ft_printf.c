/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 18:39:34 by yrobotko          #+#    #+#             */
/*   Updated: 2017/08/13 19:04:27 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_print_list		*parse_this(char **str)
{
	t_print_list	*ret_lst;
	t_print_list	*curr_lst;

	ret_lst = new_struc_list();
	curr_lst = ret_lst;
	while (**str && **str != '\n')
	{
		curr_lst->lst = do_parse(str);
		curr_lst->next = new_struc_list();
		curr_lst = curr_lst->next;
	}
	return (ret_lst);
}

int					print_param(t_print *list, va_list ptr)
{
	if (list->convers == 'd' || list->convers == 'i' || list->convers == 'D')
		return (next_step_for_ddi(list, ptr));
	if (list->convers == 'u' || list->convers == 'U')
		return (next_step_for_uu(list, ptr));
	if (list->convers == 'c' || list->convers == 'C')
		return (next_step_for_cc(list, ptr));
	if (list->convers == 's' || list->convers == 'S')
		return (next_step_for_ss(list, ptr));
	if (list->convers == 'o' || list->convers == 'O')
		return (next_step_for_oo(list, ptr));
	if (list->convers == 'x' || list->convers == 'X')
		return (next_step_for_xx(list, ptr));
	if (list->convers == 'p')
		return (next_step_for_p(list, ptr));
	return (0);
}

int					ft_printf(char *tmp_format, ...)
{
	va_list			arg_ptr;
	char			*ptr;
	int				ret_sum;
	t_print_list	*start_struc;

	ret_sum = 0;
	ptr = ft_strdup(tmp_format);
	pass_some(&tmp_format);
	va_start(arg_ptr, tmp_format);
	start_struc = parse_this(&tmp_format);
	if (start_struc->lst->star == 666)
		return (0);
	while (start_struc)
	{
		ret_sum += print_some(&ptr);
		ret_sum += print_param(start_struc->lst, arg_ptr);
		pass_this(&ptr);
		start_struc = start_struc->next;
	}
	va_end(arg_ptr);
	return (ret_sum);
}
