/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <cadenegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:01:46 by cadenegr          #+#    #+#             */
/*   Updated: 2023/08/30 13:34:10 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_next(char *stat)
{
	int		i;
	int		j;
	char	*str_next;

	i = 0;
	j = 0;
	while (stat[i] && stat[i] != '\n')
		i++;
	if (stat[i] == 0)
		return (NULL);
	i++;
	while (stat[i + j])
		j++;
	str_next = malloc (j + 1);
	if (!str_next)
		return (NULL);
	j = 0;
	while (stat[i + j])
	{
		str_next[j] = stat[i + j];
		j++;
	}
	str_next[j] = '\0';
	return (str_next);
}

char	*ft_line(char *stat)
{
	char	*str_line;
	int		i;

	i = 0;
	if (stat[i] == 0)
		return (NULL);
	while (stat[i] && stat[i] != '\n')
		i++;
	if (stat[i] == '\n')
		i++;
	str_line = malloc (i + 1);
	if (!str_line)
		return (NULL);
	i = 0;
	while (stat[i] != 0 && stat[i] != '\n')
	{
		str_line[i] = stat[i];
		i++;
	}
	if (stat[i] == '\n')
		str_line[i++] = '\n';
	str_line[i] = 0;
	return (str_line);
}

char	*ft_read(int fd, char *stat)
{
	char	*buffer;
	int		byte_read;

	byte_read = 1;
	while (!ft_strchr_gnl(stat, '\n') && byte_read != 0)
	{
		buffer = malloc (BUFFER_SIZE + 1);
		if (!buffer)
			return (NULL);
		byte_read = read (fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free (stat);
			free (buffer);
			buffer = NULL;
			return (NULL);
		}
		buffer[byte_read] = '\0';
		stat = ft_strjoin_gnl(stat, buffer);
		free (buffer);
		buffer = NULL;
	}
	return (stat);
}

char	*get_next_line(int fd)
{
	static char	*stat = NULL;
	char		*line;
	char		*next;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	stat = ft_read(fd, stat);
	if (stat == NULL)
		return (NULL);
	line = ft_line(stat);
	next = stat;
	stat = ft_next(stat);
	free(next);
	next = NULL;
	return (line);
}
// int	main(void)
//  {
//  	int		fd;
//  	char	*theline = NULL;

//  	fd = open("Psalm91.txt", O_RDONLY, 0644);
//  	if (fd == -1)
//  		return (1);
//  	theline = get_next_line(fd);
//  	printf("first line output = %s\n", theline);
//  		free (theline);
//  	theline = get_next_line(fd);
//  	printf("second line output = %s\n", theline);
//  		free (theline);
//  	theline = get_next_line(fd);
//  	printf("third line output = %s\n", theline);
//  		free (theline);
//  	theline = get_next_line(fd);
//  	printf("fourth line output = %s\n", theline);
//  		free (theline);
// 	theline = get_next_line(fd);
//  	printf("fifth line output = %s\n", theline);
// 		free (theline);
//  	theline = get_next_line(fd);
//  	printf("sixth line output = %s\n", theline);
//  		free (theline);
//  	close(fd);
//  	return (0);
// }
//
// int main(void)
// {
//     int fd ;
//     char *theline = NULL;
//     int line_number = 1;
//     fd = open("Psalm91.txt", O_RDONLY);
//     if (fd == -1)
//         return (1);
//     while ((theline = get_next_line(fd)) != NULL) {
//         printf("Line %d: %s\n", line_number++, theline);
//         free(theline);
//     }
//     close(fd);
//     return (0);
// }

// int main(void)
// {
//     char *input_line;
// 	if ((input_line = get_next_line(STDIN_FILENO)) != NULL)
//         // Process the input_line
//         {
//         	printf("You entered: %s\n", input_line);
// 	        free(input_line);
// 	}
//     return 0;
// }
