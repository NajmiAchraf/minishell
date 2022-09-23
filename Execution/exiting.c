/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 23:03:57 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/23 20:49:53 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	trouble(char *cmd, char *arg, char *msg, int error_status)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd != NULL)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (arg != NULL)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg != NULL)
		ft_putstr_fd(msg, 2);
	ft_putstr_fd(".\n", 2);
	g_status = error_status;
	return (1);
}

void	trouble_exit(char *cmd, char *arg, char *msg, int exit_status)
{
	trouble(cmd, arg, msg, exit_status);
	exit(exit_status);
}

static int	check_exit(char *cmds)
{
	t_allways	aws;

	aws.i = 0;
	if (cmds[aws.i] == '-' || cmds[aws.i] == '+')
		aws.i++;
	if (cmds[aws.i] == '\0')
		return (1);
	while (cmds[aws.i])
	{
		if (!ft_isdigit(cmds[aws.i]))
			return (1);
		aws.i++;
	}
	return (0);
}

static int	exit_cases(t_final *node)
{
	t_allways	aws;

	aws.i = ft_lstlen(node->cmd);
	if (aws.i > 2 && !check_exit(node->cmd[1]))
	{
		ft_putstr_fd("exit\n", 2);
		trouble("exit", NULL, "too many arguments", 1);
		return (1);
	}
	else if (aws.i >= 2 && check_exit(node->cmd[1]))
	{
		ft_putstr_fd("exit\n", 2);
		trouble_exit("exit", NULL, "numeric argument required", 255);
	}
	else if (aws.i >= 2 && !check_exit(node->cmd[1]))
	{
		ft_putstr_fd("exit\n", 2);
		exit(ft_atoi(node->cmd[1]) % 256);
	}
	return (0);
}

int	exiting(t_final *node)
{
	t_allways	aws;

	aws.i = ft_lstlen(node->cmd);
	if (aws.i == 1)
	{
		ft_putstr_fd("exit\n", 2);
		exit(EXIT_SUCCESS);
	}
	else if (exit_cases(node))
		return (1);
	else
		exit(EXIT_FAILURE);
	return (0);
}
