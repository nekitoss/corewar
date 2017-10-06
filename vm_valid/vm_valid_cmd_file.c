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
	while (argv[i] != '\0')
	{
		ptr++;
 		i++;
	}
	ptr -= 4;
	if (!ft_strcmp(cor, ptr))
		return (0);
	return (1);
}

int		ft_isdigit_str(char *argv)
{
	int i;

	i = 0;
	while (argv[i] != '\0')
	{
		if(!(ft_isdigit(argv[i])))
			return (1);
		i++;
	}
	return (0);
}

int		sv_number_player(char *argv, t_arg *ptr)
{
	int tmp;
	char *tmp2;

	if (ft_isdigit_str(argv))
		ft_exit("Not correct value");
	tmp = ft_atoi(argv);
    tmp2 = ft_itoa(tmp);
    if ((ft_strcmp(tmp2, argv)))
                return (1);
	ptr->num[ptr->cnt_player] = tmp;
	return (0);
}

void 	sv_path_player(char *argv, t_arg *ptr)
{
	if (ptr->cnt_player == 0)
		ptr->path_p1 = ft_strdup(argv);
	if (ptr->cnt_player == 1)
		ptr->path_p2 = ft_strdup(argv);
	if (ptr->cnt_player == 2)
		ptr->path_p3 = ft_strdup(argv);
	if (ptr->cnt_player == 3)
		ptr->path_p4 = ft_strdup(argv);
	if (ptr->cnt_player > 3)
		ft_exit("to many bots");
	ptr->cnt_player++;
	ptr->nm_f = 1;

}


int		hndl_valid_file(char **argv, t_arg *ptr)
{
	int i;
	while (argv[i] != NULL)
	{
		ft_printf("%s ", argv[i]);
		i++;
	}
	if (valid_filename(argv, ptr))
		return (1);
	return (0);
}

