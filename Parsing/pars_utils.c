/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:19:40 by ohrete            #+#    #+#             */
/*   Updated: 2022/08/27 01:20:03 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	list_size(t_cmd *list)
{
	t_cmd	*tmp;
	int		i;

	if (!list)
		return (0);
	i = 1;
	tmp = list;
	while (tmp->next)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	redirect(char *str)
{
	if (ft_strcmp(str, "<") == 0)
		return (1);
	if (ft_strcmp(str, ">") == 0)
		return (2);
	if (ft_strcmp(str, ">>") == 0)
		return (3);
	if (ft_strcmp(str, "<<") == 0)
		return (4);
	return (0);
}

t_final	*create_node(void)
{
	t_final	*new_node;

	new_node = (t_final *)malloc(sizeof (t_final));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->infile = -1;
	new_node->outfile = -1;
	return (new_node);
}

t_file	*file_node(char *str, int type)
{
	t_file	*new_node;

	new_node = (t_file *)malloc(sizeof (t_file));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->str = my_strdup(str);
	new_node->id = type;
	return (new_node);
}

void	to_array(t_final *node)
{
	int	i;
	int	len;

	while (node)
	{
		len = list_size(node->name);
		node->cmd = malloc((len + 1) * sizeof(char *));
		i = 0;
		while (node->name)
		{
			if (node->name->str[0] != '\0')
			{
				node->cmd[i] = my_strdup(node->name->str);
				i++;
			}
			node->name = node->name->next;
		}
		node->cmd[i] = NULL;
		node = node->next;
	}
}
