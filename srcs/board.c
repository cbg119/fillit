/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 13:58:29 by alkozma           #+#    #+#             */
/*   Updated: 2019/02/21 03:42:49 by alkozma          ###   ########.fr       */
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

int		can_place(char **board, int **tet, int x, int y)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (!board[y - tet[i][1]] ||
				!board[y - tet[i][1]][x - tet[i][0]] ||
				!EMPTY(board[y - tet[i][1]][x - tet[i][0]]))
			return (0);
		i++;
	}
	return (1);
}

void	place_tet(char **board, int **tet, int x, int y, int num)
{
	int		sq;

	sq = -1;
	while (tet[++sq])
		board[y - tet[sq][1]][x - tet[sq][0]] = (num + 'A');
}

int		is_placed(int num, char **board)
{
	int i;

	i = 0;
	while (board[i])
		if (ft_strchr(board[i++], (num + 'A')))
			return (1);
	return (0);
}

void	rem_tet(char **board, int num)
{
	int i;

	i = 0;
	while (board[i])
		ft_tokreplc(board[i++], (num + 'A'), '.');
}
