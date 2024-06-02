/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_poss.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 23:38:06 by cadenegr          #+#    #+#             */
/*   Updated: 2024/03/13 22:32:37 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skyscrapers.h"

void	build_possibilities(t_x *x)
{
	int	i;

	i = 0;
	x->arg_index = -1;
	while (i < 8)
	{
		if (i == 3)
			x->arg_index = 7;
		else
			x->arg_index = x->arg_index + 1;
		first_gen_per(x->sequence, 0, 3, x);
		i++;
	}
	x->possibilities = ft_calloc (1, ((4 * x->poss_len) + (8 * 4)));
	x->result = ft_calloc (1, ((4 * x->poss_len) + (8 * 4)));
	second_build_possibilities(x);
}

void	second_build_possibilities(t_x *x)
{
	int	i;
	int	j;
	int	sep;

	i = 0;
	sep = 65;
	x->arg_index = 7;
	while (i < 8)
	{
		if (i == 4)
			x->arg_index = 0;
		else
			x->arg_index = x->arg_index + 1;
		gen_per(x->sequence, 0, 3, x);
		j = 0;
		while (j++ < 4)
			x->possibilities[ft_strlen(x->possibilities)] = sep;
		sep++;
		i++;
	}
	x->poss_result_len = ft_strlen(x->possibilities);
}
