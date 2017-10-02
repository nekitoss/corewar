
#include "../corewar.h"

int		valid_val_arg(char *argv)
{
	int i;

	i = 0;
	while(argv[i])
	{
		if(!ft_isdigit(argv[i]))
			return (1);
		i++;
	}
	return (0);
}

void	sv_arg(t_arg *ptr, char *arg, char *val, int i)
{
	if (!ft_strcmp("-dump",arg))
	{
		ptr->nm_d = i;
		ptr->dump = ft_atoi(val);
	}
	else
	{
		ptr->nm_n = i;
		ptr->n = ft_atoi(val);

	}
}

int		hndl_cmd_arg(int argc, char **argv, t_arg *ptr, char *str)
{
	int i;

	i = 0;
	while(i < argc)
	{
		if (!ft_strcmp(str, argv[i]))
		{
			if (++i <= argc)
				if(!valid_val_arg(argv[i]))
				{
					sv_arg(ptr, argv[(i-1)], argv[i], i);
					return (0);
				}
			return (1);
		}
		i++;
	}
	return (1);
}


int		vm_valid(int argc, char **argv)
{
	t_arg *ptr;

	ft_init_struct(&ptr);
	ptr->cnt_arg = argc;
	if(hndl_cmd_arg(argc, argv, ptr, "-dump"))
		ft_exit("Not correct arg1");
	if(hndl_cmd_arg(argc, argv, ptr, "-n"))
		ft_exit("Not correct arg2");
	if(hndl_valid_file(argc, argv, ptr, ".cor"))
		ft_exit("Not correct file");
	return (0);

}