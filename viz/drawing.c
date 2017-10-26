#include "viz.h"

void    draw_field(t_core *core)
{
    int x = 3;
    int y = 2;
    int i = 0;
    int t;

    while (i < MEM_SIZE)
    {
        t = (int)(core->colors[i]) ? (int)(core->colors[i]) * -1 : 6;
        attron(COLOR_PAIR(t + 1));
        mvprintw(y, x, "%.2x", core->field[i]);
        attroff(COLOR_PAIR(t + 1));
        x += 3;
        if (x >= 195)
        {
            x = 3;
            y++;
        }
        i++;
    }
    refresh();
}

void    get_yx(int *yx, int pc)
{
    int y;
    int x;
    int t;

    y = pc / 64;
    t = pc - 64 * y;
    if (!t)
    {
        yx[0] = y + 2;
        yx[1] = 3;
        return;
    }
    x = t * 2 + t;
    yx[0] = y + 2;
    yx[1] = x + 3;
}

void    draw_carriage(t_core *core)
{
    t_proc *temp;
    int     yx[2];

    temp = core->processes_list;
    while (temp)
    {
        get_yx(yx, temp->pc);
        attron(COLOR_PAIR(temp->belong_to_player * -1 + 9));
        mvprintw(yx[0], yx[1], "%.2x", core->field[temp->pc]);
        attroff(COLOR_PAIR(temp->belong_to_player * -1 + 9));
        refresh();
        temp = temp->next;
    }
}

void    draw_cycle(t_core *core)
{
    int     i;
    int     arr[4];
    int     arr1[4];

    i = 0;
    draw_field(core);
    draw_carriage(core);
    set_cycle(core->cycle);
    set_processes(core->num_of_processes);
    set_all_lives(core->gen_lives_in_current_period);
    while (i < core->num_of_players)
    {
        set_last_alive(i + 1, core->players[i]->last_live);
        set_live_in_current(i + 1, core->players[i]->sum_lives_in_current_period);
        arr[i] = core->players[i]->sum_lives_in_current_period;
        arr1[i] = core->players[i]->sum_lives_in_previous_period;
        i++;
    }
    while (i < 4)
    {
        arr[i] = 0;
        arr1[i] = 0;
        i++;
    }
    set_cycle_to_die(core->cycle_to_die);
    set_current_breakdown(arr[0], arr[1], arr[2], arr[3]);
    set_last_breakdown(arr1[0], arr1[1], arr1[2], arr1[3]);
}

int    draw_paused(int *paused, t_core *core, unsigned int *cs)
{
    int     c;

    while (*paused)
    {
        set_cycles_per_second(*cs);
        c = getch();
        if (c == 32)
        {
            *paused = 0;
            n_run();
            draw_cycle(core);
            return (1);
        }
        else if (c == 115)
        {
            draw_cycle(core);
            return 1;
        }
        else if (c == 119)
            *cs -= (*cs > 1) ? 1 : 0;
        else if (c == 113)
            *cs -= (*cs > 10) ? 10 : 0;
        else if (c == 101)
            *cs += (*cs < 2000) ? 1 : 0;
        else if (c == 114)
            *cs += (*cs < 1991) ? 10 : 0;
        else if (c == 116)
            *cs = 2000;
    }
    return 0;
}

void    drawing(t_core *core)
{
    int c;
    static unsigned int cs = 50;
    static int paused = 1;
    static int first = 1;
    static int counter;

    counter++;
    if (counter < cs / 30 && !(unsigned int)paused)
        return;
    counter = 0;
    if (first)
    {
        first = 0;
        return;
    }
    if (paused)
        if (draw_paused(&paused, core, &cs))
            return;
    c = getch();
    if (c == 32)
    {
        paused = 1;
        n_pause();
        if (draw_paused(&paused, core, &cs))
            return;
    }
    else if (c == 115)
    {
        draw_cycle(core);
        n_pause();
        paused = 1;
        return;
    }
    else if (c == 119)
        cs -= (cs > 1) ? 1 : 0;
    else if (c == 113)
        cs -= (cs > 10) ? 10 : 0;
    else if (c == 101)
        cs += (cs < 2000) ? 1 : 0;
    else if (c == 114)
        cs += (cs < 1991) ? 10 : 0;
    else if (c == 116)
        cs = 2000;
    set_cycles_per_second(cs);
    draw_cycle(core);
    usleep(1000000 / cs);
}
