/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 12:52:34 by rhulam            #+#    #+#             */
/*   Updated: 2016/12/01 16:07:25 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*temp1;
	unsigned char	*temp2;

	i = 0;
	temp1 = (unsigned char *)s1;
	temp2 = (unsigned char *)s2;
	while (temp1[i] != '\0' && temp2[i] != '\0' && i < n)
	{
		if (temp1[i] == temp2[i])
		{
			if (i + 1 < n)
				i++;
			else
				break ;
		}
		else
			break ;
	}
	return (temp1[i] - temp2[i]);
}
