/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 23:50:30 by ohrete            #+#    #+#             */
/*   Updated: 2022/09/11 16:45:50 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	list_size(t_cmd *list)
{
	t_cmd	*tmp;
	int	i;
	
	if (!list)
		return (0);
	i = 1;
	tmp = list;
	while(tmp->next)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
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
			node->cmd[i] = ft_strdup(node->name->str);
			node->name = node->name->next;
			i++;
		}
		node->cmd[i] = NULL;
		node = node->next;
	}
}

int redirect(char *str)
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
	
	new_node =  (t_final *)malloc(sizeof (t_final));
	if (!new_node)
		return (NULL);
	// new_node = NULL;
	new_node->next = NULL; //*****
	new_node->infile = -1;
	new_node->outfile = -1;
	// new_node->file = NULL;
	// new_node->name = NULL;
	//printf("creat big node \n");
	return (new_node);
}

t_file	*file_node(char *str, int type)
{
	t_file	*new_node;

	new_node =  (t_file *)malloc(sizeof (t_file));
	if (!new_node)
		return (NULL);
	// new_node = NULL;
	new_node->next = NULL;  //*****
	new_node->str = ft_strdup(str);
	new_node->id = type;
	//printf("creat file node \n");
	return (new_node);
}

t_cmd	*cmd_node(char *str)
{
	t_cmd	*new_node;

	new_node =  (t_cmd *)malloc(sizeof (t_cmd));
	if (!new_node)
		return (NULL);
	new_node->str = ft_strdup(str);
	new_node->next = NULL;  //*****   
	//printf("|%s| \n", (*name)->str);
	//printf("creat cmd node \n");
	return (new_node);
}

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
	tmp->next = NULL;
	to_array(head);
	return (head);
}