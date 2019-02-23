/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 13:40:05 by cbagdon           #+#    #+#             */
/*   Updated: 2019/02/22 16:56:40 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

/*
**	***********
**	INCLUDES
**	***********
*/

# include "./libft/includes/libft.h"

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

/*
**	***********
*/

/*
**	***********
**	MACROS
**	***********
*/

# define FILLED(c)				((c - '#' == 0) ? 1 : -1)
# define EMPTY(c)				((c - '.' == 0) ? 1 : 0)
# define CHECK_BAD(x)			if (x) return (0)
# define VALID_CHAR(c)			((c == '#' || c == '.' || c == '\n') ? 1 : 0)
# define ITERATE(a, b)			while (a) (b++)

/*
**	***********
*/

/*
**	***********
**	PROTOTYPES
**	***********
*/

char			**fill_array(char **tetriminos, int fd);
void			print_array(char **board, int tet_count);
void			place_tet(char **board, int **tet, int x, int y);
int				print_board(char **board);
void			rem_tet(char **board, int num);
void			adv_xy(int board_len, int *x, int *y);
int				**construct_tetrimino(char *line, int num);
int				validate_file(int fd, int chars, int lines, int *tetriminos);
char			**make_array(int tetriminos, char *file);
int				valid_tetrimino(char *arr);
int				***build_offset_arr(char **board, int tet_count);
int				can_place(char **board, int **tet, int x, int y);
int				solve_board(char **board, int ***tets, int tet_num);
int				is_placed(int num, char **board);
int				find_and_place(char **board, int **tet, int x, int y);
int				count_chars(char *str, char c);
int				min_square(int ***container);
char			**grow_board(char **board);
char			**init_board(int tetriminos, int minsq);
void			zero_out(int *a, int *b, int *c);

#endif
