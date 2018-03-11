#include "printf.h"

char	*rev(char *start)
{
	char				*new;
	char				*end;
	char				*new_start;

	if (*start == '\0')
		return (NULL);
	end = start;
	new = ft_strnew(ft_strlen(start));
	new_start = new;
	while (*end)
		end++;
	end--;
	*new++ = *end;
	while (end - start != 0)
		*new++ = *(--end);
	free(start);
	return (new_start);
}

void	ft_chang_modif(long long int *num, t_lst opt)
{
	if (opt.modif == '0')
		*num = (int)(*num);
	if (opt.modif == '1')
		*num = (signed char)(*num);
	if (opt.modif == '2')
		*num = (short)(*num);
	if (opt.modif == '3')
		*num = (long)(*num);
	if (opt.modif == '5')
		*num = (intmax_t)(*num);
	if (opt.modif == '6')
		*num = (size_t)(*num);
}

void	ft_chang_modif_unsig(unsigned long long int *num, t_lst opt)
{
	if (opt.modif == '0')
		*num = (unsigned int)(*num);
	if (opt.modif == '1')
		*num = (unsigned char)(*num);
	if (opt.modif == '2')
		*num = (unsigned short int)(*num);
	if (opt.modif == '3')
		*num = (unsigned long int)(*num);
	if (opt.modif == '5')
		*num = (uintmax_t)(*num);
	if (opt.modif == '6')
		*num = (size_t)(*num);
}

void	ft_pr_num_2(t_lst opt, char c, int *n, int *spaces)
{
	(opt.nul != 'n') ? ft_putchar('0') : 0;
	(*spaces)--;
	if ((c == 'x' || c == 'X') && opt.nul != 'n' && ++(*n))
	{
		(c == 'x') ? ft_putchar('x') : ft_putchar('X');
		(*spaces)--;
	}
}

void	ft_pr_num(char *str, t_lst opt, char c, int *n)
{
	int					spaces;
	int					l;

	l = (str != NULL) ? ft_strlen(str) : 0;
	spaces = (opt.precis > l) ? opt.precis : l;
	spaces = (opt.znak != 'n') ? spaces + 1 : spaces;
    spaces = (*str == '0' && opt.precis == 0) ? 0 : spaces;
	spaces = (opt.width > spaces) ? opt.width - spaces : 0;
	l = (opt.precis > l) ? opt.precis - l : 0;
	(opt.h == 'y' && (*str != '0' || opt.type == 'p') && (c == 'x' || c == 'X') && ++(*n)) ? ft_pr_num_2(opt, c, n, &spaces) : 0;
    (opt.h == 'y' && c == 'o' && ++(*n)) ? ft_pr_num_2(opt, c, n, &spaces) : 0;
    if (opt.znak != 'n' && opt.nul != 'n' && ++(*n))
        ft_putchar(opt.znak);
	while (spaces > 0 && opt.vyravn == 'n' && ++(*n))
	{
		(opt.nul == 'n') ? ft_putchar(' ') : ft_putchar('0');
		spaces--;
	}
    (c == 'x' && opt.h == 'y' && opt.nul == 'n' && *str != '0') ? ft_putstr("0x") : 0;
    (c == 'X' && opt.h == 'y' && opt.nul == 'n' && *str != '0') ? ft_putstr("0X") : 0;
    (c == 'o'&& opt.h == 'y' && opt.nul == 'n') ? ft_putchar('0') : 0;
	if (opt.znak != 'n' && opt.nul == 'n' && ++(*n))
		ft_putchar(opt.znak);
	while (l-- > 0 && ++(*n))
		ft_putchar('0');
	(str != NULL && !(*str == '0' && opt.precis == 0)) ? ft_putstr(str) : 0;
	(str != NULL && !(*str == '0' && opt.precis == 0)) ? (*n) += ft_strlen(str) : 0;
	while (spaces-- && opt.vyravn == 'l' && ++(*n))
		(opt.nul == 'n') ? ft_putchar(' ') : ft_putchar('0');
}

void	ft_itoa_base_u(char c, unsigned long long int num, t_lst opt, int *n)
{
	long long int		base;
	char				*res;
	long long int		i;

	i = 0;
	ft_chang_modif_unsig(&num, opt);
	opt.znak = 'n';
	res = (char *)(malloc(sizeof(char) * 30));
	base = (c == 'o') ? 8 : 16;
	base = (c == 'd') ? 10 : base;
	(num == 0 && ++i) ? res[0] = '0' : 0;
	while (num > 0)
	{
		if ((c == 'x' || c == 'X') && num % base > 9 && num % base < 17)
			res[i] = (c == 'x') ? 87 + num % base : 55 + num % base;
		else
			res[i] = (char)(48 + num % base);
		num = num / base;
		i++;
	}
	res[i] = '\0';
	res = rev(res);
	ft_pr_num(res, opt, c, n);
	free(res);
}

