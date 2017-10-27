/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 18:12:15 by yrobotko          #+#    #+#             */
/*   Updated: 2016/12/01 16:26:32 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	char *ptrb;
	char *ptrl;

	if (*little == 0)
		return ((char*)big);
	while (*big)
	{
		ptrb = (char*)big;
		ptrl = (char*)little;
		while (*ptrb == *ptrl && *ptrl)
		{
			ptrb++;
			ptrl++;
		}
		if (*ptrl == '\0')
			return ((char*)big);
		big++;
	}
	return (0);
}
