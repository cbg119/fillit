/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:39:52 by cbagdon           #+#    #+#             */
/*   Updated: 2019/02/19 22:31:02 by alkozma          ###   ########.fr       */
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
			if ((i > 3 && FILLED(arr[i - 4])) || FILLED(arr[i + 4]))
				connections++;
			if ((i > 0 && FILLED(arr[i - 1])) || FILLED(arr[i + 1]))
				connections++;
		}
	}
	CHECK_BAD(squares != 4 || (connections != 8 && connections != 6));
	return (1);
}

int		**construct_tetrimino(char *line)
{
	int		xy[2];
	int		squares;
	int		startxy[2];
	int		**ret;

	xy[0] = 0;
	xy[1] = 0;
	squares = 0;
	MEMCHK((ret = (int**)malloc(sizeof(int*) * 5)));
	while (*line)
	{
		MEMCHK((ret[squares] = (int*)malloc(sizeof(int) * 3)));
		if (FILLED(*line++) == 1)
		{
			startxy[0] = squares == 0 ? xy[0] : startxy[0];
			startxy[1] = squares == 0 ? xy[1] : startxy[1];
			ret[squares][0] = squares == 0 ? 0 : xy[0] - startxy[0];
			ret[squares][1] = squares == 0 ? 0 : startxy[1] - xy[1];
			ret[squares++][2] = 0;
		}
		xy[1] += (++xy[0] / 4);
		xy[0] %= 4;
	}
	ret[squares] = NULL;
	return (ret);
}


