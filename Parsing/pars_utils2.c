/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:20:35 by ohrete            #+#    #+#             */
/*   Updated: 2022/08/27 01:20:50 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_final	*link_nodes(t_final *head, t_final **link, t_final *tmp)
{
	if (head == NULL)
	{
		head = tmp;
		(*link) = head;
		tmp->file = NULL;
		tmp->name = NULL;
	}
	else
	{
		(*link)->next = tmp;
		(*link) = tmp;
		tmp->file = NULL;
		tmp->name = NULL;
	}
	return (head);
}

void	free_tokens(t_token *data)
{
	t_token	*tmp;
	t_token	*new;

	new = data;
	while (new != NULL)
	{
		tmp = new->next;
		free(new->str);
		free(new);
		new = tmp;
	}
}

static void	free_child(t_final	*parent_node)
{
	t_cmd	*child_node;
	t_cmd	*child_node_tmp;
	t_file	*file_node;
	t_file	*file_node_tmp;

	child_node = parent_node->name;
	while (child_node)
	{
		child_node_tmp = child_node->next;
		free(child_node->str);
		free(child_node);
		child_node = child_node_tmp;
	}
	file_node = parent_node->file;
	while (file_node)
	{
		file_node_tmp = file_node->next;
		free(file_node->str);
		free(file_node);
		file_node = file_node_tmp;
	}
}

void	free_parser(t_final *cmd)
{
	t_final	*parent_node;
	t_final	*parent_node_tmp;
	int		i;

	parent_node = cmd;
	while (parent_node)
	{
		free_child(parent_node);
		i = 0;
		while (parent_node->cmd[i])
		{
			free(parent_node->cmd[i]);
			i++;
		}
		free(parent_node->cmd);
		parent_node_tmp = parent_node->next;
		free(parent_node);
		parent_node = parent_node_tmp;
	}
}
