/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 21:12:38 by ohrete            #+#    #+#             */
/*   Updated: 2022/10/06 15:22:27 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_error(char *str)
{
	int	i;
	int	f;

	i = 0;
	f = 0;
	if (str[0] == '|')
		return (0);
	while (str[i] != '\0')
	{
		if (f == 0 && (str[i] == '\'' || str[i] == '\"'))
			f = str[i];
		else if (f == str[i])
			f = 0;
		if (str[i] == '|' && str[i + 1] == '|' && f == 0)
			return (0);
		i++;
	}
	if (str[ft_strlen(str) - 1] == '|')
		return (0);
	return (1);
}
