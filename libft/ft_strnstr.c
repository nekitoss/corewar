/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 13:01:13 by rhulam            #+#    #+#             */
/*   Updated: 2016/11/25 18:08:31 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	const char		*s1;
	const char		*s2;
	size_t			i;
	size_t			j;

	i = 0;
	if (!*little)
		return ((char *)big);
	while (*big && i < len)
	{
		s1 = big;
		s2 = little;
		j = i;
		while (*s1 && *s2 && !(*s1 - *s2) && j < len)
		{
			s1++;
			s2++;
			j++;
		}
		if (!*s2)
			return ((char *)big);
		big++;
		i++;
	}
	return (NULL);
}
