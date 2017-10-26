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

void    end_draw(t_player *player)
{
    attron(A_BOLD);
    attron(COLOR_PAIR(player->num * -1 + 1));
    mvprintw(64, x_s + 2, "The winner is: player %d, \"%s\"", player->num * -1, player->name);
    attroff(COLOR_PAIR(player->num * -1 + 1));
    mvprintw(65, x_s + 2, "Press any key to exit");
    attroff(A_BOLD);
    nodelay(stdscr, false);
    getch();
    // system("killall afplay");
    endwin();
}