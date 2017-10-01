/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 11:12:01 by rhulam            #+#    #+#             */
/*   Updated: 2016/12/01 16:41:06 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	trim(char const *s, int *i, int *j)
{
	while (s[*i] == ' ' || s[*i] == '\n' || s[*i] == '\t')
		++*i;
	while (s[*j] == ' ' || s[*j] == '\n' || s[*j] == '\t')
		--*j;
}

char		*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
		i++;
	j = i - 1;
	i = 0;
	trim(s, &i, &j);
	if (i < j)
		str = malloc(j - i + 2);
	else
		str = malloc(1);
	if (!str)
		return (NULL);
	k = 0;
	while (i <= j)
		str[k++] = s[i++];
	str[k] = '\0';
	return (str);
}
