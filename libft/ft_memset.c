/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 12:59:30 by rhulam            #+#    #+#             */
/*   Updated: 2016/11/21 17:10:52 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *str, int val, size_t num)
{
	unsigned char *s;

	s = (unsigned char *)str;
	if (num)
	{
		while (num)
		{
			*s++ = val;
			num--;
		}
	}
	return (str);
}
