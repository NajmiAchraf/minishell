/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 01:18:54 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/22 01:38:56 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_environment(t_vars *var)
{
	t_allways	aws;

	aws.i = 0;
	var->env.newenv = malloc(sizeof(char *) * 4096);
	while (var->env.env[aws.i])
	{
		var->env.newenv[aws.i] = ft_strdup(var->env.env[aws.i]);
		aws.i++;
	}
	var->env.newenv[aws.i] = NULL;
	var->env.sizeofenv = ft_lstlen(var->env.newenv);
}

void	init_export(t_vars *var)
{
	t_allways	aws;

	aws.i = 0;
	var->env.newexp = malloc(sizeof(char **) * 4096);
	while (var->env.env[aws.i])
	{
		var->env.newexp[aws.i] = malloc(sizeof(char *) * 3);
		ft_free(var->tmpp);
		var->tmpp = ft_split(var->env.env[aws.i], '=');
		var->env.newexp[aws.i][0] = ft_strdup(var->tmpp[0]);
		var->env.newexp[aws.i][1] = \
		ft_strdup(ft_strchr(var->env.env[aws.i], '=') + 1);
		var->env.newexp[aws.i][2] = NULL;
		aws.i++;
	}
	var->env.newexp[aws.i] = NULL;
	var->env.sizeofexp = ft_lstslen(var->env.newexp);
	if (!var->env.env[0])
		return ;
	sort_export(var);
}
