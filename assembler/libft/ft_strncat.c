/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:13:35 by yrobotko          #+#    #+#             */
/*   Updated: 2016/12/11 16:47:35 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t len)
{
	char	*dst;
	char	c;

	if (len != 0)
	{
		dst = s1;
		while (*dst)
			dst++;
		while ((len-- > 0) && ((c = *s2++) != '\0'))
			*dst++ = c;
		*dst = '\0';
	}
	return (s1);
}
