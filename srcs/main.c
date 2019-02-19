/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 19:21:17 by cbagdon           #+#    #+#             */
/*   Updated: 2019/02/19 14:38:05 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

int		main(int argc, char *argv[])
{
	int		fd;
	int		tetriminos;
	char	**board;

	(void)argc;
	tetriminos = 0;
	fd = open(argv[1], O_RDONLY);
	if (validate_file(fd, 0, 0, &tetriminos))
	{
		close(fd);
		board = make_array(tetriminos, argv[1]);
		print_array(board, tetriminos);
	}
	return (0);
}
