/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetriminos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 07:21:19 by alkozma           #+#    #+#             */
/*   Updated: 2019/02/21 07:21:22 by alkozma          ###   ########.fr       */
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
