/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 13:59:11 by rhulam            #+#    #+#             */
/*   Updated: 2016/12/05 12:25:29 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*s;
	size_t	i;

	s = (char*)malloc(sizeof(char) * size + 1);
	i = 0;
	if (s == NULL)
		return (NULL);
	while (i <= size)
	{
		s[i] = '\0';
		i++;
	}
	s[i] = '\0';
	return (s);
}
