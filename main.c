#include "corewar.h"

int ft_exit(char *str)
{
	if (errno == 1)
		perror(str);
	else
		write(1, str, ft_strlen(str));
	exit(0);
}

void 	ft_exit_name_file(t_player *player, char *str1, char *str2)
{
	write(1, str1, ft_strlen(str1));
	write(1, player->path_player, ft_strlen(player->path_player));
	write(1, str2, ft_strlen(str2));
	exit(0);
}

void for_test(t_arg *ptr)
{
	int i;

	i = 0;
	printf("number of players%i\n", ptr->cnt_player);
	printf("dump flag->%i num->%zu\n", ptr->fl_dump, ptr->num_dump);
	printf("++++++++++++++++++++++++++++++++++++++++++++\n");
	while (i < ptr->cnt_player)
	{
		printf("name->%s\n", ptr->player[i]->name);
		printf("comment->%s\n", ptr->player[i]->comment);
		printf("number->%i\n", ptr->player[i]->num);
		i++;
		printf("\n");
		printf("---------------------%i-----------------------\n", i);
		printf("\n");
	}
}

void	vm_sort_player(t_arg *ptr)
{
	int i;
	int j;
	t_player *tmp_player;

	i = 0;
	while (i < ptr->cnt_player)
	{
		j = i;
		while (j < ptr->cnt_player)
		{
			if (ptr->player[i]->num > ptr->player[j]->num)
			{
				tmp_player = ptr->player[i];
				ptr->player[i] = ptr->player[j];
				ptr->player[j] = tmp_player;
			}
			j++;
		}
		i++;
	}
}

void	vm_show_usage(void)
{
	write(1, "Usage: ./corewar [-dump nbr_cycles] [-w number] [-v] [[-n number] champion1.cor] ...\n", 74);
	write(1, "#### TEXT OUTPUT MODE ##########################################################\n", 81);
	write(1, "-dump N      : Dumps memory after N cycles then exits\n", 54);
	write(1, "-w N         : wide of dumps memory, in octets\n", 48);
	write(1, "#### NCURSES OUTPUT MODE #######################################################\n", 81);
	write(1, "-v           : Ncurses output mode\n", 35);
	write(1, "################################################################################\n", 81);
}

// int main(int argc, char **argv)
// {
// 	t_arg *ptr;

// 	if(argc == 1)
// 		vm_show_usage();
// 	ptr = vm_valid(argc, argv);
// 	vm_sort_player(ptr);

// 	if (ptr->fl_visual == 1)// turn on fl_visual
// 	{
// 		start_draw(ptr);
// 		end_draw();
// 	}
// 	return 0;
// }