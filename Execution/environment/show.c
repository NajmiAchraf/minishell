/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 01:19:25 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/22 21:55:38 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	show_env(t_vars *var, t_final *node)
{
	t_allways	aws;

	aws.i = 0;
	while (aws.i < var->env.sizeofenv)
	{
		ft_putstr_fd(var->env.newenv[aws.i], node->outfile);
		ft_putstr_fd("\n", node->outfile);
		aws.i++;
	}
}

void	show_exp(t_vars *var, t_final *node)
{
	t_allways	aws;

	aws.i = 0;
	while (aws.i < var->env.sizeofexp)
	{
		if (!var->env.newexp[aws.i][1])
		{
			ft_putstr_fd("declare -x ", node->outfile);
			ft_putstr_fd(var->env.newexp[aws.i][0], node->outfile);
			ft_putstr_fd("\n", node->outfile);
		}
		else
		{
			ft_putstr_fd("declare -x ", node->outfile);
			ft_putstr_fd(var->env.newexp[aws.i][0], node->outfile);
			ft_putstr_fd("=", node->outfile);
			ft_putstr_fd("\"", node->outfile);
			ft_putstr_fd(var->env.newexp[aws.i][1], node->outfile);
			ft_putstr_fd("\"\n", node->outfile);
		}
		aws.i++;
	}
}
