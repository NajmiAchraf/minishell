/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oldparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:56:06 by ohrete            #+#    #+#             */
/*   Updated: 2022/09/06 16:55:04 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//The Parser is the software component that reads the command line such as “ls -­al” 
//and puts it into a data structure called C​ommand Table ​that will store the commands that will be executed.


t_token	*new_content(void *str)
{
	t_token	*new_node;
	
	new_node =  (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->str = str;
	new_node->my_node = NULL;
	new_node->after_pipe = 0;
	new_node->before_pipe = 0;
	new_node->append = NULL;
	new_node->here_d = NULL;
	new_node->infile = NULL;
	new_node->outfile = NULL;
	new_node->cmd = NULL;
	new_node->id = 0;
	new_node->next = NULL;
	return (new_node);
}



// void	add_first_list(t_token **list, t_token *new)
// {
// 	if (!new || !list)
// 		return ;
// 	new->next = *list;
// 	*list = new;
// }

// t_token	*last_elem(t_token *list)
// {
// 	t_token	*tmp;

// 	if (!list)
// 		return (NULL);
// 	tmp = list;
// 	while (tmp->next != NULL)
// 	{
// 		tmp = tmp->next;
// 	}
// 	return (tmp);
// }

// void	add_last_list(t_token **list, t_token *new)
// {
// 	t_token	*last;

// 	if (!(*list))
// 	{
// 		add_first_list(list, new);
// 		return ;
// 	}
// 	last = last_elem(*list);
// 	if (new->next == NULL)
// 		last->next = new;
// 	while (new->next != NULL)
// 	{
// 		last->next = new;
// 		new = new->next;
// 	}
// }

void	 my_cmds(t_token **head)
{
	int	i;
	int	len;
	t_token	*tmp_head;
	t_token	*tab;

	tmp_head = *head;
	//printf("before while \n");
	while (tmp_head)
	{
		tab = tmp_head->my_node;
		i = 0;
		len = list_size(tab);
		tmp_head->cmd = malloc((len + 1) * sizeof (char *));
		//printf("my table\n");
		while(tab)
		{
			tmp_head->cmd[i] = ft_strdup(tab->str);
			i++;
			tab = tab->next;
		}
		//printf("after strdup\n");
		tmp_head->cmd[i] = NULL;
		tmp_head = tmp_head->next;
	}
	//printf("after while \n");
}

void	redirects(t_token **line, t_token **head)
{
	if ((*line)->id == INPUT)
	{
		if (!(*line)->next)
			my_errors(1);
		(*head)->infile = ft_strdup((*line)->str);
	}
	else if ((*line)->id == OUTPUT)
	{
		if (!(*line)->next)
			my_errors(1);
		(*head)->outfile = ft_strdup((*line)->str);
	}
	else if ((*line)->id == HERE_DOC)
	{
		if (!(*line)->next)
			my_errors(1);
		(*head)->here_d= ft_strdup((*line)->str);
	}
	else if ((*line)->id == APPEND)
	{
		if (!(*line)->next)
			my_errors(1);
		(*head)->append = ft_strdup((*line)->str);
	}
	(*line) = (*line)->next;
}

void	my_pipe(t_token **line, t_token **head)
{
	if (!(*head) || !(*line)->next)
		my_errors(1);
	(*line) = (*line)->next;
	(*head)->after_pipe = 1;
	add_last_list(head, create_node());
	(*head) = (*head)->next;
	(*head)->before_pipe = 1;
}

t_token *parser(t_token **line)
{
	t_token	*new;
	t_token	*head;
	t_token	*tmp;
	// t_token *save;

	new = *line;
	head = create_node();
	tmp = head;
	while (new)
	{
		// printf("id is %d\n", new->id);
		if (new->id == PIPE)
		{
			my_pipe(&new, &head);
		}
		else if (new->id == WORD)
		{
			add_last_list(&(head->next), new_content((new->str)));
			new = new->next;
		}
		else
			redirects(&new, &head);
	}
	// while (tmp)
	// 		{
	// 			printf("****\n");
	// 			printf("word2 = %s, id = %d\n", tmp->str, tmp->id);
	// 			tmp = tmp->next;
	// 		}
	// save = tmp;
	my_cmds(&tmp);
	//clear_list(line);
	line = 0;
	// printf("(%s)\n", tmp->str);
	return (tmp);
}
