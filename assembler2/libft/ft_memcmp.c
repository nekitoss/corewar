/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 17:47:51 by yrobotko          #+#    #+#             */
/*   Updated: 2016/11/30 16:14:51 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *p1;
	const unsigned char *p2;

	if (n != 0)
	{
		p1 = s1;
		p2 = s2;
		while (n-- != 0)
			if (*p1++ != *p2++)
				return (*--p1 - *--p2);
	}
	return (0);
}
