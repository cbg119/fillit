/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 07:54:19 by alkozma           #+#    #+#             */
/*   Updated: 2019/02/22 17:14:54 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	adv_xy(int board_len, int *x, int *y)
{
	*y += (++*x / board_len);
	*x %= board_len;
}

void	zero_out(int *a, int *b, int *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}

int		min_square(int ***container)
{
	int ret;
	int a;
	int b;

	zero_out(&ret, &a, &b);
	while (container[a])
	{
		while (container[a][b])
		{
			if (ABS(container[a][b][0]) > ret)
				ret = ABS(container[a][b][0]);
			if (ABS(container[a][b][1]) > ret)
				ret = ABS(container[a][b][1]);
			b++;
		}
		a++;
	}
	return (ret + 1);
}
