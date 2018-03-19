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
void	ft_pr_num2(t_lst opt, int *spaces, int *n, int *l)
{
	(*l) = (opt.precis > (*l)) ? opt.precis - (*l) : 0;
	if (opt.h == 'y' && (opt.type == 'o' || opt.type == 'x'
			    || opt.type == 'X' || opt.type == 'p') && opt.nul != 'n' && ++(*n))
    {
        write(1, "0", 1);
        (*spaces)--;
        if (opt.type != 'o' && ++(*n))
			(opt.type == 'X') ? write(1, "X", 1) : write(1, "x", 1);
        (*spaces)--;
    }
    if (opt.znak != 'n' && opt.nul != 'n' && ++(*n))
        write(1, &opt.znak, 1);
    while ((*spaces) > 0 && opt.vyravn == 'n' && ++(*n))
    {
        (opt.nul == 'n') ? write(1, " ", 1) : write(1, "0", 1);
        (*spaces)--;
    }
}

int		ft_spaces(t_lst o, char *s, int l, char c)
{
    int spaces;

    spaces = (o.precis > l) ? o.precis : l;
    spaces = (o.znak != 'n') ? spaces + 1 : spaces;
    spaces = (*s == '0' && o.precis == 0) ? 0 : spaces;
    spaces = (o.width > spaces) ? o.width - spaces : 0;
    spaces = (c == 'x' && o.h == 'y' && o.nul == 'n' && (*s != '0'
		                           || o.type == 'p')) ? spaces - 2 : spaces;
    spaces = (c == 'o' && o.h == 'y') ? spaces - 1 : spaces;
    return (spaces);
}

