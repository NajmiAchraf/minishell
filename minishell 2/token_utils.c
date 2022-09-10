/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 18:25:58 by ohrete            #+#    #+#             */
/*   Updated: 2022/09/09 17:11:26 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	single_quote(t_token **head, char *line, int *i)
{
	int	index;

	index = *i;
	(*i)++;
	while (line[*i] && line[*i] != '\'')
		(*i)++;
	if (!line[*i])
	{
		printf("ERROR: inclosed quotes\n");
		return ;
	}
	add_token_last(head, new_node
		(ft_substr(line, index + 1, *i - index - 1), SQ));
	(*i)++;
}

// void	double_quote(t_save *save, t_token **temp, char *line, int *i)
// {
// 	int		index;
// 	char	*str;
// 	char	*expand;

// 	index = *i;
// 	(*i)++;
// 	while (line[*i] && line[*i] != '\"')
// 		(*i)++;
// 	if (!line[*i])
// 	{
// 		printf("ERROR: inclosed quotes\n");
// 		return ;
// 	}
// 	str = ft_substr(line, index + 1, *i - index - 1);
// 	expand = ft_expand(str, save->env, save->av);
// 	add_token_last(temp, new_node(expand, DQ));
// 	(*i)++;
// }

void	double_quote(t_save *save, t_token **temp, char *line, int *i)
{
	int		index;
	char	*str;
	char	*expand;

	index = *i;
	(*i)++;
	while (line[*i] && line[*i] != '\"')
		(*i)++;
	if (!line[*i])
	{
		printf("ERROR: inclosed quotes\n");
		return ;
	}
	str = ft_substr(line, index + 1, *i - index - 1);
	if (check_dollar(str) != 0)
	{
		expand = ft_expand(str, save->env, save->av);
		add_token_last(temp, new_node(expand, DQ));
	}
	else
		add_token_last(temp, new_node(str, DQ));	
	(*i)++;
}


// void	dollar(t_save *save, t_token **temp, char *line, int *i)
// {
// 	int		index;
// 	char	*str;
// 	char	*expand;
// 	t_token	*copy;

// 	copy = *temp;
// 	index = *i;
// 	(*i)++;
// 	while (line[*i] && other_char(line[*i]))
// 		(*i)++;
// 	str = ft_substr(line, index, *i - index);
// 	while (copy != NULL)
// 	{
// 		if (copy && ft_strcmp(copy->str, "<<") == 0)
// 		{
// 			add_token_last(temp, new_node(str, EXPAND));
// 			return ;
// 		}
// 		else if (copy->next == NULL)
// 			break ;
// 		copy = copy->next;
// 	}
// 	expand = ft_expand(str, save->env, save->av);
// 	add_token_last(temp, new_node(expand, EXPAND));
// }

void	dollar(t_save *save, t_token **temp, char *line, int *i)
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
	if (check_dollar(str) != 0)
	{
		expand = ft_expand(str, save->env, save->av);
		add_token_last(temp, new_node(expand, EXPAND));	
	}
	while (copy != NULL)
	{
		if (copy && ft_strcmp(copy->str, "<<") == 0)
		{
			add_token_last(temp, new_node(str, EXPAND));
			return ;
		}
		else if (copy->next == NULL)
			break ;
		copy = copy->next;
	}
}

void	redirection(t_token **head, char *str, int *i)
{
	if (str[*i] == '>' && str[*i + 1] == '>')
	{
		add_token_last(head, new_node(">>", APPEND));
		(*i)++;
	}
	else if (str[*i] == '<' && str[*i + 1] == '<')
	{
		add_token_last(head, new_node("<<", HERE_DOC));
		(*i)++;
	}
	else if (str[*i] == '>')
		add_token_last(head, new_node(">", OUTPUT));
	else if (str[*i] == '<')
		add_token_last(head, new_node("<", INPUT));
	(*i)++;
}

void	setting_word(t_save *save, t_token **temp, char *line, int *i)
{
	int		index;
	char	*str;
	char	*expand;
	
	index = *i;
	while (line[*i] && skip_char(line[*i]))
		(*i)++;
	str = ft_substr(line, index, *i - index);
	if (check_dollar(str) != 0)
	{
		//printf("inside if \n");
		expand = ft_expand(str, save->env, save->av);
		add_token_last(temp, new_node(expand, WORD));
	}
	else
	{
		//printf("inside else \n");
		add_token_last(temp, new_node(str, WORD));
		//while (1);
	}
}