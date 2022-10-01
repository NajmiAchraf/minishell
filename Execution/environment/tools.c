/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 01:20:26 by anajmi            #+#    #+#             */
/*   Updated: 2022/10/01 11:45:24 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sort_export(t_vars *var)
{
	t_allways	aws;

	aws.i = -1;
	while (++aws.i < var->env.sizeofexp - 1)
	{
		if (ft_strcmp(var->env.newexp[aws.i][0],
			var->env.newexp[aws.i + 1][0]) > 0)
		{
			ft_swap_tp(&var->env.newexp[aws.i], &var->env.newexp[aws.i + 1]);
			aws.i = -1;
		}
	}
}

char	*get_env_var(t_vars *var, char *to_get)
{
	t_allways	aws;

	if (!ft_strcmp("?", to_get))
		return (ft_itoa(g_status));
	else if (!ft_strcmp("0", to_get))
		return (ft_strdup(var->main_name));
	aws.i = -1;
	while (++aws.i < var->env.sizeofexp)
	{
		if (!ft_strcmp(var->env.newexp[aws.i][0], to_get))
			return (ft_strdup(var->env.newexp[aws.i][1]));
	}
	return (ft_strdup(""));
}

int	check_env_var(t_vars *var, char *to_check)
{
	t_allways	aws;

	if (!ft_strcmp("?", to_check) || !ft_strcmp("0", to_check))
		return (0);
	aws.j = -1;
	while (++aws.j < var->env.sizeofexp)
	{
		if (!ft_strcmp(var->env.newexp[aws.j][0], to_check))
			return (0);
	}
	return (1);
}
