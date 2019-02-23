/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 19:21:17 by cbagdon           #+#    #+#             */
/*   Updated: 2019/02/22 16:55:47 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		main(int argc, char *argv[])
{
	int		fd;
	int		tetriminos;

	(void)argc;
	tetriminos = 0;
	fd = open(argv[1], O_RDONLY);
	if (validate_file(fd, 0, 0, &tetriminos))
	{
		close(fd);
		if (!make_array(tetriminos, argv[1]))
		{
			ft_putstr("error\n");
			return (0);
		}
	}
	else
		ft_putstr("error\n");
	return (0);
}
