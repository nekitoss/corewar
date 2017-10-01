/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 13:17:47 by rhulam            #+#    #+#             */
/*   Updated: 2016/11/22 13:37:46 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char *p = s;

	if (n)
	{
		while (n)
		{
			if (*p++ == (unsigned char)c)
			{
				return ((void *)(p - 1));
			}
			n--;
		}
	}
	return (NULL);
}
