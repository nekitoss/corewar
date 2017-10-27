/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 16:33:18 by yrobotko          #+#    #+#             */
/*   Updated: 2016/12/01 19:18:27 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*ptrb;
	char	*ptrl;

	if (*little == 0)
		return ((char*)big);
	i = 0;
	while (*big && i < len)
	{
		ptrb = (char*)big;
		ptrl = (char*)little;
		j = 0;
		while (*ptrb == *ptrl && *ptrl && (i + j) < len)
		{
			ptrb++;
			ptrl++;
			j++;
		}
		if (*ptrl == '\0')
			return ((char*)big);
		big++;
		i++;
	}
	return (0);
}
