/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:39:54 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/11 16:33:25 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free1(char **tofree)
{
	t_allways	aws;

	aws.i = 0;
	while (tofree[aws.i])
	{
		free(tofree[aws.i]);
		aws.i++;
	}
	free(tofree);
}

int	replace_variable(t_vars *var, char *to_check, char *value)
{
	t_allways aws;

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
	t_allways aws;

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
	t_allways aws;

	free1(var->tmpp);
	var->tmpp = ft_split(to_check, '=');
	if (ft_strchr(to_check, '=') == NULL && !check_env_var(var, var->tmpp[0])) // not fixed yet
		return (0);
	else if (replace_variable(var, var->tmpp[0], to_check))
		return (0);
	if (little_checker(var->tmpp[0]))
		return (2);
	return (1);
}

void	sort_export(t_vars *var)
{
	t_allways aws;

	aws.i = -1;
	while (++aws.i < var->env.sizeofexp - 1)
	{
		if (ft_strcmp(var->env.newexp[aws.i][0], var->env.newexp[aws.i + 1][0]) > 0)
		{
			ft_swap_tp(&var->env.newexp[aws.i], &var->env.newexp[aws.i + 1]);
			aws.i = -1;
		}
	}
}

void	init_environment(t_vars *var)
{
	t_allways aws;

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
	t_allways aws;

	aws.i = 0;
	var->env.newexp = malloc(sizeof(char **) * 4096);
	while (var->env.env[aws.i])
	{
		var->env.newexp[aws.i] = malloc(sizeof(char *) * 3);
		free1(var->tmpp);
		var->tmpp = ft_split(var->env.env[aws.i], '=');
		var->env.newexp[aws.i][0] = ft_strdup(var->tmpp[0]);
		var->env.newexp[aws.i][1] = ft_strdup(ft_strchr(var->env.env[aws.i], '=') + 1);
		var->env.newexp[aws.i][2] = NULL;
		aws.i++;
	}
	var->env.newexp[aws.i] = NULL;
	var->env.sizeofexp = ft_lstslen(var->env.newexp);
	if (!var->env.env[0])
		return ;
	sort_export(var);
}

void	show_env(t_vars *var)
{
	t_allways aws;

	aws.i = 0;
	while (aws.i < var->env.sizeofenv)
	{
		printf("%s\n", var->env.newenv[aws.i]);
		aws.i++;
	}
}

void	show_exp(t_vars *var)
{
	t_allways aws;

	aws.i = 0;
	while (aws.i < var->env.sizeofexp)
	{
		if (!var->env.newexp[aws.i][1])
			printf("declare -x %s\n", var->env.newexp[aws.i][0]);
		else
			printf("declare -x %s=\"%s\"\n", var->env.newexp[aws.i][0], var->env.newexp[aws.i][1]);
		aws.i++;
	}
}

void	ft_export(t_vars *var, char *to_add, int pass)
{
	if (!pass)
		pass = validate_variable(var, to_add);
	if (pass == 1)
		export_add(var, to_add);
	else if (pass == 2)
		printf("minishell: export: `%s': not a valid identifier\n", to_add);
}

void	export_add(t_vars *var, char *to_add)
{
	var->env.newexp[var->env.sizeofexp] = malloc(sizeof(char *) * 3);
	free1(var->tmpp);
	var->tmpp = ft_split(to_add, '=');
	var->env.newexp[var->env.sizeofexp][0] = ft_strdup(var->tmpp[0]);
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
	t_allways aws;

	aws.i = -1;
	while (++aws.i < var->env.sizeofenv)
	{
		free1(var->tmpp);
		var->tmpp = ft_split(var->env.newenv[aws.i], '=');
		if (ft_strcmp(var->tmpp[0], to_del) == 0)
		{
			free(var->env.newenv[aws.i]);
			var->env.newenv[aws.i] = "~";
			--aws.i;
			while (++aws.i < var->env.sizeofenv - 1)
				ft_swap_dp(&var->env.newenv[aws.i], &var->env.newenv[aws.i + 1]);
			var->env.newenv[aws.i] = NULL;
			var->env.sizeofenv = ft_lstlen(var->env.newenv);
			break;
		}
	}
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
			break;
		}
	}
}

char	*get_env_var(t_vars *var, char *to_get)
{
	t_allways aws;

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
	t_allways aws;

	aws.j = -1;
	while (++aws.j < var->env.sizeofexp)
	{
		if (!ft_strcmp(var->env.newexp[aws.j][0], to_check))
			return (0);
	}
	return (1);
}
