/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 16:35:20 by yrobotko          #+#    #+#             */
/*   Updated: 2016/12/04 16:33:29 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

void	*ft_memset(void *p, int c, size_t len)
{
	char	*ptr;
	size_t	counter;

	ptr = (char *)p;
	counter = 0;
	while (counter < len)
	{
		ptr[counter] = (char)c;
		counter++;
	}
	return (p);
}
