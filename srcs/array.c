/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 18:27:56 by cbagdon           #+#    #+#             */
/*   Updated: 2019/02/20 16:17:04 by alkozma          ###   ########.fr       */
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
	return (tet_list);
}

/*
void	print_array(char **board, int tet_count)
{
	int		rows;
	int		columns;

	rows = 0;
	while (rows < tet_count)
	{
		columns = 0;
		while (board[rows][columns])
		{
			ft_putchar(board[rows][columns]);
			columns++;
			if (columns % 4 == 0)
				ft_putchar('\n');
		}
		if (rows != tet_count - 1)
			ft_putchar('\n');
		rows++;
	}
}
*/

void	print_array(char **board, int tet_count)
{
	int		i;
	int		***container;

	i = 0;
	container = build_offset_arr(board, tet_count);
	while (i < tet_count)
	{
		ft_putstr(board[i]);
		ft_putnbr(valid_tetrimino(board[i]));
		ft_putchar('\n');
		i++;
	}
	i = 0;
	board = init_board(tet_count);
	i = 0;
	while (board[i])
	{
		ft_putstr(board[i++]);
		ft_putchar('\n');
	}
	print_board(board, tet_count, container);
}
	
int		***build_offset_arr(char **board, int tet_count)
{
	int		i;
	int		***ret;

	i = -1;
	MEMCHK((ret = (int***)malloc(sizeof(int**) * (tet_count + 1))));
	while (++i < tet_count)
		ret[i] = construct_tetrimino(board[i]);
	ret[i] = NULL;
	return (ret);
}

void	print_board(char **board, int tet_count, int ***container)
{
	int tet;
	size_t x;
	size_t y;
	int num;

	tet = 0;
	x = 0;
	y = 0;
	num = 0;
	tet_count++;
	while (container[tet])
	{
		if (x > ft_strlen(board[0]) || y > ft_strlen(board[0]))
		{
			board = grow_board(board);
			tet = 0;
			x = 0;
			y = 0;
			num = 0;
		}
		if (can_place(board, container[tet], x, y))
			place_tet(board, container[tet++], x, y, num++);
		y += (++x / ft_strlen(board[0]));
		x %= ft_strlen(board[0]);
	}
	while (*board)
	{
		ft_putstr(*board++);
		ft_putchar('\n');
	}
	ft_putnbr(num);
}
