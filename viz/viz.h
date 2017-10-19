#ifndef NCURSES_VIZ_H
#define NCURSES_VIZ_H

#include "../corewar.h"
#include <curses.h>

/*
 * start_draw(t_arg*) - draws initial map
 * end_draw(void) - free memory and clean the window
 *
 * n_run(void) - runs battle
 * n_pause(void) - pauses battle
 *
 * set_cycles_per_second(int) - changes cycles/second value to n
 * void set_cycle(int n) - sets cycles to n
 * set_processes(int n) - changes processes value to n
 * set_all_lives(int n) - sets all lives value to n
 *
 * set_last_alive(int n, int cycle) - sets last alive value to cycle for n player
 * set_live_in_current(int bot, int n) - sets last alive period value for bot to n
 *
 * set_current_breakdown(int a, int b, int c, int d) - sets current breakdown according to ints
 * set_last_breakdown(int a, int b, int c, int d) - sets last breakdown according to ints
 *
 * set_cycle_to_die(int n) - sets cycle_to_die value to n
 *
 *
 *
 * */

int y;
int x_s;
int x_b;
int colors[4];
int pos;

void    start_draw(t_arg *list);
void    fill_memory(void);
void    n_run(void);
void    n_pause(void);
void    set_cycles_per_second(int n);
void    set_cycle(int n);
void    set_processes(int n);
void    bots_draw(t_arg *list);
void    set_last_alive(int bot, int cycle);
void    set_live_in_current(int bot, int n);
void    set_current_breakdown(int a, int b, int c, int d);
void    set_last_breakdown(int a, int b, int c, int d);
void    draw_constants(void);
void    set_cycle_to_die(int n);
void    end_draw(void);
void    set_all_lives(int n);
void    drawing(t_core *core);

#endif
