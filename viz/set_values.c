#include "viz.h"

void    set_cycles_per_second(int n)
{
    attron(A_BOLD);
    mvprintw(4, x_s + 2 + 22, "%d          ", n);
    attroff(A_BOLD);
    refresh();
}

void    set_cycle(int n)
{
    attron(A_BOLD);
    mvprintw(7, x_s + 2 + 8, "%d", n);
    attroff(A_BOLD);
    refresh();
}

void    set_processes(int n)
{
    attron(A_BOLD);
    mvprintw(9, x_s + 2 + 12, "%d           ", n);
    attroff(A_BOLD);
    refresh();
}

void    set_last_alive(int bot, int cycle)
{
    int     pos;

    pos = 14 + (4 * (bot - 1));
    attron(A_BOLD);
    mvprintw(pos, x_s + 4 + 29, "%d", cycle);
    attroff(A_BOLD);
    refresh();
}

void    set_live_in_current(int bot, int n)
{
    int     pos;

    pos = 15 + (4 * (bot - 1));
    attron(A_BOLD);
    mvprintw(pos, x_s + 4 + 29, "%d              ", n);
    attroff(A_BOLD);
    refresh();
}