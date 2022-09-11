/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:22:39 by ohrete            #+#    #+#             */
/*   Updated: 2022/09/07 23:46:37 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_first(t_env **fst_link, t_env *new)
{
	if (!new || !fst_link)
		return ;
	new->next = *fst_link;
	*fst_link = new;
}

void	add_last(t_env **head, t_env *new)
{
	t_env	*last;

	last = (*head);
	if (!(*head))
		(*head) = new;
	else
	{
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

