/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:52:36 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/26 17:21:01 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_builtin(t_vars *var, t_final **node)
{
	g_status = builtin(var, *node);
	full_close(node);
}

void	execute_builtin_fork(t_vars *var, t_final **node)
{
	(*node)->infile = 0;
	(*node)->outfile = 1;
	g_status = builtin(var, (*node));
	if (g_status == 1)
		trouble_exit("builtin", (*node)->cmd[0], "failed", 1);
	exit(0);
}

void	execute_execve_fork(t_vars *var, t_final **node, t_final **n)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	duping(n);
	full_close(node);
	if (!builtincheck((*n)->cmd[0]))
		execute_builtin_fork(var, n);
	execve(exe_path_set(var, (*n)->cmd[0]), (*n)->cmd, var->env.newenv);
	trouble_exit(NULL, (*n)->cmd[0], "command not found", 1);
}
