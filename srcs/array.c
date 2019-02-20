/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 18:27:56 by cbagdon           #+#    #+#             */
/*   Updated: 2019/02/19 22:09:55 by alkozma          ###   ########.fr       */
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
	int		**container;
	int		cursq;

	i = 0;
	while (i < tet_count)
	{
		cursq = 0;
		container = construct_tetrimino(board[i]);
		while (container[cursq] != NULL)
		{
			ft_putnbr(container[cursq][0]);
			ft_putstr(" , ");
			ft_putnbr(container[cursq++][1]);
			ft_putchar('\n');
		}
		ft_putstr(board[i]);
		ft_putnbr(valid_tetrimino(board[i]));
		ft_putchar('\n');
		i++;
	}
}
