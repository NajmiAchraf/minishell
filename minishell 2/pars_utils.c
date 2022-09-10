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

#include "minishell.h"

t_token	*create_node(void)
{
	t_token	*new_node;
	
	new_node =  (t_token *)malloc(sizeof (t_token));
	new_node->my_node = NULL;
	new_node->next = NULL;
	new_node->after_pipe = 0;
	new_node->before_pipe = 0;
	new_node->append = NULL;
	new_node->here_d = NULL;
	new_node->infile = NULL;
	new_node->outfile = NULL;
	new_node->cmd = NULL;
	new_node->str = NULL;
	return (new_node);
}

void	add_last_list(t_token **head, t_token *new)
{
	t_token	*last;

	last = (*head);
	if (!(*head))
		(*head) = new;
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}

int	list_size(t_token *list)
{
	t_token	*tmp;
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

void	clear_list(t_token **list)
{
	t_token	*tmp;

	if (!(*list))
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		//free((*list)->str);
		free(*list);
		*list = tmp;
	}
	list = NULL;
}

int	my_errors(int e)
{
	if (e == 1)
		printf("Oops Error! Syntax error!\n");
	return (0) ;
}