#include "viz.h"

void    n_run(void)
{
    attron(A_BOLD);
    move(2, x_s + 2);
    printw("** RUNNING **");
    refresh();
    attroff(A_BOLD);
}

void    n_pause(void)
{
    attron(A_BOLD);
    move(2, x_s + 2);
    printw("** PAUSE **  ");
    refresh();
    attroff(A_BOLD);
}

void    end_draw(void)
{
    endwin();
}