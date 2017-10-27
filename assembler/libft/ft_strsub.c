/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 17:25:02 by yrobotko          #+#    #+#             */
/*   Updated: 2016/12/09 17:16:41 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	i = 0;
	if ((substr = (char*)malloc(sizeof(char) * (len + 1))) && s)
	{
		while (i < len)
		{
			substr[i] = s[start + i];
			i++;
		}
		substr[i] = 0;
	}
	return (substr);
}
