/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 12:49:46 by rhulam            #+#    #+#             */
/*   Updated: 2016/12/01 14:57:37 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*temp1;
	unsigned char	*temp2;

	temp1 = (unsigned char *)s1;
	temp2 = (unsigned char *)s2;
	while (*temp1 == *temp2 && temp1 != '\0' && *temp2 != '\0')
	{
		temp1++;
		temp2++;
	}
	if (*temp1 != *temp2)
		return (*temp1 - *temp2);
	else
		return (0);
}
