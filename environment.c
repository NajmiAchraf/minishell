/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:39:54 by anajmi            #+#    #+#             */
/*   Updated: 2022/06/22 17:04:10 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_export(t_vars *var)
{
	var->i = -1;
	while (++var->i < var->sizeofexp - 1)
	{
		if (ft_strcmp(var->newexp[var->i][0], var->newexp[var->i + 1][0]) > 0)
		{
			ft_swap(&var->newexp[var->i], &var->newexp[var->i + 1]);
			var->i = -1;
		}
	}
}

void	init_environment(t_vars *var)
{
	var->i = 0;
	var->newenv = malloc(sizeof(char *) * 1024);
	while (var->env[var->i])
	{
		var->newenv[var->i] = ft_strdup(var->env[var->i]);
		var->i++;
	}
	var->newenv[var->i] = NULL;
	var->sizeofenv = ft_lstlen(var->newenv);
}

void	init_export(t_vars *var)
{
	var->i = 0;
	var->newexp = malloc(sizeof(char **) * 1024);
	while (var->env[var->i])
	{
		var->newexp[var->i] = malloc(sizeof(char *) * 3);
		var->newexp[var->i][0] = ft_strdup(ft_split(var->env[var->i], '=')[0]);
		var->newexp[var->i][1] = ft_strdup(ft_strchr(var->env[var->i], '=') + 1);
		var->newexp[var->i][2] = NULL;
		var->i++;
	}
	var->newexp[var->i] = NULL;
	var->sizeofexp = ft_lstslen(var->newexp);
	sort_export(var);
}

void	show_env(t_vars *var)
{
	var->i = 0;
	while (var->i < var->sizeofenv)
	{
		printf("%s\n", var->newenv[var->i]);
		var->i++;
	}
}

void	show_exp(t_vars *var)
{
	var->i = 0;
	while (var->i < var->sizeofexp)
	{
		if (!var->newexp[var->i][1])
			printf("declare -x %s\n", var->newexp[var->i][0]);
		else
			printf("declare -x %s=\"%s\"\n", var->newexp[var->i][0], var->newexp[var->i][1]);
		var->i++;
	}
}

void	ft_export(t_vars *var, char *to_add)
{
	var->newexp[var->sizeofexp] = malloc(sizeof(char *) * 3);
	var->newexp[var->sizeofexp][0] = ft_strdup(ft_split(to_add, '=')[0]);
	if (ft_strchr(to_add, '='))
	{
		var->newexp[var->sizeofexp][1] = ft_strdup(ft_strchr(to_add, '=') + 1);
		var->newexp[var->sizeofexp][2] = NULL;
		var->newenv[var->sizeofenv] = ft_strdup(to_add);
	}
	else
		var->newexp[var->sizeofexp][1] = NULL;

	var->newexp[var->sizeofexp + 1] = NULL;
	var->sizeofexp = ft_lstslen(var->newexp);
	sort_export(var);

	var->newenv[var->sizeofenv + 1] = NULL;
	var->sizeofenv = ft_lstlen(var->newenv);
}

void	ft_unset(t_vars *var, char *to_del)
{
	if (ft_strcmp(ft_split(var->newenv[var->sizeofenv - 1], '=')[0], to_del) == 0)
	{
		free(var->newenv[var->sizeofenv - 1]);
		var->newenv[var->sizeofenv - 1] = NULL;
		var->sizeofenv = ft_lstlen(var->newenv);
	}
	var->i = -1;
	while (++var->i < var->sizeofexp - 1)
	{
		if (ft_strcmp(var->newexp[var->i][0], to_del) == 0)
		{
			free(var->newexp[var->i][0]);
			free(var->newexp[var->i][1]);
			var->newexp[var->i][0] = "~";
			var->newexp[var->i][1] = NULL;
			sort_export(var);
			free(var->newexp[var->sizeofexp - 1]);
			var->newexp[var->sizeofexp - 1][0] = NULL;
			var->newexp[var->sizeofexp - 1] = NULL;
			var->sizeofexp = ft_lstslen(var->newexp);
			break;
		}
	}
}