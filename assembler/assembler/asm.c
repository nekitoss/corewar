/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 14:17:46 by yrobotko          #+#    #+#             */
/*   Updated: 2017/10/16 14:18:38 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int main(int argc, char **argv)
{
	int			fd;
	char		*file;
	t_asm		*mstruc;

	if (argc <= 1)
		error("No filename. Usage: ./asm filename.");
	fd = check_file_name(argv[argc - 1]);
	file = read_file(fd);
	mstruc = new_struct();
	mstruc->head = new_head();
	mstruc->labels->byte_num = -1;
	mstruc->commands->command_name = ft_strdup("start");
	valid_code(mstruc, file, mstruc->head);

	t_commands *c;
	c = mstruc->commands;
	check_lb(mstruc->commands, mstruc->labels);
	make_corfile(mstruc, mstruc->commands, mstruc->labels, argv[argc - 1]);
	close(fd);
	return 0;
}
