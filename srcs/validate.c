/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:39:52 by cbagdon           #+#    #+#             */
/*   Updated: 2019/02/21 07:17:34 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

int		validate_file(int fd, int chars, int lines, int *tetriminos)
{
	char	buf;

	while (read(fd, &buf, 1))
	{
		if (!VALID_CHAR(buf))
			return (0);
		else if (buf == '\n')
		{
			lines++;
			read(fd, &buf, 1);
			CHECK_BAD(chars != 4 || (buf == '\n' && lines != 4) ||
					!VALID_CHAR(buf));
			chars = 0;
			if (buf == '\n' && lines == 4)
			{
				lines = 0;
				*tetriminos += 1;
			}
			else
				chars++;
		}
		else
			chars++;
	}
	return (1);
}

int		valid_tetrimino(char *arr)
{
	int		i;
	int		squares;
	int		connections;

	i = -1;
	squares = 0;
	connections = 0;
	while (arr[++i])
	{
		if (FILLED(arr[i]) == 1)
		{
			squares++;
			if ((i > 3 && FILLED(arr[i - 4]) == 1))
				connections++;
			if (FILLED(arr[i + 4]) == 1)
				connections++;
			if ((i > 0 && FILLED(arr[i - 1]) == 1))
				connections++;
			if (FILLED(arr[i + 1]) == 1)
				connections++;
		}
	}
	CHECK_BAD(squares == 4 && (connections == 8 || connections == 6));
	return (1);
}
