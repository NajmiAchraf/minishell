/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:52:36 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/24 17:54:57 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	node_close(t_final *node)
{
	if (node->infile != 0)
		close(node->infile);
	if (node->outfile != 1)
		close(node->outfile);
}

void	full_close(t_final **node)
{
	t_final		*n;

	n = *node;
	while (n)
	{
		node_close(n);
		n = n->next;
	}
}

void	duping(t_final **node)
{
	if ((*node)->infile != 0)
	{
		if (dup2((*node)->infile, 0) == -1)
			trouble_exit("dup2", NULL, "failed", 1);
		close((*node)->infile);
	}
	if ((*node)->outfile != 1)
	{
		if (dup2((*node)->outfile, 1) == -1)
			trouble_exit("dup2", NULL, "failed", 1);
		close((*node)->outfile);
	}
}

void	wait_status(t_vars *var, t_allways w)
{
	waitpid(var->pid[w.j], &w.status, 0);
	if (WIFEXITED(w.status))
		g_status = WEXITSTATUS(w.status);
	if (w.status == 2)
		g_status = 128 + w.status;
	else if (w.status == 3)
	{
		printf("Quit: %d\n", w.status);
		g_status = 128 + w.status;
	}
}
