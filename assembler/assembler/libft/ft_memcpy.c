/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 17:28:52 by yrobotko          #+#    #+#             */
/*   Updated: 2016/11/30 15:36:20 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	char		*d;
	char		*s;

	d = (char *)dst;
	s = (char *)src;
	if (len != 0 && dst != src)
		while (len--)
			*d++ = *s++;
	return (dst);
}
