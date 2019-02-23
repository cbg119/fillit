/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:39:52 by cbagdon           #+#    #+#             */
/*   Updated: 2019/02/21 12:02:52 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	line_cleanse(int *lines, int *tetriminos)
{
	*lines = 0;
	*tetriminos += 1;
}

int		validate_file(int fd, int chars, int lines, int *tetriminos)
{
	int		new_lines;
	char	buf;

	new_lines = 0;
	while (read(fd, &buf, 1))
	{
		CHECK_BAD(!VALID_CHAR(buf));
		if (buf == '\n')
		{
			lines++;
			new_lines++;
			new_lines += (read(fd, &buf, 1) && buf == '\n') ? 1 : 0;
			CHECK_BAD(chars != 4 || (buf == '\n' && lines != 4) ||
					!VALID_CHAR(buf));
			chars = 0;
			if (buf == '\n' && lines == 4)
				line_cleanse(&lines, tetriminos);
			else
				chars++;
		}
		else
			chars++;
	}
	CHECK_BAD(lines > 0 || new_lines != *tetriminos * 4 + *tetriminos - 1);
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
