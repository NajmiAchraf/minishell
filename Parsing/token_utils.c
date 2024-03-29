/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 18:25:58 by ohrete            #+#    #+#             */
/*   Updated: 2022/09/30 17:06:55 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*single_quote(char *line, int *i)
{
	char	*value;
	int		index;

	index = *i;
	(*i)++;
	while (line[*i] && line[*i] != '\'')
		(*i)++;
	if (!line[*i])
	{
		trouble("syntax error", NULL, "inclosed single quotes", 258);
		return (NULL);
	}
	value = ft_substr(line, index + 1, *i - index - 1);
	(*i)++;
	return (value);
}

char	*double_quote(t_save *save, char *line, int *i)
{
	int		index;
	char	*expand;
	char	*value;

	index = *i;
	(*i)++;
	while (line[*i] && line[*i] != '\"')
		(*i)++;
	if (!line[*i])
	{
		trouble("syntax error", NULL, "inclosed double quotes", 258);
		return (NULL);
	}
	value = ft_substr(line, index + 1, *i - index - 1);
	if (check_dollar(value) != 0)
	{
		expand = value;
		value = ft_expand(value, save->env, save->av);
		free (expand);
	}
	(*i)++;
	return (value);
}

void	redirection(t_token **head, char *str, int *i)
{
	if (str[*i] == '>' && str[*i + 1] == '>')
	{
		add_token_last(head, new_node(my_strdup(">>"), APPEND));
		(*i)++;
	}
	else if (str[*i] == '<' && str[*i + 1] == '<')
	{
		add_token_last(head, new_node(my_strdup("<<"), HERE_DOC));
		(*i)++;
	}
	else if (str[*i] == '>')
		add_token_last(head, new_node(my_strdup(">"), OUTPUT));
	else if (str[*i] == '<')
		add_token_last(head, new_node(my_strdup("<"), INPUT));
	(*i)++;
}

char	*quoting(t_save *save, char *line, int *i, char *value)
{
	char	*str;

	if (line[*i] == '\'')
	{
		str = single_quote(line, i);
		if (!str)
		{
			free(value);
			return (NULL);
		}
		value = my_strjoin (value, str);
	}
	else if (line[*i] == '\"')
	{
		str = double_quote(save, line, i);
		if (!str)
		{
			free(value);
			return (NULL);
		}
		value = my_strjoin(value, str);
	}
	return (value);
}

int	setting_word(t_save *save, t_token **temp, char *line, int *i)
{
	char	*value;
	char	*str;

	value = ft_strdup("");
	while (line[*i] && skip_char(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '\"')
			value = quoting(save, line, i, value);
		else if (line[*i] == '$')
			value = my_strjoin(value, dollar(save, temp, line, i));
		else
		{
			str = convert_char_str(line[(*i)++]);
			value = my_strjoin(value, str);
		}
		if (!value)
			return (1);
	}
	add_token_last(temp, new_node(value, WORD));
	return (0);
}
