/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:52:36 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/24 17:12:32 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	executor(t_vars *var, t_final **node)
{
	t_allways	w;
	t_final		*n;

	w.i = 0;
	w.j = 0;
	w.k = 1;
	n = *node;
	w.len = iterate_pipes(node);
	iterate_files(var, node);
	while (n)
	{
		if (n->cmd[0])
		{
			if (w.len == 1 && !builtincheck(n->cmd[0]))
			{
				g_status = builtin(var, n);
				if (g_status == 1)
					trouble("builtin", n->cmd[0], "failed", 1);
				full_close(node);
			}
			else if (w.len <= 200)
			{
    			signal(SIGINT, SIG_IGN);
				var->pid[w.j] = ft_fork();
				if (var->pid[w.j] == 0)
				{
					signal(SIGINT, SIG_DFL);
					signal(SIGQUIT, SIG_DFL);
					duping(&n);
					full_close(node);
					if (!builtincheck(n->cmd[0]))
					{
						n->infile = 0;
						n->outfile = 1;
						g_status = builtin(var, n);
						if (g_status == 1)
							trouble_exit("builtin", n->cmd[0], "failed", 1);
						exit(0);
					}
					execve(exe_path_set(var, n->cmd[0]), n->cmd, var->env.newenv);
					trouble_exit("execve", n->cmd[0], "failed", 1);
				}
				else if (var->pid[w.j] == -1)
				{
					full_close(node);
					ft_signals();
					return ;
				}
				node_close(n);
				w.k = 0;
			}
			else
			{
				trouble("fork", NULL, "Resource temporarily unavailable", 1);
				return ;
			}
		}
		// else
		// 	printf("minishell: %s No such file or directory\n", n->cmd[0]);
		n = n->next;
		w.i++;
		w.j++;
	}
	if (w.k == 0)
	{
		w.j = 0;
		n = *node;
		while (n)
		{
			wait_status(var, w);
			n = n->next;
			w.j++;
		}
	}
	ft_signals();
	full_close(node);
}
