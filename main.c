#include "corewar.h"

int ft_exit(char *str)
{
	if (errno == 1)
		perror(str);
	else
		ft_putstr(str);
	exit(0);
}

void 	ft_exit_name_file(t_player *player, char *str1, char *str2)
{
	ft_putstr(str1);
	ft_putstr(player->path_player);
	ft_putstr(str2);
	exit(0);
}

void for_test(t_arg *ptr)
{
	int i;

	i = 0;
	printf("--->switch off this function in main file, funciton - 'for test(void)'\n\n");
	printf("number of players%i\n", ptr->cnt_player);
	printf("dump flag->%i num->%zu\n", ptr->fl_dump, ptr->num_dump);
	printf("debug flag->%i num->%zu\n", ptr->fl_debug, ptr->num_debug);
	printf("width flag->%i num->%i\n", ptr->fl_width, ptr->width_dump);
	printf("original flag->%i\n", ptr->fl_original);
	printf("music flag->%i\n", ptr->fl_music);
	printf("visual flag->%i\n", ptr->fl_visual);
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
	i = 0;
	while (i < ptr->cnt_player)
	{
		ptr->player[i]->num *= -1;
		i++;
	}
}

void	vm_show_usage(void)
{
	ft_putstr("Usage: ./corewar [-dump nbr_cycles [-w width]] [-debug [number]] [-m] [-v] [-o] [[-n number]"
			" champion1.cor] ...\n\n");
	ft_putstr("#### TEXT OUTPUT MODE ###########################################"
			"###############\n");
	ft_putstr("-dump N      : Dumps memory after N cycles then exits\n");
	ft_putstr("-w N         : wide of dumps memory, in octets\n");
	ft_putstr("-m           : enable music\n");
	ft_putstr("-o           : make corewar like original\n");
	ft_putstr("-n N         : set number of player\n");
	ft_putstr("-debug N     : Verbosity levels, can be added together to enable"
					  " several\n");
	ft_putstr("     - 0 : Show only essentials\n");
	ft_putstr("		- 1 : Show lives\n");
	ft_putstr("		- 2 : Show cycles\n");
	ft_putstr("		- 4 : Show operations (Params are NOT litteral ...)\n");
	ft_putstr("		- 8 : Show deaths\n");
		ft_putstr("#### NCURSES OUTPUT MODE ########################################"
			"###############\n");
	ft_putstr("-v           : Ncurses output mode\n");
	ft_putstr("#################################################################"
			"###############\n");
	exit(0);
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