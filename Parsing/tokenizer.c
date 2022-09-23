/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 23:00:09 by ohrete            #+#    #+#             */
/*   Updated: 2022/09/22 22:59:30 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*convert_char_str(char c)
{
	char	*str;

	str = malloc (sizeof (char) * 2);
	if (!str)
	{
		ft_putstr_fd("error allocation\n", 2);
		return (NULL);
	}
	str[0] = c;
	str[1] = '\0';
	return (str);
}

void	pipe_sign(t_token **head, int *i)
{
	add_token_last(head, new_node(my_strdup("|"), PIPE));
	(*i)++;
}

void	tokens(char *line, t_token **temp, t_save *save, int *i)
{
	if (space(line[*i]))
		(*i)++;
	else if (line[*i] == '<' || line[*i] == '>')
		redirection(temp, line, i);
	else if (line[*i] == '|')
		pipe_sign(temp, i);
	else
		setting_word(save, temp, line, i);
}

t_token	*tokenizer(char *line, char **av, t_env *env)
{
	int		i;
	t_token	*temp;
	t_save	*save;

	save = (t_save *)malloc(sizeof(t_save));
	save->av = av;
	save->env = env;
	i = 0;
	temp = NULL;
	while (line[i])
	{
		tokens(line, &temp, save, &i);
	}
	free(save);
	return (temp);
}
