/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 13:40:58 by cbagdon           #+#    #+#             */
/*   Updated: 2019/02/18 16:08:40 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "../includes/fillit.h"

static int		validate_file(int fd, int chars, int lines)
{
	char	buf;

	while (read(fd, &buf, 1))
	{
		CHECK_BAD(!VALID_CHAR(buf));
		if (buf == '\n')
		{
			lines++;
			read(fd, &buf, 1);
			CHECK_BAD(chars != 4 || (buf == '\n' && lines != 4) ||
					!VALID_CHAR(buf));
			chars = 0;
			if (buf == '\n' && lines == 4)
				lines = 0;
			else
				chars++;
		}
		else
			chars++;
	}
	return (1);
}

int		main(int argc, char *argv[])
{
	(void)argc;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (validate_file(fd, 0, 0))
		printf("OK\n");
	else
		printf("NOPE\n");
	return (0);
}
