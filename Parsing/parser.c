/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 23:50:30 by ohrete            #+#    #+#             */
/*   Updated: 2022/09/27 22:32:19 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*cmd_node(char *str)
{
	t_cmd	*new_node;

	new_node =  (t_cmd *)malloc(sizeof (t_cmd));
	if (!new_node)
		return (NULL);
	new_node->str = my_strdup(str);
	new_node->next = NULL;
	return (new_node);
}

/*
t_final	*ft_parser(t_token *data)
{
	t_final *head;
	t_final *tmp;
	t_final *link;
	t_token *save;
	t_file *save_file;
	t_file *node_file;
	t_cmd *save_cmd;
	t_cmd *node_cmd;
	int		type;

	head = NULL;
	save = data;
	while (data)
	{
		tmp = create_node();
		if (head == NULL)
		{
			head = tmp;
			link = head;
			tmp->file = NULL;
			tmp->name = NULL;
		}
		else
		{
			link->next = tmp;
			link = tmp;
			tmp->file = NULL;
			tmp->name = NULL;
		}
		while (data && ft_strcmp(data->str, "|") != 0)
		{
			if (redirect(data->str))
			{
				if (data->str[0] == redirect(data->str) || data->next == NULL)
				{
					printf("redirect error\n");
					return (0);
				}
				type = redirect(data->str);
				data = data->next;
				node_file = file_node(data->str, type);
				if (tmp->file == NULL)
				{
					tmp->file = node_file;
					save_file = node_file;
				}
				else
				{
					save_file->next = node_file;
					save_file = node_file;
				}
			}
			else
			{
				node_cmd = cmd_node(data->str);
				if (tmp->name == NULL)
				{
					tmp->name = node_cmd;
					save_cmd = node_cmd;
				}
				else
				{
					save_cmd->next = node_cmd;
					save_cmd = node_cmd;
				}
			}
			data = data->next;
		}
		if (tmp->name)
			node_cmd->next = NULL;
		if (tmp->file)
			node_file->next = NULL;
		if (data != NULL)
			data = data->next;
	}
	//tmp->next = NULL;
	to_array(head);
	return (head);
}
*/


//FOR NORM
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
	return(head);
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

void	cmd_name(t_final *tmp,t_cmd **save_cmd, t_cmd *node_cmd, t_token *data)
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


void	norm_while(t_token **data, t_final **tmp, t_cmd *node_cmd)
{
	int type;
	t_cmd *save_cmd;
	//t_cmd *node_cmd;
	t_file *node_file;
	t_file *save_file;
	
	while ((*data) && (*data)->str && ft_strcmp((*data)->str, PIPE) != 0)
	{
		if (redirect((*data)->str))
		{
			if (((1 <= redirect((*data)->str) && redirect((*data)->str) <= 4)
				&& ((*data)->next == NULL || !my_isalnum((*data)->next->str[0]))))
			{
				trouble(NULL, NULL, "syntax error", 258);
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

t_final	*ft_parser(t_token *data)
{
	t_final	*head;
	t_final	*tmp;
	t_token	*save;
	t_final	*link;
	t_cmd	*node_cmd;

	head = NULL;
	link = head;
	save = data;
	node_cmd = NULL;
	while (data)
	{
		tmp = create_node();
		head = link_nodes(head, &link, tmp);
		norm_while(&data, &tmp, node_cmd);
		if (data != NULL)
			data = data->next;
	}
	to_array(head);
	return (head);
}




/*
t_final	*ft_parser(t_token *data)
{
	t_final	*head;
	t_final	*tmp;
	t_token	*save;
	t_file	*node_file;
	t_cmd	*node_cmd;
	t_final	*link;
	t_file	*save_file;
	t_cmd	*save_cmd;
	int		type;

	head = NULL;
	link = head;
	save = data;
	while (data)
	{
		tmp = create_node();
		head = link_nodes(head, &link, tmp);
		while (data && data->str && ft_strcmp(data->str, PIPE) != 0)
		{
			if (redirect(data->str))
			{
				if (((1 <= redirect(data->str) && redirect(data->str) <= 4)
						&& (data->next == NULL || !my_isalnum(data->next->str[0]))))
				{
					trouble(NULL, NULL, "syntax error", 258);
					return (0);
				}
				type = redirect(data->str);
				data = data->next;
				node_file = file_node(data->str, type);
				redir_cmd(tmp, &save_file, node_file);
			}
			else
				cmd_name(tmp, &save_cmd, node_cmd, data);
			data = data->next;
		}
		if (data != NULL)
			data = data->next;
	}
	to_array(head);
	return (head);
}

*/