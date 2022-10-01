/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:12:12 by anajmi            #+#    #+#             */
/*   Updated: 2022/10/01 14:32:11 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		trouble("fork", NULL, "error", 1);
	return (pid);
}

void	fill_path(t_vars *var)
{
	t_allways	aws;

	free(var->tmp);
	var->tmp = get_env_var(var, "PATH");
	ft_free(var->tmpp);
	var->tmpp = ft_split(var->tmp, ':');
	ft_free(var->exepath);
	var->exepath = malloc(sizeof(char *) * (ft_lstlen(var->tmpp) + 3));
	aws.i = 0;
	while (var->tmpp[aws.i])
	{
		var->exepath[aws.i] = ft_strjoin(var->tmpp[aws.i], "/");
		aws.i++;
	}
	var->exepath[aws.i] = ft_strdup("./");
	var->exepath[aws.i + 1] = ft_strdup("");
	var->exepath[aws.i + 2] = NULL;
}

char	*exe_path_set(t_vars *var, char *exe)
{
	t_allways	aws;

	if (check_env_var(var, "PATH"))
	{
		if (!access(exe, F_OK))
			return (exe);
		trouble_exit(exe, NULL, "PATH not set", 1);
	}
	fill_path(var);
	aws.i = 0;
	while (var->exepath[aws.i])
	{
		free(var->tmp);
		var->tmp = ft_strjoin(var->exepath[aws.i], exe);
		if (!access(var->tmp, F_OK))
			return (var->tmp);
		aws.i++;
	}
	return (NULL);
}

static void	initialisation_tmp(t_vars *var)
{
	var->tmp = NULL;
	var->tmp3 = NULL;
	var->tmp4 = NULL;
	var->tmp5 = NULL;
	var->tmp6 = NULL;
	var->tmp7 = NULL;
	var->tmp8 = NULL;
	var->tmpp = malloc(sizeof(char *));
	var->tmpp[0] = NULL;
}

void	initialisation(t_vars *var, char **av, char **env)
{
	initialisation_tmp(var);
	var->main_name = ft_strdup(av[0]);
	var->exepath = malloc(sizeof(char *));
	var->exepath[0] = NULL;
	var->hdocs = malloc(sizeof(char));
	var->hdocs[0] = '\0';
	var->infile = -1;
	var->env.env = env;
	var->pid = malloc(sizeof(int) * FILENAME_MAX);
	if (!env)
	{
		var->env.env = malloc(sizeof(char *));
		var->env.env[0] = NULL;
		return ;
	}
	init_environment(var);
	init_export(var);
	var->tmp0 = get_env_var(var, "SHLVL");
	var->tmp1 = ft_itoa(ft_atoi(var->tmp0) + 1);
	var->tmp2 = ft_strjoin("SHLVL=", var->tmp1);
	ft_export(var, var->tmp2, 0);
	ft_unset(var, "OLDPWD");
	ft_export(var, "OLDPWD", 1);
}
