/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 15:45:19 by rhulam            #+#    #+#             */
/*   Updated: 2016/12/05 16:11:38 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	unsigned int	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] && i < (unsigned int)n)
	{
		if ((unsigned char)s1[i] - (unsigned char)s2[i])
			return (0);
		i++;
	}
	if ((unsigned char)s1[i] - (unsigned char)s2[i]
		&& (i != (unsigned int)n))
		return (0);
	else
		return (1);
}
