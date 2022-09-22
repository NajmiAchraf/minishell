/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 23:18:46 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/22 01:44:42 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	echo_check(char *args)
{
	t_allways	aws;

	aws.j = 1;
	while (args[aws.j])
	{
		if (args[aws.j] != 'n')
			return (1);
		aws.j++;
	}
	return (0);
}

int	echo(t_vars *var, t_final *node)
{
	t_allways	aws;

	aws.i = 1;
	aws.k = 1;
	if (node->cmd[aws.i])
	{
		if (node->cmd[aws.i][0] == '-' && node->cmd[aws.i][1])
		{
			while (node->cmd[aws.i] && node->cmd[aws.i][0] == '-'
				&& !echo_check(node->cmd[aws.i]))
			{
				aws.k = 0;
				aws.i++;
			}
		}
		while (node->cmd[aws.i])
		{
			ft_putstr_fd(node->cmd[aws.i], node->outfile);
			aws.i++;
			if (node->cmd[aws.i])
				ft_putchar_fd(' ', node->outfile);
		}
	}
	if (aws.k)
		ft_putchar_fd('\n', node->outfile);
	return (0);
}
