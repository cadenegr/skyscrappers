/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_print_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:15:28 by cadenegr          #+#    #+#             */
/*   Updated: 2024/03/13 22:32:44 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skyscrapers.h"

void	ft_free(t_x *x)
{
	free (x->arg);
	free (x->sequence);
	free (x->possibilities);
	free (x->result);
}

bool	ft_check_if_correct(t_x *x)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	while (x->result[j])
	{
		if (ft_isalpha(x->result[j]))
			count++;
		if (count > 4)
			return (0);
		if (ft_isdigit(x->result[j]))
			count = 0;
		j++;
	}
	return (1);
}

bool	build_result(t_x *x)
{
	int	i;

	while (1)
	{
		extract_row(x);
		i = ft_strlen(x->result);
		if (!ft_check_if_correct(x))
			return (0);
		if (i > 64)
		{
			ft_memset (x->possibilities, '\0', (x->poss_result_len - 1));
			ft_strcat(x->possibilities, x->result);
			ft_memset (x->result, '\0', (x->poss_result_len - 1));
		}
		else
			break ;
		if (i < 63)
			return (0);
	}
	return (true);
}

void	print_result(t_x *x)
{
	ft_printf("\n\t\t   %c %c %c %c \n", x->arg[0],
		x->arg[1], x->arg[2], x->arg[3]);
	ft_printf("\t\t  ---------\n");
	ft_printf("\t\t%c |%c|%c|%c|%c| %c\n", x->arg[8],
		x->result[0], x->result[1], x->result[2], x->result[3], x->arg[12]);
	ft_printf("\t\t  ---------\n");
	ft_printf("\t\t%c |%c|%c|%c|%c| %c\n", x->arg[9],
		x->result[8], x->result[9], x->result[10], x->result[11], x->arg[13]);
	ft_printf("\t\t  ---------\n");
	ft_printf("\t\t%c |%c|%c|%c|%c| %c\n", x->arg[10],
		x->result[16], x->result[17], x->result[18], x->result[19], x->arg[14]);
	ft_printf("\t\t  ---------\n");
	ft_printf("\t\t%c |%c|%c|%c|%c| %c\n", x->arg[11],
		x->result[24], x->result[25], x->result[26], x->result[27], x->arg[15]);
	ft_printf("\t\t  ---------\n");
	ft_printf("\t\t   %c %c %c %c \n\n", x->arg[4],
		x->arg[5], x->arg[6], x->arg[7]);
}

bool	ft_shorten(t_x *x, char *substr)
{
	if (ft_isalpha(substr[0]) && substr[0] != 'D')
	{
		ft_strcat(x->result, substr);
		return (1);
	}
	return (0);
}
