/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 16:48:29 by yrobotko          #+#    #+#             */
/*   Updated: 2016/12/15 21:19:41 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	size_t	n;
	void	*area;

	area = (void*)malloc(sizeof(void) * size);
	if (area)
	{
		n = 0;
		while (n < size)
			((char*)area)[n++] = 0;
	}
	return (area);
}
