/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 16:12:35 by yrobotko          #+#    #+#             */
/*   Updated: 2016/12/09 16:43:55 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
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
			str[i] = f(i, *s);
			s++;
			i++;
		}
	return (str);
}