void	ft_itoa_base(long long int num, t_lst opt, int *n)
{
	char				*res;
	long long int		i;

	i = 0;
	ft_chang_modif(&num, opt);
	if (num < 0)
	{
		if (num < -9223372036854775807)
		{
			ft_pr_num("-9223372036854775808", opt, '\0', n);
			return ;
		}
		opt.znak = '-';
		num *= -1;
	}
	res = (char *)(malloc(sizeof(char) * 30));
	(num == 0 && ++i) ? res[0] = '0' : 0;
	while (num > 0)
	{
		res[i++] = (char)(48 + num % 10);
		num = num / 10;
	}
	res[i] = '\0';
	res = rev(res);
	ft_pr_num(res, opt, '\0', n);
}

char	is_param(char *c)
{
	if (*c == '.' && *(c + 1) && (*(c + 1) >= '1' && *(c + 1) <= '9'))
		return ('p');
	if (*c == '.' && *(c + 1) && !(*(c + 1) >= '1' && *(c + 1) <= '9'))
		return ('g');
	if (*c == '-' || *c == '+' || *c == '0' || *c == ' ' || *c == '#')
		return ('f');
	if (*c >= '1' && *c <= '9')
		return ('w');
	if (*c == 'h' || *c == 'l' || *c == 'j' || *c == 'z')
		return ('m');
	if (*c == 'i' || *c == 'd' || *c == 'D' || *c == 'o' || *c == 'O' ||
			*c == 'x' || *c == 'X' || *c == 'c' || *c == 'C' || *c == 'p' ||
			*c == 'u' || *c == 'U' || *c == 's' || *c == 'S')
		return ('t');
	return ('0');
}

void	ft_flag(char c, t_lst *option)
{
	if (c == '+')
		option->znak = '+';
	else if (c == ' ' && option->znak != '+')
		option->znak = ' ';
	else if (c == '-')
	{
		option->nul = 'n';
		option->vyravn = 'l';
	}
	else if (c == '0' && option->vyravn != 'l')
		option->nul = 'y';
	else if (c == '#')
		option->h = 'y';
}

char	*ft_precision(char *str, t_lst *option)
{
	char				*precis;
	char				*ptr;

	precis = (char *)malloc(sizeof(char) * (ft_strlen(str)));
	++str;
	ptr = precis;
	while (*str >= '0' && *str <= '9' && *str != '\0')
	{
		*precis = *str;
		++str;
		++precis;
	}
	*precis = '\0';
	option->tochn_bool = 'y';
	option->precis = (option->precis < ft_atoi(ptr))
		? ft_atoi(ptr) : option->precis;
	free(ptr);
	return (str);
}

char	*ft_width(char *str, t_lst *option)
{
	char				*width;
	char				*ptr;

	width = (char *)malloc(sizeof(char) * (ft_strlen(str)));
	ptr = width;
	while (*str >= '0' && *str <= '9' && *str != '\0')
	{
		*width = *str;
		++str;
		++width;
	}
	*width = '\0';
	option->width = (option->width < ft_atoi(ptr))
		? ft_atoi(ptr) : option->width;
	free(ptr);
	return (str);
}

char	*ft_modific_2(char *str, t_lst *option)
{
	if (*(str + 1) != '\0' && *(str + 1) == 'l' && (*str++))
	{
		if (option->modif < '4')
			option->modif = '4';
	}
	else if (option->modif < '3')
		option->modif = '3';
	return (str);
}

char	*ft_modific(char *str, t_lst *option)
{
	while (*str && (*str == 'h' || *str == 'l' || *str == 'z' || *str == 'j'))
	{
		if (*str == 'h')
		{
			if (*(str + 1) != '\0' && *(str + 1) == 'h')
			{
				++str;
				if (option->modif < '1')
					option->modif = '1';
			}
			else if (option->modif < '2')
				option->modif = '2';
		}
		else if (*str == 'l')
			str = ft_modific_2(str, option);
		else if (*str == 'j' && option->modif != '6')
			option->modif = '5';
		else if (*str == 'z')
			option->modif = '6';
		++str;
	}
	return (str);
}

