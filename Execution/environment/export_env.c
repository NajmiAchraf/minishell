/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:39:54 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/30 21:01:06 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	replace_variable(t_vars *var, char *to_check, char *value)
{
	t_allways	aws;

	aws.i = -1;
	while (++aws.i < var->env.sizeofexp)
	{
		if (!ft_strcmp(var->env.newexp[aws.i][0], to_check))
		{
			ft_unset(var, var->env.newexp[aws.i][0]);
			ft_export(var, value, 1);
			return (1);
		}
	}
	return (0);
}

int	little_checker(char *to_check)
{
	t_allways	aws;

	if (ft_isalpha(to_check[0]) || to_check[0] == '_')
	{
		aws.i = 0;
		while (to_check[++aws.i])
		{
			if (!ft_isalnum(to_check[aws.i]) && to_check[aws.i] != '_')
				return (1);
		}
	}
	else
		return (1);
	return (0);
}

int	validate_variable(t_vars *var, char *to_check)
{
	ft_free(var->tmpp);
	var->tmpp = ft_split(to_check, '=');
	if (var->tmpp[0] != NULL)
	{
		if (ft_strchr(to_check, '=') == NULL
			&& !check_env_var(var, var->tmpp[0]))
			return (0);
		else if (replace_variable(var, var->tmpp[0], to_check))
			return (0);
		if (little_checker(var->tmpp[0]))
			return (2);
	}
	else
		return (2);
	return (1);
}

int	ft_export(t_vars *var, char *to_add, int pass)
{
	if (!pass)
		pass = validate_variable(var, to_add);
	if (pass == 1)
		export_add(var, to_add);
	else if (pass == 2)
	{
		trouble("export", to_add, "not a valid identifier", 1);
		return (1);
	}
	return (0);
}

void	export_add(t_vars *var, char *to_add)
{
	var->env.newexp[var->env.sizeofexp] = malloc(sizeof(char *) * 3);
	ft_free(var->tmpp);
	var->tmpp = ft_split(to_add, '=');
	var->env.newexp[var->env.sizeofexp][0] = ft_strdup(var->tmpp[0]);
	if (ft_strchr(to_add, '='))
	{
		var->env.newexp[var->env.sizeofexp][1] = \
		ft_strdup(ft_strchr(to_add, '=') + 1);
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
