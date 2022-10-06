/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:52:36 by anajmi            #+#    #+#             */
/*   Updated: 2022/10/06 14:57:14 by anajmi           ###   ########.fr       */
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
	struct stat	dir_stat;
	int			folder;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	duping(n);
	full_close(node);
	if (!builtincheck((*n)->cmd[0]))
		execute_builtin_fork(var, n);
	folder = open(exe_path_set(var, (*n)->cmd[0]), O_RDONLY);
	if (fstat(folder, &dir_stat) > -1 && S_ISDIR(dir_stat.st_mode))
	{
		close(folder);
		trouble_exit((*n)->cmd[0], NULL, "is a directory", 126);
	}
	close(folder);
	execve(exe_path_set(var, (*n)->cmd[0]), (*n)->cmd, var->env.newenv);
	trouble_exit(NULL, (*n)->cmd[0], "command not found", 127);
}
