/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 22:52:10 by cadenegr          #+#    #+#             */
/*   Updated: 2024/03/13 22:32:58 by cadenegr         ###   ########.fr       */
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
}

int	main(int ac, char **av)
{
	t_x		x;

	init(&x);
	if (!argument(ac, av[1], &x))
		return (EXIT_FAILURE);
	build_possibilities (&x);
	if (build_result(&x))
		print_result(&x);
	else
		ft_printf("Wrong argument parameters.\n");
	ft_free (&x);
	return (0);
}
