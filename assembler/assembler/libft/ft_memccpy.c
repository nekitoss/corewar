/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 17:54:20 by yrobotko          #+#    #+#             */
/*   Updated: 2016/12/08 20:16:32 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	count;

	count = 0;
	if (n != 0)
	{
		while (count < n)
		{
			((char*)dst)[count] = ((char*)src)[count];
			if (((char*)src)[count] == (char)c)
				return (dst + count + 1);
			count++;
		}
	}
	return (0);
}
