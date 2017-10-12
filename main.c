#include "corewar.h"

int ft_exit(char *str)
{
	perror(str);
	exit(0);
}

void for_test(t_arg *ptr)
{
	int i;

	i = 0;
	while (i < ptr->cnt_player)
	{
		printf("name->%s", ptr->player[i]->name);
		printf("comment->%s", ptr->player[i]->name);

		ptr->player[i]->num = 0;
		ptr->player[i]->fd = 0;
		ptr->player[i]->size_code = 0;
		i++;
	}
}

int main(int argc, char **argv)
{
	t_arg *ptr;

	if(argc == 1)
		ft_exit("Don't have arg!");
	ptr = vm_valid(argc, argv);
	for_test(ptr);
	if (ptr->visual == 1)// turn on visual
	{
		start_draw(ptr);
		end_draw();
	}
	return 0;
}