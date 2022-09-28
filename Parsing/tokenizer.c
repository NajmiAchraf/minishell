/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 23:00:09 by ohrete            #+#    #+#             */
/*   Updated: 2022/09/28 15:39:04 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_sign(t_token **head, int *i)
{
	add_token_last(head, new_node(ft_strdup(PIPE), 182));
	(*i)++;
}

char	*dollar(t_save *save, t_token **temp, char *line, int *i)
{
	int		index;
	char	*str;
	char	*expand;
	t_token	*copy;

	copy = *temp;
	index = *i;
	(*i)++;
	while (line[*i] && other_char(line[*i]))
		(*i)++;
	str = ft_substr(line, index, *i - index);
	while (copy != NULL)
	{
		if (copy && ft_strcmp(copy->str, "<<") == 0)
			return (str);
		else if (copy->next == NULL)
			break ;
		copy = copy->next;
	}
	expand = ft_expand(str, save->env, save->av);
	free(str);
	return (expand);
}

void	tokens(char *line, t_token **temp, t_save *save, int *i)
{
	t_token	*tmp;

	tmp = *temp;
	if (space(line[*i]))
		(*i)++;
	else if (line[*i] == '<' || line[*i] == '>')
		redirection(temp, line, i);
	else if (line[*i] == '|')
	{
		if (!ft_strcmp(ft_lstlast1(tmp)->str, PIPE))
			save->error = trouble(NULL, NULL, "syntax error", 258);
		pipe_sign(temp, i);
	}
	else
		save->error = setting_word(save, temp, line, i);
}

t_token	*tokenizer(char *line, t_save *save)
{
	int		i;
	t_token	*temp;

	i = 0;
	temp = NULL;
	if (allspaces(line))
		return (NULL);
	while (line[i])
	{
		tokens(line, &temp, save, &i);
		if (save->error == 1)
			break ;
	}
	if (save->error != 1)
		check_last_word(&temp, save);
	return (temp);
}
