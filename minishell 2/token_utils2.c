/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 18:30:42 by ohrete            #+#    #+#             */
/*   Updated: 2022/09/09 16:41:29 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	skip_char(char c)
{
	if (c == '$' || c == '&' || c == '\'' || c == '\"' || c == '<' || c == '>'
		|| c == ' ' || c == '|')
		return (0);
	return (1);
}

int	other_char(char c)
{
	if (!(c >= '0' && c <= '9') && !(c >= 'A' && c <= 'Z')
		&& !(c >= 'a' && c <= 'z') && c != '_' && c != '?')
		return (0);
	return (1);
}

t_token	*new_node(char *str, int id)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		return NULL;
	new->str = str;
	new->id = id;
	new->next = NULL;
	//printf("new node \n");
	return (new);
}

void	add_token_last(t_token **head, t_token *new)
{
	t_token	*last;
	//printf("start add \n");

	last = (*head);
	if (!(*head))
	{
		//printf("if add last \n");
		(*head) = new;
		//printf("=== > %s\n", (*head)->str);
	}
	else
	{
		while (last->next != NULL)
		{
			//printf("0000 %s\n", last->str);
			last = last->next;
		}
		//printf("66666 \n");
		last->next= new;

		//printf("else 88\n");
	}
		//  while (test)
		//  {
		// printf("======== else add last %s\n", test->str);
		// 	test = test->next;
		//  }
		// printf("======== else add head %s\n", (*head)->str);
	// printf("last is {%s}\n", (*head)->str);
}