/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 23:02:13 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/24 11:37:04 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	change_directory(t_vars *var, char *chemin)
{
	free(var->tmp1);
	var->tmp1 = dir();
	if (chdir(chemin))
		return (trouble("cd", chemin, "No such file or directory", 1));
	if (!check_env_var(var, "OLDPWD"))
		ft_export(var, ft_strjoin("OLDPWD=", var->tmp1), 0);
	if (!check_env_var(var, "PWD"))
		ft_export(var, ft_strjoin("PWD=", dir()), 0);
	return (0);
}

char	*dir(void)
{
	char	cwd[FILENAME_MAX];

	getcwd(cwd, sizeof(cwd));
	return (ft_strdup(cwd));
}

int	cd(t_vars *var, t_final *node)
{
	if (ft_lstlen(node->cmd) == 1)
	{
		if (check_env_var(var, "HOME"))
			return (trouble("cd", NULL, "HOME not set", 1));
		else
			return (change_directory(var, get_env_var(var, "HOME")));
	}
	else
		return (change_directory(var, node->cmd[1]));
	return (0);
}

int	pwd(t_final *node)
{
	ft_putstr_fd(dir(), node->outfile);
	ft_putchar_fd('\n', node->outfile);
	return (0);
}
