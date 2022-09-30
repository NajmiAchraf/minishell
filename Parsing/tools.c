/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:52:39 by ohrete            #+#    #+#             */
/*   Updated: 2022/09/28 21:09:58 by ohrete           ###   ########.fr       */
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

t_token	*ft_lstlast1(t_token *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
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

int	allspaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!space(line[i]))
			return (0);
		i++;
	}
	return (1);
}
