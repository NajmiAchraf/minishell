/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 01:19:25 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/22 01:42:49 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	show_env(t_vars *var)
{
	t_allways	aws;

	aws.i = 0;
	while (aws.i < var->env.sizeofenv)
	{
		printf("%s\n", var->env.newenv[aws.i]);
		aws.i++;
	}
}

void	show_exp(t_vars *var)
{
	t_allways	aws;

	aws.i = 0;
	while (aws.i < var->env.sizeofexp)
	{
		if (!var->env.newexp[aws.i][1])
			printf("declare -x %s\n", var->env.newexp[aws.i][0]);
		else
			printf("declare -x %s=\"%s\"\n",
				var->env.newexp[aws.i][0], var->env.newexp[aws.i][1]);
		aws.i++;
	}
}
