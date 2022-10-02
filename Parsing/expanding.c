/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 19:51:30 by ohrete            #+#    #+#             */
/*   Updated: 2022/10/02 17:17:39 by anajmi           ###   ########.fr       */
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
	char		*value;
	t_allways	w;
	char		*ptr;

	value = ft_strdup("");
	w.h = 0;
	w.start = 0;
	while (str[w.h])
	{
		if (str[w.h] == '$')
		{
			ptr = inside_dollar(str, env, av, &w.h);
			if (ptr)
				value = my_strjoin(value, ptr);
		}
		else
		{
			w.start = w.h;
			while (str[w.h] != '\0' && str[w.h] != '$')
				w.h++;
			ptr = ft_substr(str, w.start, w.h - w.start);
			value = my_strjoin(value, ptr);
		}
	}
	return (value);
}
