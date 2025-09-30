/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 22:52:10 by cadenegr          #+#    #+#             */
/*   Updated: 2025/09/30 17:09:25 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skyscrapers.h"

void	init(t_x *x)
{
	x->arg = NULL;
	x->sequence = NULL;
	x->possibilities = NULL;
	x->substr = NULL;
	x->result = NULL;
	x->before_first = NULL;
	x->first = NULL;
	x->second = NULL;
	x->third = NULL;
	x->fourth = NULL;
	x->fifth = NULL;
	x->uno = NULL;
	x->dos = NULL;
	x->tres = NULL;
	x->cuatro = NULL;
	x->poss_len = 0;
	x->poss_result_len = 0;
}

int	main(int ac, char **av)
{
	t_x		x;

	init(&x);
	if (!argument(ac, av[1], &x))
	{
		ft_free (&x);
		return (EXIT_FAILURE);
	}
	build_possibilities (&x);
	if (x.possibilities != NULL && build_result(&x))
		print_result(&x);
	else
		ft_printf("Wrong argument parameters.\n");
	ft_free (&x);
	return (0);
}
