/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 07:23:23 by alkozma           #+#    #+#             */
/*   Updated: 2019/02/21 07:24:47 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

char	**init_board(int tetriminos)
{
	char	**ret;
	int		sqsz;
	int		x;
	int		y;

	sqsz = 0;
	while (sqsz * sqsz < tetriminos * 4)
		sqsz += 1;
	MEMCHK((ret = (char**)malloc(sizeof(char*) * (sqsz + 1))));
	y = -1;
	while (++y < sqsz)
	{
		x = -1;
		MEMCHK((ret[y] = (char*)malloc(sizeof(char) * (sqsz + 1))));
		while (++x < sqsz)
			ret[y][x] = '.';
		ret[y][x] = '\0';
	}
	ret[y] = NULL;
	return (ret);
}

char	**grow_board(char **board)
{
	int		size;
	char	**ret;
	int		x;
	int		y;
	int		i;

	size = ft_strlen(board[0]) + 1;
	y = -1;
	MEMCHK((ret = (char**)malloc(sizeof(char*) * (size + 1))));
	while (++y < size)
	{
		x = -1;
		MEMCHK((ret[y] = (char*)malloc(sizeof(char) * (size + 1))));
		while (++x < size)
			ret[y][x] = '.';
		ret[y][x] = '\0';
	}
	i = 0;
	while (board[i])
		ft_strdel(&board[i]);
	board[size + 1] = NULL;
	ft_memdel((void**)&board);
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
				while (is_placed(i, board))
					i++;
			}
		}
		place_tet(board, tets[i], x, y, i);
	}
	return (1);
}
