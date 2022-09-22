/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 01:23:24 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/22 01:37:23 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	unset_env(t_vars *var, char *to_del)
{
	t_allways	aws;

	aws.i = -1;
	while (++aws.i < var->env.sizeofenv)
	{
		ft_free(var->tmpp);
		var->tmpp = ft_split(var->env.newenv[aws.i], '=');
		if (ft_strcmp(var->tmpp[0], to_del) == 0)
		{
			free(var->env.newenv[aws.i]);
			var->env.newenv[aws.i] = "~";
			--aws.i;
			while (++aws.i < var->env.sizeofenv - 1)
				ft_swap_dp(&var->env.newenv[aws.i],
					&var->env.newenv[aws.i + 1]);
			var->env.newenv[aws.i] = NULL;
			var->env.sizeofenv = ft_lstlen(var->env.newenv);
			break ;
		}
	}
}

static void	unset_export(t_vars *var, char *to_del)
{
	t_allways	aws;

	aws.i = -1;
	while (++aws.i < var->env.sizeofexp)
	{
		if (ft_strcmp(var->env.newexp[aws.i][0], to_del) == 0)
		{
			free(var->env.newexp[aws.i][0]);
			var->env.newexp[aws.i][0] = "~";
			free(var->env.newexp[aws.i][1]);
			var->env.newexp[aws.i][1] = NULL;
			var->env.newexp[aws.i][2] = NULL;
			sort_export(var);
			var->env.newexp[var->env.sizeofexp - 1][0] = NULL;
			free(var->env.newexp[var->env.sizeofexp - 1]);
			var->env.newexp[var->env.sizeofexp - 1] = NULL;
			var->env.sizeofexp = ft_lstslen(var->env.newexp);
			break ;
		}
	}
}

void	ft_unset(t_vars *var, char *to_del)
{
	unset_env(var, to_del);
	unset_export(var, to_del);
}
