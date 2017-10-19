#include "viz.h"

void    set_current_breakdown(int a, int b, int c, int d)
{
    int     first;
    int     second;
    int     third;
    int     fourth;
    int     i;

    i = 1;
    mvprintw(pos + 3, x_s + 2, "[");
    mvprintw(pos + 3, x_s + 2 + 61, "]");
    if (!a && !b && !c && !d)
    {
        while (i <= 60)
            mvprintw(pos + 3, x_s + 2 + i++, "-");
        return ;
    }
    first = (float)a / ((a + b + c + d) == 0 ? 1 : (a + b + c + d)) * 60 + 0.5;
    second = (float)b / ((a + b + c + d) == 0 ? 1 : (a + b + c + d)) * 60 + 0.5;
    third = (float)c / ((a + b + c + d) == 0 ? 1 : (a + b + c + d)) * 60 + 0.5;
    if (d)
        fourth = 60 - (first + second + third);
    else
        fourth = 0;
    while (first)
    {
        attron(COLOR_PAIR(2));
        mvprintw(pos + 3, x_s + 2 + i++, "-");
        attroff(COLOR_PAIR(2));
        first--;
    }
    while (second)
    {
        attron(COLOR_PAIR(3));
        mvprintw(pos + 3, x_s + 2 + i++, "-");
        attroff(COLOR_PAIR(3));
        second--;
    }
    while (third)
    {
        attron(COLOR_PAIR(4));
        mvprintw(pos + 3, x_s + 2 + i++, "-");
        attroff(COLOR_PAIR(4));
        third--;
    }
    while (fourth)
    {
        attron(COLOR_PAIR(5));
        mvprintw(pos + 3, x_s + 2 + i++, "-");
        attroff(COLOR_PAIR(5));
        fourth--;
    }
    refresh();
}

void    set_last_breakdown(int a, int b, int c, int d)
{
    int     first;
    int     second;
    int     third;
    int     fourth;
    int     i;

    i = 1;
    mvprintw(pos + 6, x_s + 2, "[");
    mvprintw(pos + 6, x_s + 2 + 61, "]");
    if (!a && !b && !c && !d)
    {
        while (i <= 60)
            mvprintw(pos + 6, x_s + 2 + i++, "-");
        return ;
    }
    first = (float)a / ((a + b + c + d) == 0 ? 1 : (a + b + c + d)) * 60 + 0.5;
    second = (float)b / ((a + b + c + d) == 0 ? 1 : (a + b + c + d)) * 60 + 0.5;
    third = (float)c / ((a + b + c + d) == 0 ? 1 : (a + b + c + d)) * 60 + 0.5;
    if (d)
        fourth = 60 - (first + second + third);
    else
        fourth = 0;
    while (first)
    {
        attron(COLOR_PAIR(2));
        mvprintw(pos + 6, x_s + 2 + i++, "-");
        attroff(COLOR_PAIR(2));
        first--;
    }
    while (second)
    {
        attron(COLOR_PAIR(3));
        mvprintw(pos + 6, x_s + 2 + i++, "-");
        attroff(COLOR_PAIR(3));
        second--;
    }
    while (third)
    {
        attron(COLOR_PAIR(4));
        mvprintw(pos + 6, x_s + 2 + i++, "-");
        attroff(COLOR_PAIR(4));
        third--;
    }
    while (fourth)
    {
        attron(COLOR_PAIR(5));
        mvprintw(pos + 6, x_s + 2 + i++, "-");
        attroff(COLOR_PAIR(5));
        fourth--;
    }
    refresh();
}

void    set_cycle_to_die(int n)
{
    attron(A_BOLD);
    mvprintw(pos + 8, x_s + 2 + 15, "%d               ", n);
    attroff(A_BOLD);
    refresh();
}