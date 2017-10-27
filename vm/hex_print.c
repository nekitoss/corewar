#include "../corewar.h"

static char		symb(char pos)
{
	return ((pos < 10) ? (pos + '0') : (pos - 10 + 'a'));
}

void			hex_print(unsigned char val)
{
	ft_putchar(' ');
	ft_putchar(symb(ABS(val % 16)));
	val = val / 16;
	ft_putchar(symb(ABS(val % 16)));
}
