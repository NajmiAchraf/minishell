/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 18:06:24 by ohrete            #+#    #+#             */
/*   Updated: 2022/09/22 22:37:57 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*search_name(char *name, int i)
{
	char	*str;
	int		len;
	char	*c;

	c = ft_strchr(name, i);
	len = ft_strlen(c);
	str = ft_substr(name, 0, ft_strlen(name) - len);
	return (str);
}

char	*search_value(char *value, int i)
{
	char	*str;
	int		len;
	char	*c;

	c = ft_strchr(value, i);
	len = ft_strlen(c);
	str = ft_substr(value, ft_strlen(value) - len + 1, len);
	return (str);
}

t_env	*fill_struct(char *name, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	new->name = my_strdup(name);
	new->value = my_strdup(value);
	new->next = NULL;
	return (new);
}

char	*getting_env(t_env *env, char *name)
{
	while (env)
	{
		if (!ft_strcmp(name, env->name))
		{
			free(name);
			return (my_strdup(env->value));
		}
		env = env->next;
	}
	free(name);
	return (my_strdup(""));
}

t_env	*setting_env(char **env)
{
	t_env	*head;
	char	*name;
	char	*value;
	int		i;

	head = NULL;
	i = 0;
	while (env[i])
	{
		name = search_name(env[i], '=');
		value = search_value(env[i], '=');
		add_last(&head, fill_struct(name, value));
		free(name);
		free(value);
		i++;
	}
	return (head);
}
