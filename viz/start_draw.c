#include "viz.h"

void    draw_big(int y, int x, int x_s)
{
    int     i;

    i = 0;
    while (i < x)
        mvprintw(0, i++, "*");
    i = 0;
    while (i < x)
        mvprintw(y - 1, i++, "*");
    i = 0;
    while (i < y)
        mvprintw(i++, 0, "*");
    i = 0;
    while (i < y)
        mvprintw(i++, x - 1, "*");
    i = 0;
    while (i < y)
        mvprintw(i++, x_s - 1, "*");
}

void    draw_frame(void)
{
    start_color();
    use_default_colors();
    init_pair(1, COLOR_MAGENTA, COLOR_MAGENTA);
    attron(COLOR_PAIR(1));
    draw_big(y, x_b, x_s);
    attroff(COLOR_PAIR(1));
}

void    initial_values(void)
{
    draw_frame();
    //fill_memory();
    attron(A_BOLD);
    mvprintw(4, x_s + 2, "Cycles/second limit : ");
    mvprintw(7, x_s + 2, "Cycle : ");
    mvprintw(9, x_s + 2, "Processes : ");
    mvprintw(11, x_s + 2, "All lives : ");
    attroff(A_BOLD);
}

void    start_draw(t_core *core)
{
    signal(SIGINT, stop_and_exit);
    system("afplay song.mp3 &");
    y = 68;
    x_s = 197;
    x_b = 264;
    t_arg *list = core->args;
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, true);
    nodelay(stdscr, true);
    n_pause();
    initial_values();
    set_cycles_per_second(0);
    set_cycle(0);
    set_processes(core->num_of_processes);
    set_all_lives(0);
    bots_draw(list);
    attron(A_BOLD);
    mvprintw(pos + 2, x_s + 2, "Live breakdown for current period : ");
    mvprintw(pos + 5, x_s + 2, "Live breakdown for last period : ");
    attroff(A_BOLD);
    set_current_breakdown(0, 0, 0, 0);
    set_last_breakdown(0, 0, 0, 0);
    attron(A_BOLD);
    draw_constants();
    attroff(A_BOLD);
	init_color(COLOR_YELLOW, 510, 510, 510);
    init_pair(10, COLOR_WHITE, COLOR_GREEN);
    init_pair(11, COLOR_WHITE, COLOR_BLUE);
    init_pair(12, COLOR_WHITE, COLOR_RED);
    init_pair(13, COLOR_WHITE, COLOR_CYAN);
	init_pair(7, COLOR_YELLOW, COLOR_BLACK);
    draw_field(core);
    draw_carriage(core);
    refresh();
}
