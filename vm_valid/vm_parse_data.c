
#include "../corewar.h"

int		valid_val_arg(char *argv, int fl_dump)
{
	int i;
	int fl;

	fl = 0;
	i = 0;
	while (argv[i] != '\0')
	{
		if (ft_isdigit(argv[i]))
		{
			if (argv[i] == '0' && fl == 0)
			{
				i++;
				continue;
			}
			fl = 1;
		}
		else
			return (1);
		i++;
	}
	if (fl == 0 && fl_dump == 0)
		ft_exit("Error: number must be content at "
		"least one digit, but not zero, my friend, it's not 'Go')\n");
	else if (fl == 0 && fl_dump == 1)
		ft_putstr("Warning: It's not comfortable for your eyes)\n");
	return (0);
}

void	hndl_cmd_arg_n(char **argv, t_arg *ptr)
{
	int i;

	i = 0;
	while (i < ptr->cnt_arg)
	{
		if (!ft_strcmp("-n",argv[i]))
		{
			if ((i + 1) < ptr->cnt_arg)
			{
				if (valid_val_arg(argv[(i + 1)], 0))
					ft_exit("Error: not valid arg, my friend\n");
				if (ft_strlen(argv[(i + 1)]) > 10)
					ft_exit("Error: too big number, my friend\n");
			}
			else
				ft_exit("Error: incorrect value of number player\n");
		}
		i++;
	}
}

int		hndl_cmd_arg_dump(char **argv, t_arg *ptr, char *str)
{
	int i;
	size_t num;

	i = 1;
	while (i < ptr->cnt_arg)
	{
		if (!ft_strcmp(str, argv[i]))
		{
			if (i + 1 >= ptr->cnt_arg)
				ft_exit("Error: incorrect value of dump\n");
			if (!valid_val_arg(argv[(i + 1)], 1))
			{
				ptr->fl_dump = 1;
				if (ft_strlen(argv[(i + 1)]) > 10)
					ft_exit("Error: too big number, my friend\n");
				num = (size_t)ft_atoi(argv[(i + 1)]);
				if (ft_strcmp(argv[(i + 1)], ft_itoa(num)))
					ft_exit("Error: to big number, my friend\n");
				ptr->num_dump = num;
			}
			else
				ft_exit("Error: incorrect value of dump\n");
		}
		i++;
	}
	return (0);
}

void		vm_valid_arg(int argc, char **argv, t_arg *ptr)
{
	ptr->cnt_arg = argc;
	hndl_cmd_arg_dump(argv, ptr, "-dump");
	hndl_cmd_arg_visual(argv, ptr, "-v");
	hndl_cmd_arg_wide(argv, ptr, "-w");
	hndl_cmd_arg_n(argv, ptr);
	valid_filename(argv, ptr);
	valid_flags(ptr);
	set_num_player(ptr);
}

t_arg	*vm_valid(int argc, char **argv)
{
	t_arg	*ptr;

	vm_init_struct(&ptr);
	vm_valid_arg(argc, argv, ptr);
	vm_init_struct_player(&ptr);
	vm_valid_data_file(ptr);

	return (ptr);
}
