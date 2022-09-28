/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 18:25:58 by ohrete            #+#    #+#             */
/*   Updated: 2022/09/27 23:26:19 by ohrete           ###   ########.fr       */
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
			return (NULL);
		value = my_strjoin (value, str);
	}
	else if (line[*i] == '\"')
	{
		str = double_quote(save, line, i);
		if (!str)
			return (NULL);
		value = my_strjoin(value, str);
	}
	return (value);
}

/*int	setting_word(t_save *save, t_token **temp, char *line, int *i)
{
	char	*value;
	char	*str;

	value = ft_strdup("");
	while (line[*i] && skip_char(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '\"')
		{
			value = quoting(save, line, i, value);
		}
		else if (line[*i] == '$')
			value = ft_strjoin(value, dollar(save, temp, line, i));
		else
		{
			str = convert_char_str(line[(*i)++]);
			value = my_strjoin (value, str);
		}
		if (!value)
			return (1);
	}
	add_token_last(temp, new_node(value, WORD));
	return (0);
}*/


int	setting_word(t_save *save, t_token **temp, char *line, int *i)
{
	char	*value;
	char	*str;

	value = malloc (sizeof (char));
	value[0] = '\0';
	while (line[*i] && skip_char(line[*i]))
	{
		if (line[*i] == '\'')
		{
			str = single_quote(line, i);
			if (!str)
				return (1);
			value = my_strjoin (value, str);
		}
		else if (line[*i] == '\"')
		{
			str = double_quote(save, line, i);
			if (!str)
				return (1);
			value = my_strjoin(value, str);
		}
		else if (line[*i] == '$')
			value = ft_strjoin(value, dollar(save, temp, line, i));
		else
		{
			str = convert_char_str(line[(*i)++]);
			if (!str)
				return (1);
			value = my_strjoin (value, str);
		}
	}
	add_token_last(temp, new_node(value, WORD));
	return (0);
}
