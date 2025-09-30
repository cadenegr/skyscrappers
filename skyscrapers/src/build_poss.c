/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_poss.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 23:38:06 by cadenegr          #+#    #+#             */
/*   Updated: 2025/09/30 17:09:25 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skyscrapers.h"

void	build_possibilities(t_x *x)
{
	int	i;
	int	buffer_size;

	x->poss_len = 0;  // Initialize counter
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
	if (x->poss_len == 0)
	{
		ft_printf("Wrong argument parameters.\n");
		return;
	}
	// More generous buffer allocation: account for worst-case scenario
	// Each permutation is 4 chars, plus separators, plus safety margin
	buffer_size = (x->poss_len * 4) + (8 * 4) + 100;
	if (buffer_size < 200)
		buffer_size = 200;  // Minimum safe buffer size
	x->possibilities = ft_calloc (1, buffer_size);
	x->result = ft_calloc (1, buffer_size);
	if (!x->possibilities || !x->result)
	{
		ft_printf("Error: Memory allocation failed\n");
		return ;
	}
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
