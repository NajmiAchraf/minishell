/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterate_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:52:36 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/24 14:56:18 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	list_size1(t_final *list)
{
	t_final	*tmp;
	int		i;

	if (!list)
		return (0);
	i = 1;
	tmp = list;
	while (tmp->next)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

static void	create_pipe(t_final **node, t_allways w)
{
	int	p[2];

	pipe(p);
	if (w.i == 1)
		(*node)->infile = 0;
	if ((*node)->outfile == -1)
		(*node)->outfile = p[1];
	if (w.i < w.len)
	{
		if ((*node)->next->infile == -1)
			(*node)->next->infile = p[0];
	}
	if (w.i == w.len)
		(*node)->outfile = 1;
}

int	iterate_pipes(t_final **node)
{
	t_allways	w;
	t_final		*n;

	w.i = 1;
	n = *node;
	w.len = list_size1(n);
	while (n)
	{
		create_pipe(&n, w);
		n = n->next;
		w.i++;
	}
	return (w.len);
}
