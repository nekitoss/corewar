#include "corewar.h"

int ft_exit(char *str)
{
	perror(str);
	exit(0);
}



int main(int argc, char **argv)
{
	t_arg *ptr;

	if(argc == 1)
		ft_exit("Don't have arg!");
	ptr = vm_valid(argc, argv);
	if (ptr->visual == 1)// turn on visual
	{
		start_draw(ptr);
		end_draw();
	}
	//test();
	return 0;
}