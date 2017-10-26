#include "viz.h"

void    fill_memory(void)
{
    int     x;
    int     y;
    int     i;

    y = 2;
    i = 0;
    while (y < 66)
    {
        x = 3;
        i = 0;
        while (x < 194)
        {
            if (i == 2)
            {
                mvprintw(y, x, " ");
                i = 0;
            }
            else
            {
                i++;
                mvprintw(y, x, "0");
            }
            x++;
        }
        y++;
    }
}

void    draw_constants(void)
{
    mvprintw(pos + 8, x_s + 2, "CYCLE_TO_DIE : %d", CYCLE_TO_DIE);
    mvprintw(pos + 10, x_s + 2, "CYCLE_DELTA : %d", CYCLE_DELTA);

    mvprintw(pos + 12, x_s + 2, "NBR_LIVE : %d", NBR_LIVE);
    mvprintw(pos + 14, x_s + 2, "MAX_CHECKS : %d", MAX_CHECKS);
}

void    set_all_lives(int n)
{
    attron(A_BOLD);
    mvprintw(11, x_s + 2 + 12, "%d            ", n);
    attroff(A_BOLD);
    refresh();
}