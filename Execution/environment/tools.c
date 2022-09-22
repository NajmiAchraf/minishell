/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 01:20:26 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/22 01:28:28 by anajmi           ###   ########.fr       */
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

	aws.i = -1;
	while (++aws.i < var->env.sizeofexp)
	{
		if (!ft_strcmp(var->env.newexp[aws.i][0], to_get))
			return (var->env.newexp[aws.i][1]);
	}
	return (ft_strdup(""));
}

int	check_env_var(t_vars *var, char *to_check)
{
	t_allways	aws;

	aws.j = -1;
	while (++aws.j < var->env.sizeofexp)
	{
		if (!ft_strcmp(var->env.newexp[aws.j][0], to_check))
			return (0);
	}
	return (1);
}
