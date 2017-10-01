
#ifndef COREWAR_COREWAR_H
#define COREWAR_COREWAR_H

#include "libft/libft.h"
#include "op.h"

typedef struct         s_op
{
    char             *name;
    int             args_nb;
    int                args[3];
    int             binary;
    int             cycles;
    char             *descr;
    int             codage_oct;
    int             carry;
    int             label_size;
}                    t_op;

#endif
