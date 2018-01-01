/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 18:42:31 by yrobotko          #+#    #+#             */
/*   Updated: 2016/12/15 20:25:24 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	fillstr(char *dst, char const *str, size_t from, size_t to)
{
	size_t	a;

	a = 0;
	while (from <= to)
		dst[a++] = str[from++];
	dst[a] = '\0';
}

char			*ft_strtrim(char const *s)
{
	char	*str;
	size_t	i;
	size_t	q;

	i = 0;
	if (!s)
		return (0);
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	q = ft_strlen(s) - 1;
	if (i != ft_strlen(s))
	{
		while (s[q] == ' ' || s[q] == '\n' || s[q] == '\t')
			q--;
		str = (char *)malloc(sizeof(char) * (q - i + 2));
	}
	else if ((str = (char*)malloc(sizeof(char) * 1)))
	{
		*str = '\0';
		return (str);
	}
	if (!str)
		return (0);
	fillstr(&str[0], s, i, q);
	return (str);
}