void	ft_pstr(char *s, t_lst opt, int *n, char c)
{
	int					l;
	int					i;

	if (!s)
	{
		(*n) += 6;
		ft_putstr("(null)");
		return ;
	}

    l = (*s == '\0' && c == 'c') ? 1 : ft_strlen(s);
	l = (l > opt.precis && opt.precis != -1) ? opt.precis : l;
	i = (opt.width > l && opt.vyravn != 'l') ? (opt.width - l) : 0;
	while (i && opt.vyravn != 'l' && ++(*n))
	{
		if (opt.nul == 'n')
			ft_putchar(' ');
		else
			ft_putchar('0');
		i--;
	}
    if (*s == '\0' && c == 'c' && ++(*n))
        ft_putchar('\0');
	if (*s)
		while (i < l && ++(*n))
			ft_putchar(s[i++]);
	i = (opt.width > l && opt.vyravn == 'l') ? (opt.width - l) : 0;
	while (i-- && opt.vyravn == 'l')
		if (opt.nul == 'n' && ++(*n))
			ft_putchar(' ');
}

void	ft_pointer(va_list args, t_lst opt, int *n)
{
	unsigned long int	p;

	p = (unsigned long)va_arg(args, void*);
	opt.h = 'y';
	ft_itoa_base_u('x', p, opt, n);
}

void	ft_type(char c, t_lst *opt, va_list args, int *n)
{
	long long int		i;
	char				*s;

    opt->type = c;
	if (c == 'i' || c == 'd' || c == 'D' || c == 'o' ||
			c == 'x' || c == 'X' || c == 'u' || c == 'U' || c == 'O')
	{
		(opt->tochn_bool == 'y') ? opt->nul = 'n' : 0;
		(c == 'D' || c == 'U' || c == 'O') ? ft_modific("l", opt) : 0;
		i = va_arg(args, long long int);
		if (c == 'i' || c == 'd' || c == 'D')
			ft_itoa_base(i, *opt, n);
		else if (c == 'x')
			ft_itoa_base_u('x', i, *opt, n);
		else if (c == 'X')
			ft_itoa_base_u('X', i, *opt, n);
		else if (c == 'o' || c == 'O')
			ft_itoa_base_u('o', i, *opt, n);
		else if (c == 'u' || c == 'U')
			ft_itoa_base_u('d', i, *opt, n);
	}
	else if (c == 's' || c == 'S')
		ft_pstr(va_arg(args, char *), *opt, n, 's');
	else if ((c == 'c' || c == 'C') && (s = malloc(sizeof(char) * 2)))
	{
		s[0] = va_arg(args, int);//char
		s[1] = '\0';
        ft_pstr(s, *opt, n, 'c');
	}
	else if (c == 'p')
		ft_pointer(args, *opt, n);
}

char	*ft_check(char *str, t_lst *option, va_list args, int *n)
{
	while (*str != '\0')
	{
		if (is_param(str) == '0')
		{
			if (*str == '%') {
                if (option->precis == 0 && (++(*n)))
                    ft_putchar((*str));
                else
                    ft_pstr("%", *option, n, 's');
                str++;
            }
			return (str);
		}
		else if (is_param(str) == 'f')
			ft_flag((*str++), option);
		else if (is_param(str) == 'w')
			str = ft_width(str, option);
		else if (is_param(str) == 'm')
			str = ft_modific(str, option);
		else if (is_param(str) == 'p')
			str = ft_precision(str, option);
		else if (is_param(str) == 't')
		{
			ft_type(*str, option, args, n);
			return (++str);
		}
		else if (is_param(str++) == 'g')
			ft_precision("0", option);
	}
	return (NULL);
}

void	creat_lst(t_lst *opt)
{
	opt->precis = -1;
	opt->vyravn = 'n';
	opt->znak = 'n';
	opt->modif = '0';
	opt->nul = 'n';
	opt->h = 'n';
	opt->tochn_bool = 'n';
	opt->width = 0;
    opt->type = 'n';
}

int		ft_printf(char *str, ...)
{
	va_list				args;
	char				*ptr;
	t_lst				option;
	int					n;

	n = 0;
	va_start(args, str);
	while (str && *str != '\0')
	{
		while (*str != '\0' && *str != '%' && ++n)
			ft_putchar((*str++));
		if (*str != '\0' && (*str++) == '%')
		{
			creat_lst(&option);
            (*str) ? ptr = ft_check(str, &option, args, &n) : 0;
			str = ptr;
		}
	}
	va_end(args);
	return (n);
}

int main(void)
{
    int *a;

    *a = 2;
	printf("\nreturn %i\n",    printf("%.0p, %.p", 0, 0));
	printf("\nreturn %i\n",	   ft_printf("%.0p, %.p", 0, 0));
    //ft_putchar('^@');
    //ft_putchar('\0');
    return (0);
}