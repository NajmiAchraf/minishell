/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 23:00:09 by ohrete            #+#    #+#             */
/*   Updated: 2022/09/28 00:04:07 by ohrete           ###   ########.fr       */
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
	add_token_last(head, new_node(ft_strdup(PIPE), 182));
	(*i)++;
}

t_token	*ft_lstlast1(t_token *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
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

void	check_last_word(t_token **temp, t_save *save)
{
	t_token	*tmp;

	tmp = *temp;
	if (!ft_strcmp(ft_lstlast1(tmp)->str, PIPE)
		|| !ft_strcmp(ft_lstlast1(tmp)->str, "A")
		|| !ft_strcmp(ft_lstlast1(tmp)->str, "H")
		|| !ft_strcmp(ft_lstlast1(tmp)->str, "W")
		|| !ft_strcmp(ft_lstlast1(tmp)->str, "<")
		|| !ft_strcmp(ft_lstlast1(tmp)->str, ">"))
		save->error = trouble(NULL, NULL, "syntax error", 258);
}

int allspaces(char *line)
{
	int i;
	 
	i = 0;
	while(line[i])
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return(1);
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
