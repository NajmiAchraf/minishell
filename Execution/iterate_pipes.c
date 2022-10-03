/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterate_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:52:36 by anajmi            #+#    #+#             */
/*   Updated: 2022/10/03 18:35:34 by anajmi           ###   ########.fr       */
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

static int	*create_pipe(t_final **node, t_allways w)
{
	int	*p;

	p = (int *) malloc(2 * sizeof(int));
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
	return (p);
}

int	iterate_pipes(t_final **node)
{
	t_allways	w;
	t_final		*n;
	int			*p;

	w.i = 1;
	n = *node;
	w.len = list_size1(n);
	p = NULL;
	while (n)
	{
		free(p);
		p = create_pipe(&n, w);
		n = n->next;
		w.i++;
	}
	close(p[0]);
	close(p[1]);
	free(p);
	return (w.len);
}
