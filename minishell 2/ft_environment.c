/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 18:06:24 by ohrete            #+#    #+#             */
/*   Updated: 2022/09/08 16:57:45 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int counting_line(char **line)
// {
//     int i;

//     i = 0;
//     while(line[i])
//         i++;
//     return (i);
// }

// char	**copy_env(char **env)
// {
//     char    **table;
//     //char    **split;
//     int     i;

//     i = 0;
//     //printf("%d\n",counting_line(env));
//     table = malloc(sizeof(char *) * counting_line(env) + 1);
//     while (env[i])
//     {
//         table[i] = ft_strdup(env[i]);
//         printf("%s\n",table[i]);
//         i++;
//     }
//     table[i] = 0;
//     return (table);
// }

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
	// char *tmp_name;
	// char *value_temp;
	
	new = (t_env *)malloc(sizeof(t_env));
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

char	*getting_env(t_env *env, char *name)
{
	while (env)
	{
		if (!ft_strcmp(name, env->name))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
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