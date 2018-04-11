#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "../libft/libft.h"
# include <stdarg.h>
# include <wchar.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

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
	char		type;
}				t_lst;

#endif
