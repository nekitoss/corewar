/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 16:33:13 by yrobotko          #+#    #+#             */
/*   Updated: 2016/12/08 21:04:21 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	len;
	char	*copy;

	len = ft_strlen(str);
	if (!(copy = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	ft_strcpy(copy, str);
	return (copy);
}
