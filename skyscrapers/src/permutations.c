/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:45:33 by cadenegr          #+#    #+#             */
/*   Updated: 2024/03/13 22:33:05 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skyscrapers.h"

bool	ft_visible_nums(const char *str, char num)
{
	int	count;
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	count = 1;
	while (i < len)
	{
		if (str[j] > str[i + 1])
			j = j + 0;
		else
		{
			count++;
			j = i + 1;
		}
		i++;
	}
	if (num == (count + 48))
		return (1);
	return (0);
}

bool	ft_rev_visible_nums(const char *str, char num)
{
	int	count;
	int	i;
	int	j;

	i = ft_strlen(str) - 1;
	j = ft_strlen(str) - 1;
	count = 1;
	while (i > 0)
	{
		if (str[j] > str[i - 1])
			j = j + 0;
		else
		{
			count++;
			j = i - 1;
		}
		i--;
	}
	if (num == (count + '0'))
		return (1);
	return (0);
}

//Function to swap two elements in an array
void	swap(char *x, char *y)
{
	char	temp;

	temp = *x;
	*x = *y;
	*y = temp;
}

void	first_gen_per(char *sequence, int start, int end, t_x *x)
{
	int	i;

	if (start == end)
	{
		if (ft_visible_nums(sequence, x->arg[x->arg_index]))
		{
			if (ft_rev_visible_nums(sequence, x->arg[x->arg_index + 4]))
				x->poss_len++;
		}
	}
	else
	{
		i = start;
		while (i <= end)
		{
			swap(&sequence[start], &sequence[i]);
			first_gen_per(sequence, start + 1, end, x);
			swap(&sequence[start], &sequence[i]);
			i++;
		}
	}
}

// Function to generate all permutations of a sequence
void	gen_per(char *sequence, int start, int end, t_x *x)
{
	int	i;

	if (start == end)
	{
		if (ft_visible_nums(sequence, x->arg[x->arg_index]))
		{
			if (ft_rev_visible_nums(sequence, x->arg[x->arg_index + 4]))
				ft_strcat (x->possibilities, sequence);
		}
	}
	else
	{
		i = start;
		while (i <= end)
		{
			swap(&sequence[start], &sequence[i]);
			gen_per(sequence, start + 1, end, x);
			swap(&sequence[start], &sequence[i]);
			i++;
		}
	}
}

/*
int main()
{
	char sequence[] = "1234"; // Change this to your desired sequence
	int length = strlen(sequence);

	printf("Acll permutations of %s are:\n", sequence);
	generatePermutations(sequence, 0, length - 1);

	return 0;
}*/
