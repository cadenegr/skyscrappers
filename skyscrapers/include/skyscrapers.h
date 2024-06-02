/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skyscrapers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 22:55:26 by cadenegr          #+#    #+#             */
/*   Updated: 2024/03/13 22:31:11 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SKYSCRAPERS_H
# define SKYSCRAPERS_H

# include "libft.h"
# include <stdbool.h>

typedef struct s_skyscrapers
{
	char	*arg;
	int		arg_index;
	char	*sequence;
	char	*possibilities;
	int		poss_len;
	int		poss_result_len;
	int		length;
	int		seq_len;
	char	*substr;
	char	*result;
	char	*before_first;
	char	*first;
	char	*second;
	char	*third;
	char	*fourth;
	char	*fifth;
	int		fir;
	int		sec;
	int		thi;
	int		four;
	int		five;
	char	*uno;
	char	*dos;
	char	*tres;
	char	*cuatro;
}	t_x;

//argument.c
bool	argument(int ac, char *av, t_x *x);
int		processed_argument(t_x *x, char *av);
int		valid_argument(char *av, t_x *x);
int		ft_isdigit_custom(int c);
int		error(int type);

//permutation generator
bool	ft_visible_nums(const char *str, char num);
bool	ft_rev_visible_nums(const char *str, char num);
void	swap(char *x, char *y);
void	first_gen_per(char *sequence, int start, int end, t_x *x);
void	gen_per(char *sequence, int start, int end, t_x *x);

//build possibilities string
void	build_possibilities(t_x *x);
void	second_build_possibilities(t_x *x);

//calculator
int		extract_row(t_x *x);
int		extract_column(t_x *x, int start);
int		check_column(char *substr, t_x *x, int index);
int		check_row(char *substr, t_x *x, int index);
char	*ft_strnchr(const char *s, int c, int n, size_t start);

//build_print_free
void	print_result(t_x *x);
bool	build_result(t_x *x);
void	ft_free(t_x *x);
bool	ft_check_if_correct(t_x *x);
bool	ft_shorten(t_x *x, char *substr);

#endif
