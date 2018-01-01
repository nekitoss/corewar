/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 17:13:17 by yrobotko          #+#    #+#             */
/*   Updated: 2016/12/09 17:11:21 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char *newdst;
	char *newsrc;

	newdst = (char *)dst;
	newsrc = (char *)src;
	if (newdst != newsrc)
	{
		if (newdst > newsrc)
		{
			while (len-- > 0)
				newdst[len] = newsrc[len];
		}
		else
			while (len-- > 0)
				*newdst++ = *newsrc++;
	}
	return (dst);
}
