/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 14:51:18 by yrobotko          #+#    #+#             */
/*   Updated: 2016/12/09 17:16:11 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	len;
	size_t	i;
	char	*str;

	if (!s || !f)
		return (0);
	i = 0;
	len = ft_strlen(s);
	if ((str = ft_memalloc(len + 1)))
		while (i < len && *s)
		{
			str[i++] = f(*s);
			s++;
		}
	return (str);
}
