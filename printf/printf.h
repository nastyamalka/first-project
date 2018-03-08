#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*
** looking for specifications? look no futher!
** http://pubs.opengroup.org/onlinepubs/9699919799/functions/printf.html
*/

/*
** stdarg: unknown number of arguments
** wchar: wide characters
** limits: upper and lower values of primitive types
*/

# include "../libft/libft.h"
# include <stdarg.h>
# include <wchar.h>
# include <limits.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct	s_lst
{
	char		znak;
	int			width;
	int			precis;
	char		modif;
	char		vyravn;
	char		tochn_bool;
	char		nul;
	char		h;
}				t_lst;




#endif