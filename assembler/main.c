#include "asm.h"

void error(char *str)
{
	ft_putstr(str);
	ft_putchar('\n');
	exit(1);
}

t_label		*new_labels()
{
	t_label	*ret;

	ret = (t_label*)malloc(sizeof(t_label));
	ret->name = NULL;
	ret->byte_num = 0;
	ret->next = NULL;
	return (ret);
}

t_commands		*new_commands()
{
	t_commands	*ret;
	int 		i;

	i = 0;
	ret = (t_commands*)malloc(sizeof(t_commands));
	ret->command_name = NULL;
	ret->labels = (char**)malloc(sizeof(char*) * 3);
	ret->P = (char*)malloc(sizeof(char) * 3);
	ret->P[3] = '\0';
	ret->param = (int*)malloc(sizeof(int) * 3);
	ft_bzero(ret->param, 3 * sizeof(int));
	while (i < 3)
	{
		ret->labels[i] = NULL;
		ret->param[i] = 0;
		ret->P[i] = 'O';
		i++;
	}
	ret->codage = 0;
	ret->size = 0;
	ret->next = NULL;
	return (ret);
}

t_asm	*new_struct()
{
	t_asm	*ret;

	ret = (t_asm*)malloc(sizeof(t_asm));
	ret->labels = new_labels();
	ret->commands = new_commands();
	ret->head = NULL;
	ret->count_byte = 0;
	return (ret);
}

t_validation *new_valid()
{
	t_validation *ret;

	ret = (t_validation*)malloc(sizeof(t_validation));
	ft_bzero(ret, sizeof(ret));
	return (ret);
}

int		check_file_name(char *s)
{
	int fd;
	int len;

//	while (ft_strchr(s, '/'))
//	{
//		s = ft_strchr(s, '/');
//		s++;
//	}
	len = (int)ft_strlen(s); //// ../zork.s /champ/zork.s
	ft_putstr(s);
	if (len <= 2 || s[len - 1] != 's' || s[len - 2] != '.')
		error("Wrong file. File format must be .s");
	fd = open(s, O_RDONLY);
	if (fd < 0)
		error("No file.");
	return (fd);
}

char		*read_file(int fd)
{
	char			*str;
	long long		len;

	len = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	str = (char*)malloc(sizeof(char) * (len + 1));
	read(fd, str, (size_t)len);
	while (len > 0)
	{
		if (str[len - 1] == ' ' || str[len - 1] == '\t')
		{
			len--;
			continue;
		}
		break;
	}
	if (str[len - 1] != '\n')
		error("No newline at the end of file.");
	return (str);
}

unsigned int		reverse_bit(unsigned int a)
{
	unsigned int	b;
	int				i;

	i = 0;
	b = 0;
	while (i < 3)
	{
		if (i)
			a = a >> 8;
		b = b | (a & 255);
		b = b << 8;
		i++;
	}
	a = a >> 8;
	b = b | (a & 255);
	return (b);
}

header_t	*new_head()
{
	header_t *ret;

	ret = (header_t*)malloc(sizeof(header_t));
	ft_bzero(ret->prog_name, sizeof(char) * (PROG_NAME_LENGTH + 1));
	ft_bzero(ret->comment, sizeof(char) * (COMMENT_LENGTH + 1));
	ret->prog_size = 0;
	ret->magic = reverse_bit(COREWAR_EXEC_MAGIC);
	return (ret);
}

