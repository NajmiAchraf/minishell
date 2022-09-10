/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 19:51:30 by ohrete            #+#    #+#             */
/*   Updated: 2022/09/08 22:04:54 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
char	*ft_expand(char *str, t_env *env, char **av)
{
	int		i;
	int		start;
	char	*ptr;
	char	*new;

	i = 0;
	start = 0;

	new = ft_strdup("");
	//printf("expanding \n");
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] != '\0' && str[i + 1] == '?')
			{
				ptr = ft_itoa(g_status);
				new = ft_strjoin(new, ptr);
				i = i + 2;
			}
			else if (str[i + 1] != '\0' && str[i + 1] == 48)
			{
				ptr = ft_strdup(av[0]);
				new = ft_strjoin(new, ptr);
				i = i + 2;
			}
			else
			{
				start = ++i;
				while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
					i++;
				ptr = ft_substr(str, start, i - start);
				ptr = getting_env(env, ptr);
				new = ft_strjoin(new, ptr);
			}
		}
		else
		{
			start = i;
			while (str[i] != '\0' && str[i] != '$')
				i++;
			ptr = ft_substr(str, start, i - start);
			new = ft_strjoin(new, ptr);
		}
	}
	return (new);
}


// For the norm
// void	inside_dollar(char *str, t_env *env, char **av)
// {
// 	int		i;
// 	int		start;
// 	char	*ptr;
// 	char	*new;

// 	i = 0;
// 	start = 0;
// 	new = ft_strdup("");
// 	if (str[i + 1] != '\0' && str[i + 1] == '?')
// 	{
// 		ptr = ft_itoa(g_status);
// 		new = ft_strjoin(new, ptr);
// 		i = i + 2;
// 	}
// 	else if (str[i + 1] != '\0' && str[i + 1] == 48)
// 	{
// 		ptr = ft_strdup(av[0]);
// 		new = ft_strjoin(new, ptr);
// 		i = i + 2;
// 	}
// 	else
// 	{
// 		start = ++i;
// 		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
// 			i++;
// 		ptr = ft_substr(str, start, i - start);
// 		ptr = getting_env(env, ptr);
// 		new = ft_strjoin(new, ptr);
// 	}
// }


// char	*ft_expand(char *str, t_env *env, char **av)
// {
// 	int		i;
// 	int		start;
// 	char	*ptr;
// 	char	*new;

// 	i = 0;
// 	start = 0;
// 	new = ft_strdup("");
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			inside_dollar(str, env, av);
// 		}
// 		else
// 		{
// 			start = i;
// 			while (str[i] != '\0' && str[i] != '$')
// 				i++;
// 			ptr = ft_substr(str, start, i - start);
// 			new = ft_strjoin(new, ptr);
// 		}
// 		i++;
// 	}
// 	return (new);
// }