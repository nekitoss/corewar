/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_valid_cmd_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 20:18:16 by mkurchin          #+#    #+#             */
/*   Updated: 2017/10/02 20:18:17 by mkurchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

int		find_ext_to_end(char *argv)
{
	int		i;
	char	*ptr;
	char	*cor;

	i = 0;
	cor = ".cor";
	ptr = argv;
	if ((ft_strlen(argv)) < 4)
		return (1);
	while (argv[i] != NULL)
	{
		ptr++;
 		i++;
	}
	ptr -= 4;
	if (!ft_strcmp(cor, ptr))
		return (0);
	return (1);
}

int		valid_filename(char **argv, t_arg *ptr)
{
	int i;

	i = 0;
	while (i < ptr->cnt_arg)
	{
		if (argv[(ptr->cnt_arg - 1)][0] != '.' && !find_ext_to_end(argv[(ptr->cnt_arg - 1)]))
		{
			ptr->nm_f = i;
		}
		i++;
	}
	return (1);
}
int		hndl_valid_file(int argc, char **argv, t_arg *ptr, char *str)
{

	if (valid_filename(argv, ptr))
		return (1);
}

