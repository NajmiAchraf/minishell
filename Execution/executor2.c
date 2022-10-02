/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:52:36 by anajmi            #+#    #+#             */
/*   Updated: 2022/10/02 15:40:16 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	terminate(t_final **node, int rtn)
{
	full_close(node);
	ft_signals();
	return (rtn);
}

int	execute_fork(t_vars *var, t_final **node, t_final **n, t_allways w)
{
	signal(SIGINT, SIG_IGN);
	var->pid[w.j] = ft_fork();
	if (var->pid[w.j] == 0)
		execute_execve_fork(var, node, n);
	else if (var->pid[w.j] == -1)
		return (terminate(node, 1));
	node_close(*n);
	return (0);
}

int	executor_core(t_vars *var, t_final **node, t_allways w)
{
	t_final		*n;

	n = *node;
	while (n)
	{
		if (n->cmd && n->cmd[0] && n->cmd[0][0] != '\0')
		{
			if (w.len == 1 && !builtincheck(n->cmd[0]))
				execute_builtin(var, node);
			else if (w.len <= 200)
				w.k = execute_fork(var, node, &n, w);
			else
				return (trouble("fork", NULL,
						"Resource temporarily unavailable", 1));
		}
		else if (n->cmd && n->cmd[0] && n->cmd[0][0] == '\0')
			trouble("", NULL, "command not found", 127);
		n = n->next;
		w.i++;
		w.j++;
	}
	if (w.k == 0)
		waiting(var, node);
	return (0);
}

int	executor(t_vars *var, t_final **node)
{
	t_allways	w;

	w.i = 0;
	w.j = 0;
	w.k = 1;
	var->infile = -1;
	if (iterate_heredoc(var, node))
		return (terminate(node, 1));
	w.len = iterate_pipes(node);
	if (iterate_files(var, node))
		return (terminate(node, 1));
	executor_core(var, node, w);
	return (terminate(node, 0));
}
