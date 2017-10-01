/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 17:37:27 by rhulam            #+#    #+#             */
/*   Updated: 2016/11/26 13:46:44 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *restrict dst, const void *restrict src, int c,
		size_t n)
{
	char	*s1;
	char	*s2;
	int		i;

	s1 = (char *)dst;
	s2 = (char *)src;
	i = 0;
	if (n)
	{
		while (n)
		{
			s1[i] = s2[i];
			if (s2[i] == c)
				return (&s1[i + 1]);
			n--;
			i++;
		}
	}
	return (NULL);
}
