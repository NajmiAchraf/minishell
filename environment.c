/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:39:54 by anajmi            #+#    #+#             */
/*   Updated: 2022/07/01 02:18:25 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	replace_variable(t_vars *var, char *to_check, char *value)
{
	t_allways aws;

	aws.i = -1;
	while (++aws.i < var->env.sizeofexp)
	{
		if (!ft_strcmp(var->env.newexp[aws.i][0], to_check))
		{
			ft_unset(var, to_check);
			ft_export(var, value, 1);
			return (1);
		}
	}
	return (0);
}

int	var_into_var(t_vars *var, char **to_check, t_allways aws)
{
	char	*variable;

	aws.j = ft_lstlen(to_check);
	if (aws.j == 2)
	{
		variable = to_check[0];
		free(var->tmp1);
		var->tmp1 = ft_substr(to_check[1], 0, aws.i);
		free(var->tmp);
		var->tmp = ft_substr(to_check[1], aws.i + 1, aws.k - aws.i - 1);
		free(var->tmp2);
		var->tmp2 = ft_substr(to_check[1], aws.k, ft_strlen(to_check[1]));
		if (!get_env_var(var, var->tmp))
			ft_export(var, ft_strjoin(ft_strjoin(ft_strjoin(variable, "="), var->tmp1), var->tmp2), 0);
		else
			ft_export(var, ft_strjoin(ft_strjoin(ft_strjoin(ft_strjoin(variable, "="), var->tmp1), get_env_var(var, var->tmp)), var->tmp2), 0);
		return (1);
	}
	return (0);
}

int	name_into_var(t_vars *var, char **to_check, t_allways aws)
{
	char	*variable;

	aws.j = ft_lstlen(to_check);
	if (aws.j == 1)
		variable = "";
	else if (aws.j == 2)
		variable = to_check[1];
	free(var->tmp1);
	var->tmp1 = ft_substr(to_check[0], 0, aws.i);
	free(var->tmp);
	var->tmp = ft_substr(to_check[0], aws.i + 1, aws.k - aws.i - 1);
	free(var->tmp2);
	var->tmp2 = ft_substr(to_check[0], aws.k, ft_strlen(to_check[0]));
	if (!get_env_var(var, var->tmp))
		ft_export(var, ft_strjoin(ft_strjoin(ft_strjoin(var->tmp1, var->tmp2), "="), variable), 0);
	else
		ft_export(var, ft_strjoin(ft_strjoin(ft_strjoin(ft_strjoin(var->tmp1, get_env_var(var, var->tmp)), var->tmp2), "="), variable), 0);
	return (1);
}

int	outside_search_variable(t_vars *var, char *to_search, char *variable)
{
	t_allways aws;

	aws.i = -1;
	while (to_search[++aws.i])
	{
		if (to_search[aws.i] == '$')
		{
			aws.k = aws.i;
			while (to_search[++aws.k])
			{
				if (!(ft_isalpha(to_search[aws.k]) || to_search[aws.k] == '_'))
					break;
			}
			free(var->tmp);
			var->tmp = ft_substr(to_search, aws.i + 1, aws.k - aws.i - 1);
			if (!ft_strcmp(var->tmp, variable) || to_search[aws.k] == '\0')
				return (var_into_var(var, var->temp, aws));
		}
	}
	return (0);
}

int	inside_search_variable(t_vars *var, char *to_search, int gen)
{
	t_allways aws;

	aws.i = -1;
	while (to_search[++aws.i])
	{
		if (to_search[aws.i] == '$')
		{
			aws.k = aws.i;
			while (to_search[++aws.k])
			{
				free(var->tmp);
				var->tmp = ft_substr(to_search, aws.i + 1, aws.k - aws.i - 1);
				if (!(ft_isalpha(to_search[aws.k]) || to_search[aws.k] == '_')
					|| check_env_var(var, var->tmp))
					break ;
			}
			if (gen == 1)
				return (name_into_var(var, var->temp, aws));
			else if (gen == 2)
				return (var_into_var(var, var->temp, aws));
		}
	}
	return (0);
}

int	little_checker(t_vars *var)
{
	t_allways aws;

	if (ft_isalpha(var->temp[0][0]) || var->temp[0][0] == '_')
	{
		aws.i = 0;
		while (var->temp[0][++aws.i])
		{
			if (!isalnum(var->temp[0][aws.i]) && var->temp[0][aws.i] != '_')
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

	free(var->temp);
	var->temp = ft_split(to_check, '=');
	aws.i = ft_lstlen(var->temp);
	if (inside_search_variable(var, var->temp[0], 1))
		return (0);
	if (aws.i == 2)
	{
		if (outside_search_variable(var, var->temp[1], var->temp[0]))
			return (0);
	}
	if (replace_variable(var, var->temp[0], to_check))
		return (0);
	if (aws.i == 2)
	{
		if (inside_search_variable(var, var->temp[1], 2))
			return (0);
	}
	if (little_checker(var))
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
	var->env.newenv = malloc(sizeof(char *) * 1024);
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
	var->env.newexp = malloc(sizeof(char **) * 1024);
	while (var->env.env[aws.i])
	{
		var->env.newexp[aws.i] = malloc(sizeof(char *) * 3);
		free(var->temp);
		var->temp = ft_split(var->env.env[aws.i], '=');
		var->env.newexp[aws.i][0] = ft_strdup(var->temp[0]);
		var->env.newexp[aws.i][1] = ft_strdup(ft_strchr(var->env.env[aws.i], '=') + 1);
		var->env.newexp[aws.i][2] = NULL;
		aws.i++;
	}
	var->env.newexp[aws.i] = NULL;
	var->env.sizeofexp = ft_lstslen(var->env.newexp);
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
		printf("bash: export: `%s': not a valid identifier\n", to_add);
}

void	export_add(t_vars *var, char *to_add)
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
	t_allways aws;

	aws.i = -1;
	while (++aws.i < var->env.sizeofenv)
	{
		free(var->temp);
		var->temp = ft_split(var->env.newenv[aws.i], '=');
		if (ft_strcmp(var->temp[0], to_del) == 0)
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
	while (++aws.i < var->env.sizeofexp - 1)
	{
		if (!ft_strcmp(var->env.newexp[aws.i][0], to_get))
			return (var->env.newexp[aws.i][1]);
	}
	return (NULL);
}

int	check_env_var(t_vars *var, char *to_check)
{
	t_allways aws;

	aws.j = -1;
	while (++aws.j < var->env.sizeofexp - 1)
	{
		if (!ft_strcmp(var->env.newexp[aws.j][0], to_check))
			return (1);
	}
	return (0);
}
