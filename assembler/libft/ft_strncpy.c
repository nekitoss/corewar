/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:39:51 by yrobotko          #+#    #+#             */
/*   Updated: 2016/11/30 16:25:54 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char	*save;

	save = dst;
	while (len > 0 && *src != '\0')
	{
		*save++ = *src++;
		--len;
	}
	while (len-- > 0)
		*save++ = '\0';
	return (dst);
}
