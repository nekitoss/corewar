/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 16:13:13 by rhulam            #+#    #+#             */
/*   Updated: 2017/04/17 16:17:12 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned char	*four_bytes(unsigned char *s, wint_t c)
{
	*s++ = (unsigned char)(((c >> 18)) | 0xF0);
	*s++ = (unsigned char)(((c >> 12) & 0x3F) | 0x80);
	*s++ = (unsigned char)(((c >> 6) & 0x3F) | 0x80);
	*s++ = (unsigned char)((c & 0x3F) | 0x80);
	return (s);
}

static unsigned char	*three_bytes(unsigned char *s, wint_t c)
{
	*s++ = (unsigned char)(((c >> 12)) | 0xE0);
	*s++ = (unsigned char)(((c >> 6) & 0x3F) | 0x80);
	*s++ = (unsigned char)((c & 0x3F) | 0x80);
	return (s);
}

static unsigned char	*two_bytes(unsigned char *s, wint_t c)
{
	*s++ = (unsigned char)((c >> 6) | 0xC0);
	*s++ = (unsigned char)((c & 0x3F) | 0x80);
	return (s);
}

static void				prin_char(unsigned char *s)
{
	while (*s)
	{
		ft_putchar(*s);
		s++;
	}
}

int						convert(wint_t c, int j, int v)
{
	static unsigned char	symb[5];
	unsigned char			*s;
	int						i;

	i = 0;
	s = symb;
	if (c < (1 << 7))
		*s++ = (unsigned char)(c);
	else if (c < (1 << 11))
		s = two_bytes(s, c);
	else if (c < (1 << 16))
		s = three_bytes(s, c);
	else if (c < (1 << 21))
		s = four_bytes(s, c);
	*s = '\0';
	while (symb[i] != '\0')
		i++;
	if (i > j && j > -1)
		return (i);
	if (v)
		prin_char(symb);
	return (i);
}
