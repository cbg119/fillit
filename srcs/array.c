/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 18:27:56 by cbagdon           #+#    #+#             */
/*   Updated: 2019/02/21 04:41:12 by alkozma          ###   ########.fr       */
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

int		is_solved(char **board, int tet_num)
{
	int i;

	i = -1;
	while (++i < tet_num)
		if (!is_placed(i, board))
			return (0);
	return (1);
}

void	print_board(char **board)
{
	while (*board)
	{
		ft_putstr(*board++);
		ft_putchar('\n');
	}
}

int		solve_board(char **board, int ***tets, int tet_num)
{
	int i;
	int x;
	int y;

	i = 0;
	x = 0;
	y = 0;
	while (is_placed(i, board))
		i++;
	while (!is_placed(i, board))
	{
		while (!can_place(board, tets[i], x, y))
		{
			y += (++x / (int)ft_strlen(board[0]));
			x %= (int)ft_strlen(board[0]);
			if (y > (int)ft_strlen(board[0]))
				return (0);
		}
		place_tet(board, tets[i], x, y, i);
	}
	if (is_solved(board, tet_num))
	{
		print_board(board);
		return (1);
	}
	while (!solve_board(board, tets, tet_num))
	{
		if (is_placed(i, board))
			rem_tet(board, i);
		y += (++x / (int)ft_strlen(board[0]));
		x %= (int)ft_strlen(board[0]);
		while (!can_place(board, tets[i], x, y))
		{
			y += (++x / (int)ft_strlen(board[0]));
			x %= (int)ft_strlen(board[0]);
			if (y > (int)ft_strlen(board[0]))
			{
				if (i != 0)
					return (0);
				else
				{
					x = 0;
					y = 0;
					i = 0;
					board = grow_board(board);
				}
				while(is_placed(i, board))
					i++;
			}
		}
		place_tet(board, tets[i], x, y, i);
	}
	return (1);
}
