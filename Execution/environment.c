/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 23:17:30 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/24 10:50:42 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export(t_vars *var, t_final *node)
{
	t_allways	aws;

	aws.j = 0;
	if (!node->cmd[1])
		show_exp(var, node);
	else
	{
		aws.i = 1;
		while (node->cmd[aws.i])
		{
			aws.k = ft_export(var, node->cmd[aws.i], 0);
			if (aws.k == 1)
				aws.j = 1;
			aws.i++;
		}
	}
	return (aws.j);
}

int	unset(t_vars *var, t_final *node)
{
	t_allways	aws;

	aws.i = 1;
	aws.j = 0;
	while (node->cmd[aws.i])
	{
		if (little_checker(node->cmd[aws.i]))
		{
			trouble("unset", node->cmd[aws.i], "not a valid identifier", 1);
			aws.j = 1;
		}
		else
			ft_unset(var, node->cmd[aws.i]);
		aws.i++;
	}
	return (aws.j);
}

int	environment(t_vars *var, t_final *node)
{
	t_allways	aws;

	aws.i = 1;
	while (node->cmd[aws.i])
	{
		if (ft_strcmp(node->cmd[aws.i], "env"))
		{
			trouble("env", node->cmd[aws.i], "No such file or directory", 1);
			return (1);
		}
		aws.i++;
	}
	show_env(var, node);
	return (0);
}
