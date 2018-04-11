/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 15:13:32 by amalkevy          #+#    #+#             */
/*   Updated: 2018/03/19 15:13:34 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void			ft_chang_modif(long long int *num, t_lst opt);
void			ft_chang_modif_unsig(unsigned long long int *num, t_lst opt);
void			ft_pointer(va_list args, t_lst opt, int *n);
void			ft_type(char c, t_lst *opt, va_list args, int *n);
int				ft_base(long long int *i, t_lst *opt, char c);
char			*ft_i_b_u(char c, unsigned long long int z, t_lst o, int *n);
void			ft_itoa_base(long long int num, t_lst opt, int *n);
char			*rev(char *start);
void			ft_pr_num2(t_lst opt, int *spaces, int *n, int *l);
int				ft_spaces(t_lst o, char *s, int l, char c);
void			ft_pr_num(char *s, t_lst o, char c, int *n);
void			ft_pstr(char *s, t_lst opt, int *n, char c);
int				n_bits(unsigned int num, t_lst opt, int *n);
int				ft_count_pr_b(wchar_t *str, t_lst opt, int *n);
void			ft_unicode_s(va_list args, t_lst opt, int *n);
void			ft_unicode_c(va_list args, t_lst opt, int *n);
void			ft_one_bit(unsigned int num);
void			ft_two_bit(unsigned int num);
void			ft_three_bit(unsigned int num);
void			ft_four_bit(int *n, unsigned int num);
void			ft_pr_unic_char(unsigned int num, int *n, int size);
void			ft_flag(char c, t_lst *option);
char			*ft_precision(char *str, t_lst *option);
char			*ft_width(char *str, t_lst *option);
char			*ft_modific_2(char *str, t_lst *option);
char			*ft_modific(char *str, t_lst *option);
void			creat_lst(t_lst *opt);
char			is_param(char *c);
int				ft_som_els(char **str, t_lst *option, int *n);
char			*ft_check(char *str, t_lst *option, va_list args, int *n);

#endif
