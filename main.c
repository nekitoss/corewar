#include "corewar.h"

int ft_exit(char *str)
{
	perror(str);
	exit(0);
}



int main(int argc, char **argv)
{
	if(argc == 1)
		ft_exit("Don't have arg!");
	vm_valid(argc, argv);

 	//test();
	return 0;
}