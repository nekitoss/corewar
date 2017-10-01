/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 16:09:01 by rhulam            #+#    #+#             */
/*   Updated: 2016/11/22 16:21:19 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncat(char *restrict s1, const char *restrict s2, size_t n)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (n)
	{
		while (s1[i] != '\0')
			i++;
		while (s2[j] != '\0' && n > 0)
		{
			s1[i + j] = s2[j];
			j++;
			n--;
		}
		s1[i + j] = '\0';
	}
	return (s1);
}
