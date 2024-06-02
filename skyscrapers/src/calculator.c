/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:17:45 by cadenegr          #+#    #+#             */
/*   Updated: 2024/03/13 22:32:51 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skyscrapers.h"

char	*ft_strnchr(const char *s, int c, int n, size_t start)
{
	int	i;

	i = 0 + start;
	while (s[i] != '\0' && s[i] != (char)c && i <= n)
		i = i + 4;
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (0);
}

int	check_row(char *substr, t_x *x, int index)
{
	x->first = (ft_strnstr(x->possibilities, "DDDD", x->poss_result_len));
	x->second = (ft_strnstr(x->possibilities, "EEEE", x->poss_result_len));
	x->third = (ft_strnstr(x->possibilities, "FFFF", x->poss_result_len));
	x->fourth = (ft_strnstr(x->possibilities, "GGGG", x->poss_result_len));
	x->fifth = (ft_strnstr(x->possibilities, "HHHH", x->poss_result_len));
	x->fir = x->poss_result_len - (x->first - x->possibilities);
	x->sec = x->poss_result_len - (x->second - x->possibilities);
	x->thi = x->poss_result_len - (x->third - x->possibilities);
	x->four = x->poss_result_len - (x->fourth - x->possibilities);
	x->five = x->poss_result_len - (x->fifth - x->possibilities);
	x->fir = x->fir - x->sec;
	x->sec = x->sec - x->thi;
	x->thi = x->thi - x->four;
	x->four = x->four - x->five;
	x->uno = ft_strnchr(x->first, substr[0], x->fir, index);
	x->dos = ft_strnchr(x->second, substr[1], x->sec, index);
	x->tres = ft_strnchr(x->third, substr[2], x->thi, index);
	x->cuatro = ft_strnchr(x->fourth, substr[3], x->four, index);
	if (x->uno != NULL && x->dos != NULL
		&& x->tres != NULL && x->cuatro != NULL)
		return (1);
	return (0);
}

int	check_column(char *substr, t_x *x, int index)
{
	x->first = (ft_strnstr(x->possibilities, "AAAA", x->poss_result_len));
	x->second = (ft_strnstr(x->possibilities, "BBBB", x->poss_result_len));
	x->third = (ft_strnstr(x->possibilities, "CCCC", x->poss_result_len));
	x->fourth = (ft_strnstr(x->possibilities, "DDDD", x->poss_result_len));
	x->fir = x->poss_result_len - (x->first - x->possibilities);
	x->sec = x->poss_result_len - (x->second - x->possibilities);
	x->thi = x->poss_result_len - (x->third - x->possibilities);
	x->four = x->poss_result_len - (x->fourth - x->possibilities);
	x->four = x->thi - x->four;
	x->thi = x->sec - x->thi;
	x->sec = x->fir - x->sec;
	x->fir = (x->poss_result_len - x->fir);
	x->uno = ft_strnchr(x->possibilities, substr[0], x->fir, index);
	x->dos = ft_strnchr(x->first, substr[1], x->sec, index);
	x->tres = ft_strnchr(x->second, substr[2], x->thi, index);
	x->cuatro = ft_strnchr(x->third, substr[3], x->four, index);
	if (x->uno != NULL && x->dos != NULL
		&& x->tres != NULL && x->cuatro != NULL)
		return (1);
	return (0);
}

int	extract_column(t_x *x, int start)
{
	char		*substr;
	static int	place;
	static int	index = 0;

	place = start;
	substr = ft_substr(x->possibilities, place, 4);
	if (ft_isalpha(substr[0]) && substr[0] != 'H')
	{
		index++;
		ft_strcat(x->result, substr);
	}
	if (ft_isdigit(substr[0]) && substr[0] != 'H')
		if (check_column(substr, x, index))
			ft_strcat (x->result, substr);
	if (substr[0] == 'H')
	{
		ft_strcat(x->result, substr);
		index = 0;
		place = 0;
		free (substr);
		return (1);
	}
	place = place + 4;
	free (substr);
	return (extract_column(x, place));
}

int	extract_row(t_x *x)
{
	static int	place = 0;
	static int	index = 0;
	int			start;
	char		*substr;

	substr = ft_substr(x->possibilities, place, 4);
	if (ft_shorten(x, substr) == true)
		index++;
	if (ft_isdigit(substr[0]) && substr[0] != 'D')
		if (check_row(substr, x, index))
			ft_strcat (x->result, substr);
	if (substr[0] == 'D')
	{
		ft_strcat(x->result, substr);
		start = place + 4;
		place = 0;
		index = 0;
		free (substr);
		return (extract_column(x, start));
	}
	place = place + 4;
	free (substr);
	return (extract_row(x));
}