char		*get_name(char *str)
{
	char	*ret;
	int		i;
	int j;

	j = 0;
	i = 0;
	while (*str != '\"')
		str++;
	str++;
	while (str[i] != '\"')
		i++;
	ret = (char*)malloc(sizeof(char) * i + 1);
	while (j < i)
	{
		ret[j] = str[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

void 	check_quotes(char *str, int i)
{
	int count;

	count = 0;
	if (i == 1)
		str = ft_strstr(str, ".name");
	else
		str = ft_strstr(str, ".comment");
	while (*str != '\0')
	{
		if (*str == '\"')
			count++;
		str++;
	}
	if (count != 2 && count != 4)
		error("Syntax error. -> \" <- ");
}

char	*check_name(char *str)
{
	t_validation *v;
	char *ptr;
	char *prev;

	v = new_valid();
	prev = ft_strstr(str, ".name");
	ptr = prev;
	while (prev != 0)
	{
		ptr = prev;
		v->count_name++;
		prev += 5;
		prev = ft_strstr(prev, ".name");
	}
	if (v->count_name != 1)
		error("Syntax error. \".name\"");
	check_quotes(str, 1);
	return (get_name(ptr));
}

void cpy(char **dest, char *str)
{
	int i;
	int len;

	i = 0;
	len = (int)ft_strlen(str);
	while (i < len)
	{
		(*dest)[i] = str[i];
		i++;
	}
}

char	*check_comment(char *str)
{
	t_validation *v;
	char *ptr;
	char *prev;

	v = new_valid();
	prev = ft_strstr(str, ".comment");
	ptr = prev;
	while (prev != 0)
	{
		ptr = prev;
		v->count_comment++;
		prev += 8;
		prev = ft_strstr(prev, ".comment");
	}
	if (v->count_comment !=1)
		error("Syntax error. \".comment\"");
	check_quotes(str, 0);
	return (get_name(ptr));
}

void valid_head(header_t *head, char **str)
{
	char *t;
	int i;

	t = head->prog_name;

	cpy(&t, check_name(*str));
	ft_printf("\nname - %s\n", head->prog_name);////
	if (ft_strlen(t) > 128)
		error("Too large name");
	t = head->comment;
	cpy(&t, check_comment(*str));
	ft_printf("\ncomment - %s\n", head->comment);////
	if (ft_strlen(t) > 2048)
		error("Too large comment");
	i = 0;
	while (i < 4)
	{
		if (**str == '\"')
			i++;
		(*str)++;
	}
	(*str)++;
	while (**str == ' ' || **str == '\n' || **str == '\t')
		(*str)++;
	if (**str == '\0')
		error("ERROR. No comands!");
}

void	del_com(char **s)
{
	int i;

	i = 0;
	while ((*s)[i] != '\0')
	{
		while ((*s)[i] != COMMENT_CHAR && (*s)[i] != '\0')
			i++;
		while ((*s)[i] != '\n' && (*s)[i] != '\0')
			(*s)[i++] = ' ';
	}
}

int		ft_stcmp(char *s1, char *s2)
{
	int i;
	char *s;

	s = s1;
	i = 0;
	while (*s1 == *s2 && (*s1 != '\0' || *s2 != '\0'))
	{
		i++;
		s1++;
		s2++;
	}
	if (*s1 != '\0')
		return (0);
	if (*s2 != ' ' && *s2 != '\t' && *s2 != '%')
		error("Invalid instruction");
	if (*s2 == '%')
		if (ft_strequ(s, "st") || ft_strequ(s, "add")
			|| ft_strequ(s, "sub") || ft_strequ(s, "sti")
			|| ft_strequ(s, "aff"))
			error("Invalid instruction");
	return (i);
}

int		is_command(char *s)
{
	int		i;
	int		a;
	char	*st;

	i = 15;
	while (*s == ' ' || *s == '\t')
		s++;
	while (i >= 0)
	{
		st = (g_tab[i]).name;
		a = ft_stcmp(st , s);
		if (a  > 0 && a == (int)ft_strlen(st))
			return (i);
		i--;
	}
	return (-1);
}

int		is_label(char *s)
{
	while (*s != '\n')
	{
		if (!ft_strchr(LABEL_CHARS, *s))
			break;
		s++;
	}
	if (*s == LABEL_CHAR)
		return (1);
	return (0);
}

int 	check_label_or_comm(char *s)			/// label - 0, command - 1
{
	while (*s ==  ' ' || *s == '\t' || *s == '\n')
		s++;
	if (!ft_strchr(LABEL_CHARS, *s))
		error("Lexical error in row");
	if (is_label(s))
	{
		ft_printf("LABEL\n");
		return (0);
	}
	if (is_command(s) != -1)
	{
		ft_printf("COMMAND\n");
		return (1);
	}
	error("Lexical error");
	return (0);
}

char	*get_lb_name(char *s)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (*s ==  ' ' || *s == '\t' || *s == '\n')
		s++;
	while (ft_strchr(LABEL_CHARS, s[i]))
		i++;
	str = (char*)malloc(sizeof(char) * (i + 1));
	while (j < i)
	{
		str[j] = s[j];
		j++;
	}
	return (str);
}

int			check_repeat(t_label *lb, char *s)
{
	if (!(lb->name))
		return (0);
	while (lb)
	{
		if (ft_strequ(s, lb->name))
			return (1);
		lb = lb->next;
	}
	return (0);
}

int		add_label(t_asm *masm, char *s)
{
	t_label	*lb;

	lb = masm->labels;
	if (check_repeat(lb, get_lb_name(s)))
		return (-1);
	if (lb->byte_num != -1)
	{
		while (lb->next)
			lb = lb->next;
		lb->next = new_labels();
		lb = lb->next;
	}
	lb->name = get_lb_name(s);
	lb->byte_num = masm->count_byte;
	return ((int)ft_strlen(lb->name));
}

void	pass_spaces(char **s)
{
	while (**s == '\t' || **s == ' ')
		(*s)++;
}

void	check_separator(char *s, int index)
{
	int count;

	count = 0;
	while (*s != '\n')
	{
		if (*s == SEPARATOR_CHAR && *(s + 1) == SEPARATOR_CHAR)
			error("Separator error \",,\"");
		if (*s == SEPARATOR_CHAR)
			count++;
		s++;
	}
	if (g_tab[index].arg_count != (count + 1))
		error("Separator error");
}

void	check_lb_char(char **s)
{
	if (!ft_strchr(LABEL_CHARS, **s))
		error("Parameter error");
	while (**s != ' ' && **s != '\t' && **s != ',' && **s != '\n')
	{
		if (!ft_strchr(LABEL_CHARS, **s))
			error("Parameter error");
		(*s)++;
	}
}

void	check_dir(char **s)
{
	(*s)++;
	if (ft_isdigit(**s) || **s == '-')
	{
		if (**s == '-' && !ft_isdigit(*(*s + 1)))
			error("Parameter error");
		(*s)++;
		if (**s == ' ' || **s == '\t' || **s == ',' || **s == '\n')
			return ;
		if (!ft_isdigit(**s))
			error("Parameter error");
		while (**s != ' ' && **s != '\t' && **s != ',' && **s != '\n')
		{
			if (!ft_isdigit(**s))
				error("Parameter error");
			(*s)++;
		}
	}
	else if (**s == ':')
	{
		(*s)++;
		check_lb_char(s);
	}
	else
		error("Parameter error");
}

void		check_reg(char **s)
{
	char	*str;

	(*s)++;
	if (!ft_isdigit(**s))
		error("Parameter error");
	str = *s;
	while (**s != ' ' && **s != '\t' && **s != ',' && **s != '\n')
	{
		if (!ft_isdigit(**s))
			error("Parameter error");
		(*s)++;
	}
	if (ft_atoi(str) > 99)
		error("Incorect register number");
}

void	check_indir(char **s)
{
	(*s)++;
	if (**s == '-')
		error("Parameter error");
	if (ft_strchr(LABEL_CHARS,**s))
		check_lb_char(s);
	else
		error("Parameter error");
}

void	check_num(char **s)
{
	if (**s == '-' && !ft_isdigit(*(*s + 1)))
		error("Parameter error");
	(*s)++;
	if (**s == ' ' || **s == '\t' || **s == ',' || **s == '\n')
		return ;
	if (!ft_isdigit(**s))
		error("Parameter error");
	while (**s != ' ' && **s != '\t' && **s != ',' && **s != '\n')
	{
		if (!ft_isdigit(**s))
			error("Parameter error");
		(*s)++;
	}
}

void	check_parameter(char **s)
{
	if (**s == '%')
		check_dir(s);
	else if (**s == 'r')
		check_reg(s);
	else if (**s == ':')
		check_indir(s);
	else if (ft_isdigit(**s) || **s == '-')
		check_num(s);
	else
		error("Parameter error");
}

void	check_args(char *s, int index)
{
	int i;

	i = 0;
	pass_spaces(&s);
	while (ft_isalpha(*s))
		s++;
	if (*s != ' ' && *s != '%' && *s != '\t')
		error("Parameter error");
	s++;
	pass_spaces(&s);
	while (i < g_tab[index].arg_count)
	{
		check_parameter(&s);
		while (*s == ' ' || *s == '\t' || *s == ',')
			s++;
		i++;
	}
}

t_commands		*get_empty_struc(t_commands *c)
{
	while (c->next)
		c = c->next;
	if (ft_strequ(c->command_name, "start"))
		return c;
	else
	{
		c->next = new_commands();
		c = c->next;
		return (c);
	}
}

int		check_type(char **s, int ind, int index)
{
	int i;

	i = 0;
	if (**s == 'r')
		i = 1;
	if (**s == '%')
		i = 2;
	if (**s == ':' || ft_isdigit(**s) || **s == '-')
	{
		i = 4;
		if ((ind == 1 && (index == 9 || index == 13)) || (ind == 2 && index == 10))
			error("Incorect parameter type");
	}
	if ((i & g_tab[index].arg[ind]) == 0)
		error("Incorect parameter type");
	return (i);
}

void	goto_next_param(char **s)
{
	pass_spaces(s);
	if (**s == ',')
	{
		(*s)++;
		pass_spaces(s);
	}
}

int		add_reg(t_commands *comm, int i, char **s)
{
	(*s)++;
	comm->param[i] = ft_atoi(*s);
	comm->P[i] = 'R';
	return (1);
}

int		add_indir(t_commands *comm, int i, char **s)
{
	if (**s == ':')
		(*s)++;
	comm->P[i] = 'I';
	if (**s == '-' || ft_isdigit(**s))
		comm->param[i] = ft_atoi(*s);
	else
		comm->labels[i] = get_lb_name(*s);
	return (2);
}

int		add_lbdir(t_commands *comm, int i, int ind, char **s)
{
	(*s)++;
	comm->labels[i] = get_lb_name(*s);
	if (!g_tab[ind].dir_size)
	{
		comm->P[i] = 'D';
		return (4);
	}
	else
	{
		comm->P[i] = 'd';
		return (2);
	}
}

int		add_dir(t_commands *comm, int i, int ind, char **s)
{
	(*s)++;
	if (**s == ':')
	{
		return (add_lbdir(comm, i, ind, s));

	}
	comm->param[i] = ft_atoi(*s);
	if (!g_tab[ind].dir_size)
	{
		comm->P[i] = 'D';
		return (4);
	}
	else
	{
		comm->P[i] = 'd';
		return (2);
	}
}

int			set_param(t_commands *comm, int i, int index, char **s)
{
	int 		k;

	k = check_type(s, i,  index);
	if (k == 1)
		return (add_reg(comm, i, s));
	else if (k == 2)
		return (add_dir(comm, i, index, s));
	else if (k == 4)
		return (add_indir(comm, i, s));
	return (0);
}

void			add_to_struct(t_asm *masm, int ind, char **s)
{
	t_commands *comm;
	int i;

	i = 0;
	comm = get_empty_struc(masm->commands);
	comm->command_name = ft_strdup(g_tab[ind].name);
	*s += ft_strlen(comm->command_name);
	pass_spaces(s);
	comm->size = masm->count_byte;
	while (i < g_tab[ind].arg_count)
	{
		//ft_printf("-->%s\n", *s);
		masm->count_byte += set_param(comm, i, ind, s);
		while (**s != ',' && **s != ' ' && **s != '\t' && **s != '\n')
			(*s)++;
		goto_next_param(s);
		i++;
	}
	masm->count_byte += 1 + g_tab[ind].codage;
	ft_printf("count_byte %d\n",masm->count_byte);
	if (**s != '\n')
		error("ERROR. Incorect symbol after command");
}

void	check_command(t_asm *masm, char **str)
{
	char	*s;
	int 	index;

	s = *str;
	if (!check_label_or_comm(s))
		error("Syntax error:  LABEL");
	index = is_command(s);
	if (index != -1)
		check_separator(s, index);
	else
		error("Zdes mozhet bit vasha oshibka");
	check_args(s, index);
	pass_spaces(&s);
	add_to_struct(masm, index, &s);

	while (**str != '\n')
		(*str)++;

}

int			check_label(t_asm *masm, char **str)
{
	char	*s;

	s = *str;
	if (check_label_or_comm(s) == 1)
		return (1);
	add_label(masm, s); ////
	while (**str != LABEL_CHAR)
		(*str)++;
	(*str)++;
	while (**str ==  ' ' || **str == '\t')
		(*str)++;
	if (**str == '\n')
		return (0);
	return (1);
}

int		is_empty(char *s)
{
	while ((*s == ' ' || *s == '\t') && *s != '\n')
		s++;
	if (*s == '\0')
		return (1);
	return (0);
}

int		pass_it(char *s)
{
	while (*s == ' ' || *s == '\t')
		s++;
	if (*s == '\n')
		return (1);
	return (0);
}

void	valid_code(t_asm *masm, char *str, header_t *head)
{
	valid_head(head, &str);
	del_com(&str);
	while (*str != '\0' && !is_empty(str))
	{
		ft_printf("--->>%s\n", str);
		if (!pass_it(str) && check_label(masm, &str))
			check_command(masm, &str);
		while (*str != '\n')
			str++;
		if (*str == '\n')
			str++;
	}
}

char		*make_name(char *s)
{
	int		i;
	char	*ret;

	i = 0;
	i = (int)ft_strlen(s);
//	while (s[i] != '.')
//		i++;
	ft_printf("%s\n", s);
	ret = (char*)malloc(sizeof(char) * (i + 3));
//	while (s[i] != 's')
//	{
//		ret[i] = s[i];
//		i++;
//	}
	ft_strcpy(ret, s);
	ret[i - 1] = 'c';
	ret[i] = 'o';
	ret[i + 1] = 'r';
	ft_printf("%s\n", ret);
	return (ret);
}

int		get_ind(char *s)
{
	int  i;

	i = 0;
	while (i < 16)
	{
		if (ft_strequ(g_tab[i].name, s))
			break ;
		i++;
	}
	return (i);
}

int 	get_codege(char *p, int i)
{
	int	code;

	if (p[i] == 'I')
		code = 3;
	else if (p[i] == 'R')
		code = 1;
	else if (p[i] == 'D' || p[i] == 'd')
		code = 2;
	else
		code = 0;
	return (code);
}

void	write_codage(int fdwrite, t_commands *comm)
{
	int codage;

	codage = 0;
	codage += get_codege(comm->P, 0);
	codage = codage << 2;
	codage += get_codege(comm->P, 1);
	codage = codage << 2;
	codage += get_codege(comm->P, 2);
	codage = codage << 2;
	write(fdwrite, &codage, 1);
}

unsigned int		reverse_two_bit(unsigned int a)
{
	unsigned int	b;

	b = 0;
	b = b | (a & 255);
	b = b << 8;
	a = a >> 8;
	b = b | (a & 255);
	return (b);
}

void	write_reg(int fd, int param)
{
	ft_printf("write reg\n");
	write(fd, &param, 1);
}

int 	get_length(int curr_byte, int lb_byte, int fl)
{
	unsigned int	res;

	if (lb_byte >= curr_byte)
		res = (unsigned)lb_byte - curr_byte;
	else
	{
		if (fl == 4)
		{
			res = 4294967295;
			res = res - (curr_byte - lb_byte) + 1;
		}
		else
		{
			res = 65535;
			res = res - (curr_byte - lb_byte) + 1;
		}
	}
	return (res);
}

void	write_indir(int fd, t_commands *comm, t_label *lb, int i)
{
	int	param;
	ft_printf("write indir\n");
	if (comm->labels[i] == NULL)
		param = comm->param[i];
	else
	{
		ft_printf("else indir\n");
		while(!ft_strequ(comm->labels[i], lb->name) && lb)
		{
			ft_printf("param lb= %d \n", lb->byte_num);
			lb = lb->next;
		}
		ft_printf("param lb= %d \n", lb->byte_num);
		param = get_length(comm->size, lb->byte_num, 2);
	}
	param = reverse_two_bit((unsigned)param);
	write(fd, &param, 2);
}

void	write_dir(int fd, t_commands *comm, t_label *lb, int i)
{
	int	param;
	ft_printf("write dir\n");
	if (comm->labels[i] == NULL)
		param = comm->param[i];
	else
	{
		while(!ft_strequ(comm->labels[i], lb->name) && lb)
		{
			ft_printf("param lb= %d \n", lb->byte_num);
			lb = lb->next;
		}
		param = get_length(comm->size, lb->byte_num, 4);
		ft_printf("param lb= %d \n", lb->byte_num);
	}
	param = reverse_bit((unsigned)param);
	write(fd, &param, 4);
}

void	write_param(int fd, t_commands *comm, t_label *lb, int i)
{
	if (comm->P[i] == 'R')
		write_reg(fd, comm->param[i]);
	else if (comm->P[i] == 'I')
		write_indir(fd, comm, lb, i);
	else if (comm->P[i] == 'D')
		write_dir(fd, comm, lb, i);
	else if (comm->P[i] == 'd')
		write_indir(fd, comm, lb, i);
	else
		return ;
	ft_printf("\n\n");
}

void	write_to_cor(int fdwrite, t_commands *comm, t_label *lb)
{
	int i;

	i = g_tab[get_ind(comm->command_name)].op_code;
	write(fdwrite, &i, 1);
	if (g_tab[get_ind(comm->command_name)].codage)
		write_codage(fdwrite, comm);
	write_param(fdwrite, comm, lb, 0);
	write_param(fdwrite, comm, lb, 1);
	write_param(fdwrite, comm, lb, 2);
}

void	make_corfile(t_asm *masm, t_commands *comm, t_label	*lb, char *name)
{
	int fdwrite;
	char *n;

	n = make_name(name); ///// DONT FORGET
	fdwrite = open(n, O_CREAT | O_TRUNC | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
	masm->head->prog_size = reverse_bit((unsigned)masm->count_byte);
	write(fdwrite, masm->head, sizeof(header_t));
	while (comm)
	{
		write_to_cor(fdwrite, comm, lb);
		comm = comm->next;
	}
	ft_printf("Writing output program to %s\n", n);
	close(fdwrite);
}

int 	find_lb(char *s, t_label *lb)
{
	while (lb)
	{
		if (ft_strequ(lb->name, s))
			return (1);
		lb = lb->next;
	}
	return (0);
}

void	check_lb(t_commands *comm, t_label *lb)
{
	int i;

	while(comm)
	{
		i = 0;
		while (i < 3)
		{
			if (comm->labels[i] != NULL)
				if (!find_lb(comm->labels[i], lb))
					error("ERROR. No such label.");
			i++;
		}
		comm = comm->next;
	}
}

int main(int argc, char **argv)
{
	int			fd;
	char		*file;
	t_asm		*mstruc;

	if (argc <= 1)
		error("No filename. Usage: ./asm filename.");
	fd = check_file_name(argv[argc - 1]);
	file = read_file(fd);
	mstruc = new_struct();
	mstruc->head = new_head();
	mstruc->labels->byte_num = -1;
	mstruc->commands->command_name = ft_strdup("start");
	valid_code(mstruc, file, mstruc->head);

	t_commands *c;
	c = mstruc->commands;
	ft_printf("\n\n\n");
	while (c)
	{
		ft_printf("name = %s  lb1- \"%s\" lb2- \"%s\" lb3- \"%s\"  %c%c%c  pr1- %d pr2- %d pr3- %d size = %d\n",
				  c->command_name, c->labels[0], c->labels[1], c->labels[2], c->P[0], c->P[1], c->P[2],
					c->param[0], c->param[1], c->param[2], c->size);
		ft_printf("NEXT\n");
		c = c->next;
	}
	t_label *l;
	l = mstruc->labels;
	while (l)
	{
		ft_printf("name = %s, byte_num = %d\n",l->name, l->byte_num);
		l = l->next;
	}
	ft_printf("count= %d\n", mstruc->count_byte);
	check_lb(mstruc->commands, mstruc->labels);
	make_corfile(mstruc, mstruc->commands, mstruc->labels, argv[argc - 1]);



//	valid = new_valid();
//	header_t head;
//	fd = open("/nfs/2016/y/yrobotko/CLionProjects/untitled1/ex.s", O_RDONLY);
//	printf("%d\n", fd);
//	valid_before_code(&head, fd, valid);
	close(fd);
	return 0;
}