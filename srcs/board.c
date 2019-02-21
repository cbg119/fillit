/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 07:23:23 by alkozma           #+#    #+#             */
/*   Updated: 2019/02/21 09:08:03 by alkozma          ###   ########.fr       */
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

int		print_board(char **board)
{
	while (*board)
	{
		ft_putstr(*board++);
		ft_putchar('\n');
	}
	return (1);
}

int		solve_board(char **board, int ***tets, int tet_num)
{
	int i;
	int xy[2];

	ZERO_OUT(xy[0], xy[1], i);
	ITERATE((is_placed(i, board)), i);
	CHECK_BAD(!find_and_place(board, tets[i], xy[0], xy[1]));
	if (is_solved(board, tet_num))
		return (print_board(board));
	while (!solve_board(board, tets, tet_num))
	{
		rem_tet(board, i);
		adv_xy((int)ft_strlen(board[0]), &xy[0], &xy[1]);
		while (!can_place(board, tets[i], xy[0], xy[1]))
		{
			adv_xy((int)ft_strlen(board[0]), &xy[0], &xy[1]);
			if (xy[1] > (int)ft_strlen(board[0]))
			{
				CHECK_BAD(i != 0);
				ZERO_OUT(xy[0], xy[1], i);
				board = grow_board(board);
			}
		}
		place_tet(board, tets[i], xy[0], xy[1]);
	}
	return (1);
}
