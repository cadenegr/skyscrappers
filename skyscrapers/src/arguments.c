/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:24:42 by cadenegr          #+#    #+#             */
/*   Updated: 2024/03/13 22:32:30 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skyscrapers.h"

int	error(int type)
{
	if (type == 1)
		ft_putstr_fd ("No argument.\n", 2);
	if (type == 2)
		ft_putstr_fd ("Not the right argument length.\n", 2);
	if (type == 3)
		ft_putstr_fd ("Invalid argument format.\n", 2);
	return (0);
}

int	ft_isdigit_custom(int c)
{
	if (!(c >= '1' && c <= '4'))
		return (0);
	return (1);
}

int	valid_argument(char *av, t_x *x)
{
	int	i;

	i = 0;
	x->length = ft_strlen(av);
	x->poss_len = 0;
	while (i < x->length)
	{
		if (i % 2 == 0)
		{
			if (!ft_isdigit_custom(av[i]))
				return (0);
		}
		else
			if (av[i] != ' ')
				return (0);
		i++;
	}
	return (1);
}

int	processed_argument(t_x *x, char *av)
{
	int	i;
	int	j;

	x->arg = ft_calloc(1, x->length);
	x->sequence = ft_calloc (1, 4);
	i = 0;
	j = 0;
	while (i < x->length)
	{
		if (ft_isdigit_custom(av[i]))
			x->arg[j++] = av [i];
		i ++;
	}
	ft_strlcpy(x->sequence, "1234", 5);
	return (1);
}

bool	argument(int ac, char *av, t_x *x)
{
	if (ac != 2)
		return (error(1));
	if (ft_strlen(av) != 31)
		return (error(2));
	if (!valid_argument(av, x))
		return (error(3));
	return (processed_argument(x, av));
}
