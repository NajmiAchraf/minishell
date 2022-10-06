/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 23:50:30 by ohrete            #+#    #+#             */
/*   Updated: 2022/10/06 14:35:09 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*cmd_node(char *str)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof (t_cmd));
	if (!new_node)
		return (NULL);
	new_node->str = my_strdup(str);
	new_node->next = NULL;
	return (new_node);
}

void	redir_cmd(t_final *tmp, t_file **save_file, t_file *node_file)
{
	if (tmp->file == NULL)
	{
		tmp->file = node_file;
		(*save_file) = node_file;
	}
	else
	{
		(*save_file)->next = node_file;
		(*save_file) = node_file;
	}
	if (tmp->file)
		node_file->next = NULL;
}

void	cmd_name(t_final *tmp, t_cmd **save_cmd, t_cmd *node_cmd, t_token *data)
{
	node_cmd = cmd_node(data->str);
	if (tmp->name == NULL)
	{
		tmp->name = node_cmd;
		(*save_cmd) = node_cmd;
	}
	else
	{
		(*save_cmd)->next = node_cmd;
		(*save_cmd) = node_cmd;
	}
	if (tmp->name)
		node_cmd->next = NULL;
}

void	norm_while(t_token **data, t_final **tmp, t_cmd *node_cmd, t_save *sv)
{
	int		type;
	t_cmd	*save_cmd;
	t_file	*node_file;
	t_file	*save_file;

	while ((*data) && (*data)->str && ft_strcmp((*data)->str, PIPE) != 0)
	{
		if (redirect((*data)->str))
		{
			if (((1 <= redirect((*data)->str) && redirect((*data)->str) <= 4)
					&& ((*data)->next == NULL
						|| !my_isalnum((*data)->next->str[0]))))
			{
				sv->error = trouble(NULL, NULL, "syntax error", 258);
				return ;
			}
			type = redirect((*data)->str);
			(*data) = (*data)->next;
			node_file = file_node((*data)->str, type);
			redir_cmd((*tmp), &save_file, node_file);
		}
		else
			cmd_name((*tmp), &save_cmd, node_cmd, (*data));
		(*data) = (*data)->next;
	}
}

t_final	*ft_parser(t_token *data, t_save *sv)
{
	t_final	*head;
	t_final	*tmp;
	t_final	*link;
	t_cmd	*node_cmd;

	head = NULL;
	link = head;
	node_cmd = NULL;
	while (data)
	{
		tmp = create_node();
		head = link_nodes(head, &link, tmp);
		norm_while(&data, &tmp, node_cmd, sv);
		if (data != NULL)
			data = data->next;
	}
	to_array(head);
	return (head);
}
