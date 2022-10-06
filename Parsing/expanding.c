/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 19:51:30 by ohrete            #+#    #+#             */
/*   Updated: 2022/10/06 14:57:14 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_dollar(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '$')
			c++;
		i++;
	}
	return (c);
}

char	*inside_dollar(char *str, t_env *env, char **av, int *i)
{
	t_token	var;
	char	*h;

	var.start = 0;
	if (str[(*i) + 1] != '\0' && str[(*i) + 1] == '?')
	{
		var.ptr = ft_itoa(g_status);
		(*i) = (*i) + 2;
	}
	else if (str[(*i) + 1] != '\0' && str[(*i) + 1] == 48)
	{
		var.ptr = my_strdup(av[0]);
		(*i) = (*i) + 2;
	}
	else
	{
		var.start = ++(*i);
		while (str[(*i)] && (ft_isalnum(str[(*i)]) || str[(*i)] == '_'))
			(*i)++;
		var.ptr = ft_substr(str, var.start, (*i) - var.start);
		h = var.ptr;
		var.ptr = get_env_var(env->env_var, var.ptr);
		free(h);
	}
	return (var.ptr);
}

char	*ft_expand(char *str, t_env *env, char **av)
{
	char	*value;
	int		i;
	int		start;
	char	*ptr;

	value = ft_strdup("");
	i = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			ptr = inside_dollar(str, env, av, &i);
			value = my_strjoin(value, ptr);
		}
		else
		{
			start = i;
			while (str[i] != '\0' && str[i] != '$')
				i++;
			ptr = ft_substr(str, start, i - start);
			value = my_strjoin(value, ptr);
		}
	}
	return (value);
}
