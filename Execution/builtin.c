/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 23:18:06 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/23 20:50:05 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtincheck(char *name)
{
	if (!ft_strcmp(name, "echo") || !ft_strcmp(name, "cd")
		|| !ft_strcmp(name, "pwd") || !ft_strcmp(name, "export")
		|| !ft_strcmp(name, "unset") || !ft_strcmp(name, "env")
		|| !ft_strcmp(name, "exit"))
		return (0);
	return (1);
}

int	builtin(t_vars *var, t_final *node)
{
	if (!ft_strcmp(node->cmd[0], "echo"))
		return (echo(node));
	else if (!ft_strcmp(node->cmd[0], "cd"))
		return (cd(var, node));
	else if (!ft_strcmp(node->cmd[0], "pwd"))
		return (pwd(node));
	else if (!ft_strcmp(node->cmd[0], "export"))
		return (export(var, node));
	else if (!ft_strcmp(node->cmd[0], "unset"))
		return (unset(var, node));
	else if (!ft_strcmp(node->cmd[0], "env"))
		return (environment(var, node));
	else if (!ft_strcmp(node->cmd[0], "exit"))
		return (exiting(node));
	return (1);
}
