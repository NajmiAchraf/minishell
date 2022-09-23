/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 18:30:42 by ohrete            #+#    #+#             */
/*   Updated: 2022/09/22 22:46:53 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	skip_char(char c)
{
	if (c == '&' || c == '<' || c == '>'
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
		return (NULL);
	new->str = str;
	new->id = id;
	new->next = NULL;
	return (new);
}

void	add_token_last(t_token **head, t_token *new)
{
	t_token	*last;

	last = (*head);
	if (!(*head))
	{
		(*head) = new;
	}
	else
	{
		while (last->next != NULL)
		{
			last = last->next;
		}
		last->next = new;
	}
}
