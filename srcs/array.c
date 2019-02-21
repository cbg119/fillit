/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 07:22:23 by alkozma           #+#    #+#             */
/*   Updated: 2019/02/21 07:24:14 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

char	**fill_array(char **tetriminos, int fd)
{
	int		rows;
	int		columns;
	int		lines;
	char	buffer;

	rows = 0;
	while (read(fd, &buffer, 1))
	{
		lines = 0;
		columns = 0;
		while (lines != 4)
		{
			if (buffer == '\n')
				lines++;
			else
			{
				tetriminos[rows][columns] = buffer;
				columns++;
			}
			read(fd, &buffer, 1);
		}
		tetriminos[rows][columns] = '\0';
		rows++;
	}
	return (tetriminos);
}

char	**make_array(int tetriminos, char *file)
{
	int		i;
	int		fd;
	char	**tet_list;
	int		***container;
	char	**board;

	i = 0;
	if (!(tet_list = (char **)malloc(sizeof(char *) * tetriminos)))
		return (NULL);
	while (i < tetriminos)
	{
		tet_list[i] = (char *)malloc(sizeof(char) * 17);
		i++;
	}
	fd = open(file, O_RDONLY);
	tet_list = fill_array(tet_list, fd);
	close(fd);
	if (!(container = build_offset_arr(tet_list, tetriminos)))
		return (0);
	board = init_board(tetriminos);
	solve_board(board, container, tetriminos);
	return (board);
}

int		***build_offset_arr(char **board, int tet_count)
{
	int		i;
	int		***ret;

	i = -1;
	MEMCHK((ret = (int***)malloc(sizeof(int**) * (tet_count + 1))));
	while (++i < tet_count)
	{
		CHECK_BAD(valid_tetrimino(board[i]));
		ret[i] = construct_tetrimino(board[i]);
	}
	ret[i] = NULL;
	return (ret);
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
			ret[squares][0] = squares == 0 ? 0 : startxy[0] - xy[0];
			ret[squares][1] = squares == 0 ? 0 : startxy[1] - xy[1];
			ret[squares++][2] = 0;
		}
		xy[1] += (++xy[0] / 4);
		xy[0] %= 4;
	}
	ret[squares] = NULL;
	return (ret);
}
