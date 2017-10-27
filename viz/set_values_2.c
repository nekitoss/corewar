/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_values_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 18:27:14 by rhulam            #+#    #+#             */
/*   Updated: 2017/10/27 18:49:19 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zconf.h>
#include "viz.h"

void	set_current_breakdown_2(int first, int second, int third, int *i)
{
	while (first)
	{
		attron(COLOR_PAIR(2));
		mvprintw(g_pos + 3, g_x_s + 2 + (*i)++, "-");
		attroff(COLOR_PAIR(2));
		first--;
	}
	while (second)
	{
		attron(COLOR_PAIR(3));
		mvprintw(g_pos + 3, g_x_s + 2 + (*i)++, "-");
		attroff(COLOR_PAIR(3));
		second--;
	}
	while (third)
	{
		attron(COLOR_PAIR(4));
		mvprintw(g_pos + 3, g_x_s + 2 + (*i)++, "-");
		attroff(COLOR_PAIR(4));
		third--;
	}
}

void	set_current_breakdown_3(int fourth, int *i)
{
	while (fourth)
	{
		attron(COLOR_PAIR(5));
		mvprintw(g_pos + 3, g_x_s + 2 + (*i)++, "-");
		attroff(COLOR_PAIR(5));
		fourth--;
	}
}

void	set_current_breakdown(int a, int b, int c, int d)
{
	int		first;
	int		second;
	int		third;
	int		fourth;
	int		i;

	i = 1;
	mvprintw(g_pos + 3, g_x_s + 2, "[");
	mvprintw(g_pos + 3, g_x_s + 2 + 61, "]");
	if (!a && !b && !c && !d)
	{
		while (i <= 60)
			mvprintw(g_pos + 3, g_x_s + 2 + i++, "-");
		return ;
	}
	first = (float)a / ((a + b + c + d) == 0 ? 1 : (a + b + c + d)) * 60 + 0.5;
	second = (float)b / ((a + b + c + d) == 0 ? 1 : (a + b + c + d)) * 60 + 0.5;
	third = (float)c / ((a + b + c + d) == 0 ? 1 : (a + b + c + d)) * 60 + 0.5;
	if (d)
		fourth = 60 - (first + second + third);
	else
		fourth = 0;
	set_current_breakdown_2(first, second, third, &i);
	set_current_breakdown_3(fourth, &i);
	refresh();
}

void	set_last_breakdown_2(int first, int second, int third, int *i)
{
	while (first)
	{
		attron(COLOR_PAIR(2));
		mvprintw(g_pos + 6, g_x_s + 2 + (*i)++, "-");
		attroff(COLOR_PAIR(2));
		first--;
	}
	while (second)
	{
		attron(COLOR_PAIR(3));
		mvprintw(g_pos + 6, g_x_s + 2 + (*i)++, "-");
		attroff(COLOR_PAIR(3));
		second--;
	}
	while (third)
	{
		attron(COLOR_PAIR(4));
		mvprintw(g_pos + 6, g_x_s + 2 + (*i)++, "-");
		attroff(COLOR_PAIR(4));
		third--;
	}
}

void	set_last_breakdown(double a, double b, double c, double d)
{
	int		first;
	int		second;
	int		third;
	int		fourth;
	int		i;

	i = 1;
	mvprintw(g_pos + 6, g_x_s + 2, "[");
	mvprintw(g_pos + 6, g_x_s + 2 + 61, "]");
	if (!a && !b && !c && !d)
	{
		while (i <= 60)
			mvprintw(g_pos + 6, g_x_s + 2 + i++, "-");
		return ;
	}
	first = a / ((a + b + c + d) == 0 ? 1 : (a + b + c + d)) * 60 + 0.5;
	second = b / ((a + b + c + d) == 0 ? 1 : (a + b + c + d)) * 60 + 0.5;
	third = c / ((a + b + c + d) == 0 ? 1 : (a + b + c + d)) * 60 + 0.5;
	if (d)
		fourth = 60 - (first + second + third);
	else
		fourth = 0;
	set_last_breakdown_2(first, second, third, &i);
	set_last_breakdown_3(fourth, &i);
	refresh();
}
