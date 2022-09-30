/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 23:02:13 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/30 21:01:21 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*dir(void)
{
	char	cwd[FILENAME_MAX];

	getcwd(cwd, sizeof(cwd));
	return (ft_strdup(cwd));
}

static int	change_directory(t_vars *var, char *chemin)
{
	free(var->tmp1);
	var->tmp1 = dir();
	if (chdir(chemin))
		return (trouble("cd", chemin, "No such file or directory", 1));
	if (!check_env_var(var, "OLDPWD"))
	{
		free(var->tmp2);
		var->tmp2 = ft_strjoin("OLDPWD=", var->tmp1);
		ft_export(var, var->tmp2, 0);
	}
	if (!check_env_var(var, "PWD"))
	{
		free(var->tmp1);
		var->tmp1 = dir();
		free(var->tmp2);
		var->tmp2 = ft_strjoin("PWD=", var->tmp1);
		ft_export(var, var->tmp2, 0);
	}
	return (0);
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
	char	*pwd;

	pwd = dir();
	ft_putstr_fd(pwd, node->outfile);
	ft_putchar_fd('\n', node->outfile);
	free(pwd);
	return (0);
}