void	ft_pr_num(char *s, t_lst o, char c, int *n)
{
    int					spaces;
    int					l;

    l = (s != NULL) ? ft_strlen(s) : 0;
    spaces = ft_spaces(o, s, l, c);
    ft_pr_num2(o, &spaces, n, &l);
    (c == 'x' && o.h == 'y' && o.nul == 'n' && (*s != '0' ||
                                                o.type == 'p') && (*n += 2)) ? write(1, "0x", 2) : 0;
    (c == 'X' && o.h == 'y' && o.nul == 'n' && *s != '0' &&
     (*n += 2)) ? write(1, "0X", 2) : 0;
    if (c == 'o' && o.h == 'y' && o.nul == 'n' && ++(*n))
    {
        write(1, "0", 1);
        l--;
    }

    if (o.znak != 'n' && o.nul == 'n' && ++(*n))
        write(1, &o.znak, 1);
    while (l-- > 0 && ++(*n))
        write(1, "0", 1);
    if (s != NULL && !(*s == '0' && o.precis == 0) && !(*s == '0'
                                                        && o.type == 'o' && o.h == 'y'))
    {
        ft_putstr(s);
        (*n) += ft_strlen(s);
    }
    while (spaces-- && o.vyravn == 'l' && ++(*n))
        (o.nul == 'n') ? write(1, " ", 1) : write(1, "0", 1);
}
char	*ft_itoa_base_u(char c, unsigned long long int num, t_lst opt, int *n)
{
    long long int		base;
    char				*res;
    long long int		i;

    i = 0;
    if (c != 'u')
        ft_chang_modif_unsig(&num, opt);
    opt.znak = 'n';
    res = (char *)(malloc(sizeof(char) * 30));
    base = (c == 'o') ? 8 : 16;
    base = (c == 'd') ? 10 : base;
    base = (c == 'u') ? 2 : base;
    (num == 0 && ++i) ? res[0] = '0' : 0;
    while (num > 0)
    {
        if ((c == 'x' || c == 'X') && num % base > 9 && num % base < 17)
            res[i++] = (c == 'x') ? 87 + num % base : 55 + num % base;
        else
            res[i++] = (char)(48 + num % base);
        num = num / base;
    }
    res[i] = '\0';
    res = rev(res);
    if (c != 'u')
    {
    	ft_pr_num(res, opt, c, n);
    	free(res);
    	return (NULL);
    }
    else
    	return (res);
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


void	ft_pstr(char *s, t_lst opt, int *n, char c)
{
	int					l;
	int					i;
	int					m;

	m = 0;
	if (!s)
	{
		m = 1;
		s = malloc(sizeof(char) * 7);
		s = ft_strcpy(s, "(null)");
	}
	l = (*s == '\0' && c == 'c') ? 1 : ft_strlen(s);
	l = (l > opt.precis && (opt.precis != -1 && !(*s == '\0' && c == 'c')))
		? opt.precis : l;
	i = (opt.width > l && opt.vyravn != 'l') ? (opt.width - l) : 0;
	while (opt.vyravn != 'l' && i > 0 && i > 0 && i-- && ++(*n))
		(opt.nul == 'n') ? write(1, " ", 1) : write(1, "0", 1);
	(*s == '\0' && c == 'c' && ++(*n)) ? write(1, "\0", 1) : 0;
	if (*s)
		while (i < l && ++(*n))
                write(1, &s[i++], 1);
	i = (opt.width > l && opt.vyravn == 'l') ? (opt.width - l) : 0;
	while (i-- && opt.vyravn == 'l')
		(opt.nul == 'n' && ++(*n)) ? write(1, " ", 1) : 0;
	(m == 1) ? free(s) : 0;
}

void	ft_itoa_base(long long int num, t_lst opt, int *n)
{
	char				*res;
	long long int		i;

	i = 0;
	ft_chang_modif(&num, opt);
	if ((res = (char*)(malloc(sizeof(char) * 30))) && num < 0)
	{
		if (num < -9223372036854775807)
		{
			ft_pr_num("-9223372036854775808", opt, '\0', n);
			return ;
		}
		opt.znak = '-';
		num *= -1;
	}
	(num == 0 && ++i) ? res[0] = '0' : 0;
	while (num > 0)
	{
		res[i++] = (char)(48 + num % 10);
		num = num / 10;
	}
	res[i] = '\0';
	res = rev(res);
	ft_pr_num(res, opt, '\0', n);
	free(res);
}

char	is_param(char *c)
{
	if (*c == '.' && *(c + 1) && (*(c + 1) >= '0' && *(c + 1) <= '9'))
		return ('p');
	if (*c == '.' && *(c + 1) && !(*(c + 1) >= '0' && *(c + 1) <= '9'))
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
	option->precis = ft_atoi(ptr);
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
	option->width = ft_atoi(ptr);
            //(option->width < ft_atoi(ptr))
		//?  : option->width;
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

void	ft_pointer(va_list args, t_lst opt, int *n)
{
	unsigned long int	p;
	char				*s;

	if (opt.type == 'p')
	{
		p = (unsigned long)va_arg(args, void*);
		opt.h = 'y';
		opt.modif = '4';
		ft_itoa_base_u('x', p, opt, n);
//	    if (p == NULL)
//            *n = -1;
    }
	else
	{
		s = malloc(sizeof(char) * 2);
		s[0] = va_arg(args, int);
		s[1] = '\0';
		ft_pstr(s, opt, n, 'c');
		free(s);
	}
}

void	ft_pr_unic_char(unsigned int num, int *n, int size)
{
    unsigned char	octet;
    unsigned char	o4;
	unsigned char	o3;
	unsigned char	o2;
	unsigned char	o1;
    unsigned int mask1 = 49280;
    unsigned int mask2= 14712960;
    unsigned int mask3= 4034953344;

	if (size == 1 && ((*n) += 1))
	{
		octet = (unsigned char)num;
		write(1, &octet, 1);
	}
	else  if (size == 2 && ((*n) += 2))
	{
		o2 = (num << 26) >> 26; // Восстановление первых 6 бит 110xxxxx 10(xxxxxx)
		o1 = ((num >> 6) << 27) >> 27; // Восстановление последних 5 бит 110(xxxxx) 10xxxxxx   
		octet = (mask1 >> 8) | o1; // Применение первой битовой маски ко первому байту
		write(1, &octet, 1);
		octet = ((mask1 << 24) >> 24) | o2; // Применение второй битовой маски ко второму байту
		write(1, &octet, 1);
	}
	else  if (size == 3 && ((*n) += 3))
	{
		o3 = (num << 26) >> 26; // Восстановление первых 6 бит 1110xxxx 10xxxxxx 10(xxxxxx)
		o2 = ((num >> 6) << 26) >> 26; // Восстановление вторых 6 бит 1110xxxx 10(xxxxxx) 10xxxxxx
		o1 = ((num >> 12) << 28) >> 28; // Восстановление последних 4 бит 1110(xxxx) 10xxxxxx 10xxxxxx   
		octet = (mask2 >> 16) | o1; // Применение первой битовой маски ко первому байту
		write(1, &octet, 1);
		octet = ((mask2 << 16) >> 24) | o2; // Применение второй битовой маски ко второму байту
		write(1, &octet, 1);
		octet = ((mask2 << 24) >> 24) | o3; // Применение третьей битовой маски ко третьему байту
		write(1, &octet, 1);
	}
	else
	{
        (*n) += 4;
		o4 = (num << 26) >> 26; // Восстановление первых 6 11110xxx 10xxxxxx 10xxxxxx 10(xxxxxx)
		o3 = ((num >> 6) << 26) >> 26; // Восстановление вторых 6 бит 11110xxx 10xxxxxx 10(xxxxxx) 10xxxxxx
		o2 = ((num >> 12) << 26) >> 26;  // Восстановление третьих 6 бит bits 11110xxx 10(xxxxxx) 10xxxxxx 10xxxxxx
		o1 = ((num >> 18) << 29) >> 29; // Восстановление последних 3 бита 11110(xxx) 10xxxxxx 10xxxxxx 10xxxxxx    
		octet = (mask3 >> 24) | o1; // Применение бит первого байта на первый байт маски
		write(1, &octet, 1);
		octet = ((mask3 << 8) >> 24) | o2; // Применение второй битовой маски ко второму байту
		write(1, &octet, 1);
		octet = ((mask3 << 16) >> 24) | o3; // Применение третьей битовой маски ко третьему байту
		write(1, &octet, 1);
		octet = ((mask3 << 24) >> 24) | o4; // Применение последней битовой маски ко последнему байту
		write(1, &octet, 1);
	}
	return ;
}

int 	n_bits(unsigned int num, t_lst opt, int *n)
{
	int 				num_bits;

	num_bits = ft_strlen(ft_itoa_base_u('u', num, opt, n));
    num_bits /= 2;
    if (num_bits < 4)
        num_bits = 1;
    else if (num_bits >= 4 && num_bits <= 5)
        num_bits = 2;
    else if (num_bits >= 6 && num_bits <= 8)
        num_bits = 3;
    else
        num_bits = 4;
    return (num_bits);
}

int 	ft_count_pr_b(wchar_t *str, t_lst opt, int *n)
{
	int 	i;
	int 	pr_b;

	i = 0;
    pr_b = 0;
    if (opt.precis == -1)
        while (str && str[i])
            pr_b += n_bits(str[i++], opt, n);
	while (opt.precis > 0 && str[i])
	{
		opt.precis -= n_bits(str[i], opt, n);
		if (opt.precis > 0 )
            pr_b += n_bits(str[i++], opt, n);
	}
	return (pr_b);
}

void	ft_unicode(va_list args, t_lst opt, int *n)
{
    wchar_t				*str;
	unsigned int		c;
	int 				anum_bits;
    int                 num_bits;
	int 				i;

	i = 0;
	if (opt.type == 's' || opt.type == 'S')
	{
		str = va_arg(args, wchar_t*);
        if (!str)
            ft_pstr(NULL, opt, n, 's');
		anum_bits = ft_count_pr_b(str, opt, n);
	num_bits = anum_bits;
		while (opt.vyravn != 'l' && opt.width-- > anum_bits && ++(*n))
			(opt.nul == 'n') ? write(1, " ", 1) : write(1, "0", 1);
	while (anum_bits > 0)
	{
	    c = (unsigned int)n_bits(str[i], opt, n);
	ft_pr_unic_char(str[i++], n, c);
	anum_bits -= c;
        }
        while (opt.vyravn == 'l' && opt.width-- > num_bits && ++(*n))
	(opt.nul == 'n') ? write(1, " ", 1) : write(1, "0", 1);
	}
	else
	{
		c = (unsigned int)va_arg(args, wint_t);
		num_bits = n_bits(c, opt, n);
		while (opt.vyravn != 'l' && opt.width-- > num_bits && ++(*n))
			(opt.nul == 'n') ? write(1, " ", 1) : write(1, "0", 1);
		ft_pr_unic_char(c, n, num_bits);
		while (opt.vyravn == 'l' && opt.width-- > num_bits && ++(*n))
			(opt.nul == 'n') ? write(1, " ", 1) : write(1, "0", 1);
	}
	return ;
}

void	ft_type(char c, t_lst *opt, va_list args, int *n)
{
	long long int		i;

	opt->type = c;
	if (c == 'i' || c == 'd' || c == 'D' || c == 'o' ||
			c == 'x' || c == 'X' || c == 'u' || c == 'U' || c == 'O')
	{
		(opt->tochn_bool == 'y') ? opt->nul = 'n' : 0;
		(c == 'D' || c == 'U' || c == 'O') ? ft_modific("l", opt) : 0;
		i = va_arg(args, long long int);
		if (c == 'i' || c == 'd' || c == 'D')
			ft_itoa_base(i, *opt, n);
		else if (c == 'x' || c == 'X')
			(c == 'x') ? ft_itoa_base_u('x', i, *opt, n) :
		ft_itoa_base_u('X', i, *opt, n);
		else if (c == 'o' || c == 'O' || c == 'u' || c == 'U')
			(c == 'o' || c == 'O') ? ft_itoa_base_u('o', i, *opt, n) :
		ft_itoa_base_u('d', i, *opt, n);
	}
	else if (c == 's' && opt->modif != '3')
		ft_pstr(va_arg(args, char *), *opt, n, 's');
	else if (c == 'S' || (c =='s' && opt->modif == '3'))
		ft_unicode(args, *opt, n);
	else if (c == 'c' && opt->modif != '3')
		ft_pointer(args, *opt, n);
	else if (c == 'C' || (c =='c' && opt->modif == '3'))
		ft_unicode(args, *opt, n);
	else if (c == 'p')
		ft_pointer(args, *opt, n);
}

int		ft_som_els(char **str, t_lst *option, int *n)
{
	char	*m;

	if (**str == '%')
	{
		//if (option->precis == 0 && (++(*n)))
		//	ft_putchar((**str));
		//else
        if (option->precis == 0)
            option->precis = 1;
			ft_pstr("%", *option, n, 's');
		(*str)++;
	}
	else if (option->width != 0)
	{
		m = malloc(sizeof(char) * 2);
		m[0] = **str;
		m[1] = '\0';
        if (option->precis == 0)
            option->precis = 1;
		ft_pstr(m, *option, n, 's');
		(*str)++;
		free(m);
	}
	return (1);
}

char	*ft_check(char *str, t_lst *option, va_list args, int *n)
{
	while (*str != '\0')
	{
		if (is_param(str) == '0' && ft_som_els(&str, option, n))
			return (str);
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

int		ft_printf(char *str, ...) {
	va_list args;
	char *ptr;
	t_lst option;
	int n;

	n = 0;
	va_start(args, str);
	while (str && *str != '\0')
	{
		while (*str != '\0' && *str != '%' && ++n)
			ft_putchar((*str++));
		if (*str != '\0' && (*str++) == '%') {
		creat_lst(&option);
		ptr = ft_check(str, &option, args, &n);
		str = ptr;
	}
	}
    va_end(args);
	return (n);
}

// #include <locale.h>

// int main(void)
// {
//    setlocale(LC_ALL, "en_US.UTF-8");
//    ft_printf("%i\n", ft_printf("%4.15S", L"ÊM-M-^QÊM-^XØ‰∏M-ÂM-^O™ÁM-^L´„M-M-^B"));
//     ft_printf("%i\n", printf("%4.15S", L"ÊM-M-^QÊM-^XØ‰∏M-ÂM-^O™ÁM-^L´„M-M-^B"));
//    return (0);
// }
