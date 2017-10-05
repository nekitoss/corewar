#include "asm.h"

void error(char *str)
{
	ft_printf("%s\n", str);
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

	ret = (t_commands*)malloc(sizeof(t_commands));
	ret->command_name = NULL;
	ret->label_name = NULL;
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

	len = (int)ft_strlen(s);
	if (len <= 2 || s[len - 1] != 's' || s[len - 2] != '.')
		error("Wrong file. File format must be .s");
	fd = open(s, O_RDONLY);
	ft_printf("fd = %d\n", fd);
	if (fd < 0)
		error("No file.");
	return (fd);
}

char	*read_file(int fd)
{
	char *s;
	char *free_ptr;
	char *str;

	str = (char*)malloc(1);
	*str = '\0';
	free_ptr = (char*)malloc(1);
	*free_ptr = '\0';
	while (get_next_line(fd, &s))
	{
		free_ptr = str;
		str = ft_strjoin(str, s);
		free(free_ptr);
		free_ptr = str;
		str = ft_strjoin(str, "\n");
		free(free_ptr);
		free(s);
	}
	return (str);
}

header_t	*new_head()
{
	header_t *ret;

	ret = (header_t*)malloc(sizeof(header_t));
	ft_bzero(ret->prog_name, sizeof(char) * (PROG_NAME_LENGTH + 1));
	ft_bzero(ret->comment, sizeof(char) * (COMMENT_LENGTH + 1));
	ret->prog_size = 0;
	ret->magic = 0xf383ea00;
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

int 	count_quotes(char *ptr)
{
	int i;

	i = 0;
	while (*ptr != '\n')
	{
		if (*ptr == '"')
			i++;
		ptr++;
	}
	return (i);
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
	if (v->count_name > 1 || v->count_name == 0)
		error("Syntax error. \".name\"");
	if (count_quotes(ptr) != 2)
		error("Syntax error. -> \" <- ");
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
	if (v->count_comment > 1 || v->count_comment == 0)
		error("Syntax error. \".comment\"");
	if (count_quotes(ptr) != 2)
		error("Syntax error. -> \" <-");
	return (get_name(ptr));
}

void valid_head(header_t *head, char **str)
{
	char *t;
	int fdwrite;
	int i;

	fdwrite = open("example.cor", O_WRONLY);
	t = head->prog_name;
	cpy(&t, check_name(*str));
	ft_printf("\nname - %s\n", head->prog_name);
	if (ft_strlen(t) > 128)
		error("Too large name");
	t = head->comment;
	cpy(&t, check_comment(*str));
	ft_printf("\ncomment - %s\n", head->comment);
	if (ft_strlen(t) > 2048)
		error("Too large comment");
	write(fdwrite, head, sizeof(header_t));
	close(fdwrite);
	i = 0;
	while (i < 2)
	{
		while (**str != '.')
			(*str)++;
		while (**str != '\n')
			(*str)++;
		i++;
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

int		ft_stcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
//	ft_printf("strcmp %.18s\n", s1);
//	ft_printf("strcmp %.18s\n", s2);
	while (*s1 == *s2 && *s1 && *s2)
	{
		i++;
		s1++;
		s2++;
	}
	if (*s1 && *s2 == LABEL_CHAR)
		return (0);
	return (i);
}

int		is_command(char *s)
{
	int		i;
	char	*st;

	i = 0;
	while (i < 16)
	{
		st = (g_tab[i]).name;
		if (ft_stcmp(st , s) > 0 && (ft_stcmp(st, s) == (int)ft_strlen(st)))
			return (i);
		i++;
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
	//ft_printf("before-> %.18s\n", s);
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
	ft_printf("str = %s\n", str);
	return (str);
}

char		*str_to_lower(char *s)
{
	char	*ret;
	int		i;

	i = 0;
	ret = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1));
	while (*s != '\0')
	{
		ret[i] = (char)ft_tolower((int)(*s));
		i++;
		s++;
	}
	ret[i] = '\0';
	return (ret);
}

void		check_repeat(t_label *lb, char *s)
{
	char	*str1;
	char	*str2;

	if (!(lb->name))
		return ;
	str1 = str_to_lower(s);
	while (lb)
	{
		str2 = str_to_lower(lb->name);
		if (ft_strequ(str1, str2))
		{
			ft_printf("s1 %s, s2 %s\n", str1, str2);
			error("ERROR. label can not have same name.");
		}
		lb = lb->next;
	}
}

int		add_label(t_asm *masm, char *s)
{
	t_label	*lb;

	lb = masm->labels;
	check_repeat(lb, get_lb_name(s));
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

void	check_command(t_asm *masm, char **str)
{
	char	*s;

	s = *str;
	if (!check_label_or_comm(s))
		return ;

	while (**str != '\n')
		(*str)++;
	//ft_printf("??|-> %s", *str);
}

int			check_label(t_asm *masm, char **str)
{
	char	*s;
	int		i;

	s = *str;
	if (check_label_or_comm(s) == 1)
		return (1);
	i = add_label(masm, s);
	(*str) += i + 1;
	while (**str != LABEL_CHAR)
		(*str)++;
	(*str)++;
	while (**str ==  ' ' || **str == '\t')
		(*str)++;
	if (**str == '\n')
		return (0);
	return (1);
//	s = *str;
//	if (check_label_or_comm(s))
//		check_command(masm, str);
}

void	valid_code(t_asm *masm, char *str, header_t *head)
{
	int fdwrite;

	fdwrite = open("hell.s", O_WRONLY);
	del_com(&str);
	valid_head(head, &str);
	while (*str != '\0')				/////check EOF
	{
		if (check_label(masm, &str))
			check_command(masm, &str);
		while (*str != '\n')
			str++;
		if (*str == '\n')
			str++;
	}



	ft_printf("\n----->%s\n", str);
	write(fdwrite, str, ft_strlen(str));
	close(fdwrite);
}

int main(int argc, char **argv)
{
	int			fd;
	char		*file;
	header_t	*head;
	t_asm		*main_struc;

	if (argc <= 1)
		error("No filename. Usage: ./asm filename.");
	fd = check_file_name(argv[argc - 1]);
	file = read_file(fd);
	head = new_head();
	main_struc = new_struct();
	main_struc->labels->byte_num = -1;
	valid_code(main_struc, file, head);


//	valid = new_valid();
//	header_t head;
//	fd = open("/nfs/2016/y/yrobotko/CLionProjects/untitled1/ex.s", O_RDONLY);
//	printf("%d\n", fd);
//	valid_before_code(&head, fd, valid);
	close(fd);
	return 0;
}