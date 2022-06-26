/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:39:54 by anajmi            #+#    #+#             */
/*   Updated: 2022/06/23 21:50:44 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_export(t_vars *var)
{
	var->i = -1;
	while (++var->i < var->env.sizeofexp - 1)
	{
		if (ft_strcmp(var->env.newexp[var->i][0], var->env.newexp[var->i + 1][0]) > 0)
		{
			ft_swap_tp(&var->env.newexp[var->i], &var->env.newexp[var->i + 1]);
			var->i = -1;
		}
	}
}

void	init_environment(t_vars *var)
{
	var->i = 0;
	var->env.newenv = malloc(sizeof(char *) * 1024);
	while (var->env.env[var->i])
	{
		var->env.newenv[var->i] = ft_strdup(var->env.env[var->i]);
		var->i++;
	}
	var->env.newenv[var->i] = NULL;
	var->env.sizeofenv = ft_lstlen(var->env.newenv);
}

void	init_export(t_vars *var)
{
	var->i = 0;
	var->env.newexp = malloc(sizeof(char **) * 1024);
	while (var->env.env[var->i])
	{
		var->env.newexp[var->i] = malloc(sizeof(char *) * 3);
		free(var->temp);
		var->temp = ft_split(var->env.env[var->i], '=');
		var->env.newexp[var->i][0] = ft_strdup(var->temp[0]);
		var->env.newexp[var->i][1] = ft_strdup(ft_strchr(var->env.env[var->i], '=') + 1);
		var->env.newexp[var->i][2] = NULL;
		var->i++;
	}
	var->env.newexp[var->i] = NULL;
	var->env.sizeofexp = ft_lstslen(var->env.newexp);
	sort_export(var);
}

void	show_env(t_vars *var)
{
	var->i = 0;
	while (var->i < var->env.sizeofenv)
	{
		printf("%s\n", var->env.newenv[var->i]);
		var->i++;
	}
}

void	show_exp(t_vars *var)
{
	var->i = 0;
	while (var->i < var->env.sizeofexp)
	{
		if (!var->env.newexp[var->i][1])
			printf("declare -x %s\n", var->env.newexp[var->i][0]);
		else
			printf("declare -x %s=\"%s\"\n", var->env.newexp[var->i][0], var->env.newexp[var->i][1]);
		var->i++;
	}
}

void	ft_export(t_vars *var, char *to_add)
{
	var->env.newexp[var->env.sizeofexp] = malloc(sizeof(char *) * 3);
	free(var->temp);
	var->temp = ft_split(to_add, '=');
	var->env.newexp[var->env.sizeofexp][0] = ft_strdup(var->temp[0]);
	if (ft_strchr(to_add, '='))
	{
		var->env.newexp[var->env.sizeofexp][1] = ft_strdup(ft_strchr(to_add, '=') + 1);
		var->env.newexp[var->env.sizeofexp][2] = NULL;
		var->env.newenv[var->env.sizeofenv] = ft_strdup(to_add);
	}
	else
		var->env.newexp[var->env.sizeofexp][1] = NULL;

	var->env.newexp[var->env.sizeofexp + 1] = NULL;
	var->env.sizeofexp = ft_lstslen(var->env.newexp);
	sort_export(var);

	var->env.newenv[var->env.sizeofenv + 1] = NULL;
	var->env.sizeofenv = ft_lstlen(var->env.newenv);
}

void	ft_unset(t_vars *var, char *to_del)
{
	var->i = -1;
	while (++var->i < var->env.sizeofenv - 1)
	{
		free(var->temp);
		var->temp = ft_split(var->env.newenv[var->i], '=');
		if (ft_strcmp(var->temp[0], to_del) == 0)
		{
			free(var->env.newenv[var->i]);
			var->env.newenv[var->i] = "~";
			--var->i;
			while (++var->i < var->env.sizeofenv - 2)
				ft_swap_dp(&var->env.newenv[var->i], &var->env.newenv[var->i + 1]);
			var->env.newenv[var->i] = NULL;
			var->env.sizeofenv = ft_lstlen(var->env.newenv);
			break;
		}
	}
	var->i = -1;
	while (++var->i < var->env.sizeofexp - 1)
	{
		if (ft_strcmp(var->env.newexp[var->i][0], to_del) == 0)
		{
			free(var->env.newexp[var->i][0]);
			var->env.newexp[var->i][0] = "~";
			
			free(var->env.newexp[var->i][1]);
			var->env.newexp[var->i][1] = NULL;
			var->env.newexp[var->i][2] = NULL;

			sort_export(var);
			
			var->env.newexp[var->env.sizeofexp - 1][0] = NULL;
			
			free(var->env.newexp[var->env.sizeofexp - 1]);
			var->env.newexp[var->env.sizeofexp - 1] = NULL;
			
			var->env.sizeofexp = ft_lstslen(var->env.newexp);
			break;
		}
	}
}

char	*get_env_var(t_vars *var, char *to_get)
{
	var->i = -1;
	while (++var->i < var->env.sizeofexp - 1)
	{
		if (!ft_strcmp(var->env.newexp[var->i][0], to_get))
			return (var->env.newexp[var->i][1]);
	}
	return (0);
}