/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:12:12 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/11 15:34:54 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*********************/
/* BUILTIN FUNCTIONS */
/*********************/

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

void	trouble_exit(char *cmd, char *arg, char *msg, int error_status)
{
	trouble(cmd, arg, msg, error_status);
	exit(error_status);
}

int	fork1(void)
{
	int pid;

	pid = fork();
	if (pid == -1)
		trouble("fork", NULL, "error", 1);
	return pid;
}

char	*dir()
{
	char	cwd[FILENAME_MAX];

	getcwd(cwd, sizeof(cwd));
	return (ft_strdup(cwd));
}

static int	echo_check(char *args)
{
	t_allways aws;

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
	t_allways aws;

	aws.i = 1;
	aws.k = 1;
	if (node->cmd[aws.i])
	{
		if (node->cmd[aws.i][0] == '-' && node->cmd[aws.i][1])
		{
			while (node->cmd[aws.i] && node->cmd[aws.i][0] == '-' && !echo_check(node->cmd[aws.i]))
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

static int	change_directory(t_vars *var, char *chemin)
{
	free(var->tmp1);
	var->tmp1 = dir();
	if (chdir(chemin))
	{
		printf("minishell: cd: %s: No such file or directory\n", chemin);
		return (1);
	}
	if (!check_env_var(var, "OLDPWD"))
		ft_export(var, ft_strjoin("OLDPWD=", var->tmp1), 0);
	if (!check_env_var(var, "PWD"))
		ft_export(var, ft_strjoin("PWD=", dir()), 0);
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

int	pwd(t_vars *var, t_final *node)
{
	ft_putstr_fd(dir(), node->outfile);
	ft_putchar_fd('\n', node->outfile);
	return (0);
}

int	export(t_vars *var, t_final *node)
{
	t_allways aws;

	aws.j = 0;
	if (!node->cmd[1])
		show_exp(var);
	else
	{
		aws.i = 1;
		while (node->cmd[aws.i])
		{
			aws.k = ft_export(var, node->cmd[aws.i], 0);
			if (aws.k == 1)
				aws.j = 1;
			aws.i++;
		}
	}
	return (aws.j);
}

int	unset(t_vars *var, t_final *node)
{
	t_allways aws;

	aws.i = 1;
	aws.j = 0;
	while (node->cmd[aws.i])
	{
		if (little_checker(node->cmd[aws.i]))
		{
			trouble("unset", node->cmd[aws.i], "not a valid identifier", 1);
			aws.j = 1;
		}
		else
			ft_unset(var, node->cmd[aws.i]);
		aws.i++;
	}
	return (aws.j);
}

int	environment(t_vars *var, t_final *node)
{
	t_allways aws;

	aws.i = 1;
	while (node->cmd[aws.i])
	{
		if (ft_strcmp(node->cmd[aws.i], "env"))
		{
			trouble("env", node->cmd[aws.i], "No such file or directory", 1);
			return (1);
		}
		aws.i++;
	}
	show_env(var);
	return (0);
}

static int	check_exit(char *cmds)
{
	int i, j;
	t_allways aws;

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

int	exiting(t_vars *var, t_final *node)
{
	t_allways aws;

	aws.i = ft_lstlen(node->cmd);
	if (aws.i == 1)
	{
		ft_putstr_fd("exit\n", 2);
		exit(EXIT_SUCCESS);
	}
	else if (aws.i > 2 && !check_exit(node->cmd[1]))
	{
		ft_putstr_fd("exit\n", 2);
		trouble("exit", NULL, "too many arguments", 1);
		return (1);
	}
	else if (aws.i >= 2 && check_exit(node->cmd[1]))
	{
		ft_putstr_fd("exit\n", 2);
		trouble("exit", NULL, "numeric argument required", 1);
		exit(255);
	}
	else if (aws.i >= 2 && !check_exit(node->cmd[1]))
	{
		ft_putstr_fd("exit\n", 2);
		exit(ft_atoi(node->cmd[1])%256);
	}
	else
		exit(EXIT_FAILURE);
	return (0);
}

int	builtincheck(char *name)
{
	if (!ft_strcmp(name, "echo") || !ft_strcmp(name, "cd")
		|| !ft_strcmp(name, "pwd") || !ft_strcmp(name, "export")
		|| !ft_strcmp(name, "unset") || !ft_strcmp(name, "env")
		|| !ft_strcmp(name, "exit"))
		return (0);
	return (1);
}

int	builtin(t_vars *var, t_final *node)
{
	if (!ft_strcmp(node->cmd[0], "echo"))
		return (echo(var, node));
	else if (!ft_strcmp(node->cmd[0], "cd"))
		return (cd(var, node));
	else if (!ft_strcmp(node->cmd[0], "pwd"))
		return (pwd(var, node));
	else if (!ft_strcmp(node->cmd[0], "export"))
		return (export(var, node));
	else if (!ft_strcmp(node->cmd[0], "unset"))
		return (unset(var, node));
	else if (!ft_strcmp(node->cmd[0], "env"))
		return (environment(var, node));
	else if (!ft_strcmp(node->cmd[0], "exit"))
		return (exiting(var, node));
	return (1);
}

char	*exe_path_set(t_vars *var, char *exe)
{
	t_allways aws;

	if (check_env_var(var, "PATH"))
		trouble_exit(exe, NULL, "PATH not set", 1);
	fill_path(var);
	aws.i = 0;
	while (var->exepath[aws.i])
	{
		if (!access(ft_strjoin(var->exepath[aws.i], exe), F_OK))
			return (ft_strjoin(var->exepath[aws.i], exe));
		aws.i++;
	}
	return (NULL);
}

void	fill_path(t_vars *var)
{
	t_allways aws;

	free1(var->tmpp);
	var->tmpp = ft_split(get_env_var(var, "PATH"), ':');
	free1(var->exepath);
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

void	initialisation(t_vars *var, char **env)
{
	var->tmp = malloc(sizeof(char));
	var->tmp1 = malloc(sizeof(char));
	var->tmpp = malloc(sizeof(char *));
	var->tmpp[0] = NULL;
	var->exepath = malloc(sizeof(char *));
	var->exepath[0] = NULL;
	var->hdocs = malloc(sizeof(char));
	var->hdocs[0] = '\0';
	var->env.env = env;
	var->pid = malloc(sizeof(int) * FILENAME_MAX);
	if (!env)
	{
		var->env.env = malloc(sizeof(char *));
		var->env.env[0] = NULL;
		return;
	}
	init_environment(var);
	init_export(var);
	ft_unset(var, "OLDPWD");
	ft_export(var, "OLDPWD", 1);
	ft_export(var, ft_strjoin("SHLVL=", ft_itoa(ft_atoi(get_env_var(var, "SHLVL")) + 1)), 0);
}

/* int	main(int ac, char *av[], char **env)
{
	t_vars	*var;
	char	cwd[1024];

	var = malloc(sizeof(t_vars));
	initialisation(var, env);

	ft_export(var, "TEST_MINISHELL=0", 1);
	ft_export(var, "ENV_EXP_UNST=0", 1);
	ft_export(var, "ENV_EXP_UNST1=0", 1);
	ft_export(var, "ENV_EXP_UNST2=0", 1);
	ft_export(var, "ENV_EXP_UNST3=0", 1);
	ft_export(var, "ENV_EXP_UNST4=0", 1);
	show_env(var);
	printf("--------------------------------------------------------------------1\n");
	show_exp(var);
	printf("--------------------------------------------------------------------2\n");
	ft_unset(var, "TEST_MINISHELL");
	ft_unset(var, "ENV_EXP_UNST");
	ft_unset(var, "ENV_EXP_UNST1");
	ft_unset(var, "ENV_EXP_UNST4");
	ft_unset(var, "ENV_EXP_UNST3");
	ft_unset(var, "ENV_EXP_UNST2");
	show_env(var);
	printf("--------------------------------------------------------------------3\n");
	show_exp(var);
	printf("--------------------------------------------------------------------4\n");
	printf("%s\n", get_env_var(var, "PATH"));
	


	execv(ecmd->name, ecmd->args);

	fill_in_test0(var);
	runcmd(var->cmd[var->cod], var);
	++var->cod;
	fill_in_test1(var);
	runcmd(var->cmd[var->cod], var);
	++var->cod;
	fill_in_test2(var);
	runcmd(var->cmd[var->cod], var);
	++var->cod;
	one_pipe_fill_in_test(var);
	runcmd(var->cmd[var->cod], var);
	++var->cod;
	two_pipes_fill_in_test(var);
	runcmd(var->cmd[var->cod], var);
	++var->cod;
	
	while (1)
	{
		// chdir("..");
		getcwd(cwd, sizeof(cwd));
		free(var->tmpp);
		var->tmpp = ft_split(cwd, '/');
		if (ft_lstlen(var->tmpp) > 0)
			printf("%s$ %s%s@%s %s%s %s|%s", C_GREEN, C_YELOW, get_env_var(var, "USER"), get_env_var(var, "HOSTNAME"), C_CYAN, var->tmpp[ft_lstlen(var->tmpp) - 1], C_RED, C_RES);
		else
			printf("%s$ %s%s@%s %s%s %s|%s", C_GREEN, C_YELOW, get_env_var(var, "USER"), get_env_var(var, "HOSTNAME"), C_CYAN, cwd, C_RED, C_RES);
		free(var->buff);
		var->buff = readline("→ ");
		add_history(var->buff);
		// printf("%s\n", var->buff);


		// fill_in_test3(var);
		// fill_in_test5(var);
		// fill_in_test0(var);
		// fill_in_test1(var);
		// two_pipes_fill_in_test0(var);
		// two_pipes_fill_in_test0test(var);
		one_pipe_fill_in_test0(var);
		// one_pipe_fill_in_test0test(var);
		system("leaks minishell");
		runcmd(var->cmd[var->cod], var);
		++var->cod;
		runPipedCommands(var);
		// fill_in_test2(var);
		// runcmd(var->cmd[var->cod], var);
		// ++var->cod;
	}
	return (0);
} */

