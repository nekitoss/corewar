/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 17:38:55 by rhulam            #+#    #+#             */
/*   Updated: 2016/11/26 14:07:07 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*s1;
	char	*s2;

	if (n)
	{
		s1 = (char *)dst;
		s2 = (char *)src;
		if (s2 < s1)
		{
			s1 += n;
			s2 += n;
			while (n)
			{
				*--s1 = *--s2;
				n--;
			}
		}
		else
		{
			while (n--)
				*s1++ = *s2++;
		}
	}
	return (dst);
}
