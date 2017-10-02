
#ifndef COREWAR_COREWAR_H
#define COREWAR_COREWAR_H

#include "libft/libft.h"
#include "op.h"

typedef struct         s_op
{
    char             *name;
    int             args_nb;
    int             args[MAX_ARGS_NUMBER];
    int             binary;
    int             cycles;
    char            *descr;
    int             codage_oct;
    int             carry;
    int             label_size;
}                    t_op;

void		test(void);
int			ft_exit(char *str);
void		ft_init_struct(t_arg **ptr);
int			vm_valid(int argc, char **argv);
int			hndl_valid_file(int argc, char **argv, t_arg *ptr, char *str);

#endif
