/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetriminos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 07:21:19 by alkozma           #+#    #+#             */
/*   Updated: 2019/02/22 14:49:05 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

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

void	place_tet(char **board, int **tet, int x, int y)
{
	int		sq;
	int		num;

	sq = -1;
	num = 0;
	if (is_placed(0, board))
		while (is_placed(num, board))
			num++;
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

int		find_and_place(char **board, int **tet, int x, int y)
{
	int		i;

	i = 0;
	if (is_placed(0, board))
		while (is_placed(i, board))
			i++;
	while (!is_placed(i, board))
	{
		while (!can_place(board, tet, x, y))
		{
			y += (++x / (int)ft_strlen(board[0]));
			x %= (int)ft_strlen(board[0]);
			if (y > (int)ft_strlen(board[0]))
				return (0);
		}
		place_tet(board, tet, x, y);
	}
	return (1);
}
