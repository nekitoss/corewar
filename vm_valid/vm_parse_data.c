
#include "../corewar.h"

int		valid_val_arg(char *argv)
{
	int i;

	i = 0;
	while (argv[i] != NULL)
	{
		if (!ft_isdigit(argv[i]))
			return (1);
		i++;
	}
	return (0);
}

int		hndl_cmd_arg_p(char **argv, t_arg *ptr)
{
	int i;
	int fl_n;
	int cnt_n;

	cnt_n = 0;
	fl_n = 0;
	i = 0;
	while (argv[i] != NULL)
	{
		if (!ft_strcmp("-n",argv[i]))
		{
			if ((i + 1) < ptr->cnt_arg)
			{
				if (!valid_val_arg(argv[(i + 1)]))
				{
					ptr->n = ft_atoi(argv[(i + 1)]);
					cnt_n++;
				}
			}
			else
			{
				ft_exit("Error: not valid arg");
			}
		}
		i++;
	}
	return (cnt_n);
}

int		hndl_cmd_arg_dump(char **argv, t_arg *ptr, char *str)
{
	int i;

	i = 1;
	if (!ft_strcmp(str, argv[i]))
	{
		if (!valid_val_arg(argv[(i + 1)]))
		{
			ptr->dump = ft_atoi(argv[(i + 1)]);
			return (0);
		}
		ft_exit("Error: incorrect val dump");
	}
	return (0);
}

int		vm_valid_arg(int argc, char **argv, t_arg *ptr)
{
	ptr->cnt_arg = argc;
	hndl_cmd_arg_dump(argv, ptr, "-dump");
	hndl_cmd_arg_p(argv, ptr);
	if (hndl_valid_file(argv, ptr))
		ft_exit("Not correct file with bot");
	set_num_player(ptr);
}

int		vm_valid(int argc, char **argv)
{
	t_arg	*ptr;
	char	*line;
	int		fd;

	ft_init_struct(&ptr);
	vm_valid_arg(argc, argv, ptr);
	fd = open(argv[(argc - 1)], O_RDONLY, 0666);
	while (get_next_line(fd, &line) > 0)
	{
		ft_printf("%s\n",line);
		//vm_valid_data_file(line);
	}

	return (0);
}
