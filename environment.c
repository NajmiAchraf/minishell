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

void	replace_variable(t_vars *var, char *to_check, char *value)
{
	var->i = -1;
	while (++var->i < var->env.sizeofexp - 1)
	{
		if (!ft_strcmp(var->env.newexp[var->i][0], to_check))
		{
			ft_unset(var, to_check);
			ft_export(var, value, 1);
		}
	}
}

int	var_into_var(t_vars *var, char *variable, char *to_check)
{
	free(var->tmp1);
	var->tmp1 = ft_substr(to_check, 0, var->i);
	free(var->tmp);
	var->tmp = ft_substr(to_check, var->i + 1, var->k - var->i - 1);
	free(var->tmp2);
	var->tmp2 = ft_substr(to_check, var->k, ft_strlen(to_check));
	
	// printf("%s = %s %s %s\n", to_check, var->tmp1, var->tmp, var->tmp2);
	// printf("here\n");
	ft_export(var, ft_strjoin(ft_strjoin(ft_strjoin(ft_strjoin(variable, "="), var->tmp1), get_env_var(var, var->tmp)), var->tmp2), 0);
	return (0);
}

int	name_into_var(t_vars *var, char *to_check, char *variable)
{
	free(var->tmp1);
	var->tmp1 = ft_substr(to_check, 0, var->i);
	free(var->tmp);
	var->tmp = ft_substr(to_check, var->i + 1, var->k - var->i - 1);
	free(var->tmp2);
	var->tmp2 = ft_substr(to_check, var->k, ft_strlen(to_check));
	
	printf("%s = %s %s %s\n", to_check, var->tmp1, var->tmp, var->tmp2);
	// printf("here\n");
	printf("%s %s %s %s %s\n", var->tmp1, get_env_var(var, var->tmp), var->tmp2, "=", variable);
	printf("%s \n", 
	ft_strjoin(
		ft_strjoin(
			ft_strjoin(
				ft_strjoin(var->tmp1, get_env_var(var, var->tmp))
				, var->tmp2)
				, "=")
				, variable));
	ft_export(var, ft_strjoin(ft_strjoin(ft_strjoin(ft_strjoin(var->tmp1, get_env_var(var, var->tmp)), var->tmp2), "="), variable), 0);
	return (0);
}

int	outside_search_variable(t_vars *var, char *to_search, char *variable)
{
	var->i = -1;
	while (to_search[++var->i])
	{
		if (to_search[var->i] == '$')
		{
			var->k = var->i;
			while (to_search[++var->k])
			{
				if (!(ft_isalpha(to_search[var->k]) || to_search[var->k] == '_'))
					break;
			}
			free(var->tmp);
			var->tmp = ft_substr(to_search, var->i + 1, var->k - var->i - 1);
			// printf("%s  |>  %s =?= %s  || k = %zu\n", to_search, var->tmp, variable, var->k - var->i - 1);
			if (!ft_strcmp(var->tmp, variable))
				return (1);
			if (to_search[var->k] == '\0')
				return (1);
		}
	}
	return (0);
}

int	inside_search_variable(t_vars *var, char *to_search)
{
	var->i = -1;
	while (to_search[++var->i])
	{
		if (to_search[var->i] == '$')
		{
			var->k = var->i;
			while (to_search[++var->k])
			{
				if (!(ft_isalpha(to_search[var->k]) || to_search[var->k] == '_'))
					return (1);
			}
			if (to_search[var->k] == '\0')
				return (1);
		}
	}
	return (0);
}

int	validate_variable(t_vars *var, char *to_check)
{
	printf("validate start |> %s\n\n", to_check);
	var->i = 0;
	free(var->temp);
	var->temp = ft_split(to_check, '=');
	if (inside_search_variable(var, var->temp[0]))
	{
		return (name_into_var(var, var->temp[0], var->temp[1]));
	}
	else if (ft_isalpha(var->temp[0][var->i]) || var->temp[0][var->i] == '_')
	{
		while (var->temp[0][++var->i])
		{
			if (!isalnum(var->temp[0][var->i]))
				return (0);
		}
		if (outside_search_variable(var, var->temp[1], var->temp[0]))
		{
			// printf("var-> %s\n", var->temp[1]);
			return (var_into_var(var, var->temp[0], var->temp[1]));
			// printf("|>ZLL = %s\n", get_env_var(var, "ZLL"));
		}
		replace_variable(var, var->temp[0], to_check);
		if (inside_search_variable(var, var->temp[1]))
		{
			return (var_into_var(var, var->temp[0], var->temp[1]));
			// printf("<|ZLL = %s\n", get_env_var(var, "ZLL"));
		}
	}
	return (1);
}

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

void	ft_export(t_vars *var, char *to_add, int pass)
{
	if (!pass)
		pass = validate_variable(var, to_add);
	if (pass)
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
	return (NULL);
}
