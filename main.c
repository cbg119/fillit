/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 19:21:17 by cbagdon           #+#    #+#             */
/*   Updated: 2019/02/22 17:29:30 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		main(int argc, char *argv[])
{
	int		fd;
	int		tetriminos;

	if (argc == 2)
	{
		tetriminos = 0;
		fd = open(argv[1], O_RDONLY);
		if (validate_file(fd, 0, 0, &tetriminos))
		{
			close(fd);
			if (!make_array(tetriminos, argv[1]))
			{
				ft_putstr("error\n");
				return (1);
			}
		}
		else
		{
			ft_putstr("error\n");
			return (1);
		}
	}
	else
		ft_putstr("usage: fillit input_file\n");
	return (0);
}
