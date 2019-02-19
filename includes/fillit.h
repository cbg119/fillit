/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 13:40:05 by cbagdon           #+#    #+#             */
/*   Updated: 2019/02/19 14:34:48 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H


/*	***********
**	INCLUDES
**	***********
*/

# include	"../libft/includes/libft.h"

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

/*
**	***********
*/

/*	***********
**	MACROS
**	***********
*/

# define FILLED(c)				((c - '#' == 0) ? 1 : -1)
# define CHECK_BAD(x)			if (x) return (0)
# define VALID_CHAR(c)			((c == '#' || c == '.' || c == '\n') ? 1 : 0)

/*
**	***********
*/

/*	***********
**	PROTOTYPES
**	***********
*/

char			**fill_array(char **tetriminos, int fd);
void			print_array(char **board, int tet_count);
int				validate_file(int fd, int chars, int lines, int *tetriminos);
char			**make_array(int tetriminos, char *file);
int				valid_tetrimino(char *arr);

#endif
