/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:12:12 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/05 12:54:53 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_in_test0(t_vars *var)
{
	/*echo $PWD*/

	var->cmd[var->cod] = (t_cmd*)malloc(sizeof(t_cmd));

	var->cmd[var->cod]->type = EXEC;

	var->cmd[var->cod]->exe = (t_execcmd*)malloc(sizeof(t_execcmd));

	var->cmd[var->cod]->exe->type = EXEC;

	ft_strlcpy(var->cmd[var->cod]->exe->name, "echo", 5);

	// var->cmd[var->cod]->exe->args[0] = ft_strdup("$USERNAM E$USER=0$USER");
	// var->cmd[var->cod]->exe->args[0] = ft_strdup("ZLL=1$ZLL23$USER");
	var->cmd[var->cod]->exe->args[0] = ft_strdup("$$");
	var->cmd[var->cod]->exe->args[1] = NULL;
	// ft_strlcpy(var->cmd[var->cod]->pip->left->exe->args[0], "-la", 4);
	// ft_bzero(var->cmd[var->cod]->pip->left->exe->args[1], 1);
}

void	fill_in_test1(t_vars *var)
{
	/*export abc=123*/

	var->cmd[var->cod] = (t_cmd*)malloc(sizeof(t_cmd));

	var->cmd[var->cod]->type = EXEC;

	var->cmd[var->cod]->exe = (t_execcmd*)malloc(sizeof(t_execcmd));

	var->cmd[var->cod]->exe->type = EXEC;

	ft_strlcpy(var->cmd[var->cod]->exe->name, "export", 7);

	var->cmd[var->cod]->exe->args[0] = ft_strdup(ft_strjoin(ft_strjoin("a", ft_itoa(var->cod)), "c=1$XDG_SESSION_TYPE:23$USER"));
	var->cmd[var->cod]->exe->args[1] = NULL;
}

void	fill_in_test2(t_vars *var)
{
	/*export*/

	var->cmd[var->cod] = (t_cmd*)malloc(sizeof(t_cmd));

	var->cmd[var->cod]->type = EXEC;

	var->cmd[var->cod]->exe = (t_execcmd*)malloc(sizeof(t_execcmd));

	var->cmd[var->cod]->exe->type = EXEC;

	ft_strlcpy(var->cmd[var->cod]->exe->name, "export", 7);

	var->cmd[var->cod]->exe->args[0] = NULL;
}

void	fill_in_test3(t_vars *var)
{

	var->cmd[var->cod] = (t_cmd*)malloc(sizeof(t_cmd));

	var->cmd[var->cod]->type = EXEC;

	var->cmd[var->cod]->exe = (t_execcmd*)malloc(sizeof(t_execcmd));

	var->cmd[var->cod]->exe->type = EXEC;

	ft_strlcpy(var->cmd[var->cod]->exe->name, "cd", 5);

	var->cmd[var->cod]->exe->args[0] = ft_strdup("~");
	var->cmd[var->cod]->exe->args[1] = NULL;
}

void	fill_in_test4(t_vars *var)
{
	/* pwd */

	var->cmd[var->cod] = (t_cmd*)malloc(sizeof(t_cmd));

	var->cmd[var->cod]->type = EXEC;

	var->cmd[var->cod]->exe = (t_execcmd*)malloc(sizeof(t_execcmd));

	var->cmd[var->cod]->exe->type = EXEC;

	ft_strlcpy(var->cmd[var->cod]->exe->name, "pwd", 4);

	var->cmd[var->cod]->exe->args[0] = NULL;
}

void	fill_in_test5(t_vars *var)
{
	/* pwd */

	var->cmd[var->cod] = (t_cmd*)malloc(sizeof(t_cmd));

	var->cmd[var->cod]->type = EXEC;

	var->cmd[var->cod]->exe = (t_execcmd*)malloc(sizeof(t_execcmd));

	var->cmd[var->cod]->exe->type = EXEC;

	ft_strlcpy(var->cmd[var->cod]->exe->name, "ls", 3);

	var->cmd[var->cod]->exe->args[0] = NULL;
}

void	one_pipe_fill_in_test0(t_vars *var)
{
	/*ls -la | wc -l*/
	
	var->cmd[var->cod] = (t_cmd*)malloc(sizeof(t_cmd));
	
	var->cmd[var->cod]->type = PIPE;
	
	var->cmd[var->cod]->pip = (t_pipecmd*)malloc(sizeof(t_pipecmd));
	
	var->cmd[var->cod]->pip->type = PIPE;
	var->cmd[var->cod]->pip->left = (t_cmd*)malloc(sizeof(t_cmd));

	var->cmd[var->cod]->pip->left->type = EXEC;

	var->cmd[var->cod]->pip->left->exe = (t_execcmd*)malloc(sizeof(t_execcmd));

	var->cmd[var->cod]->pip->left->exe->type = EXEC;

	ft_strlcpy(var->cmd[var->cod]->pip->left->exe->name, "ls", 3);

	var->cmd[var->cod]->pip->left->exe->args[0] = ft_strdup("ls");
	var->cmd[var->cod]->pip->left->exe->args[1] = ft_strdup("-la");
	var->cmd[var->cod]->pip->left->exe->args[2] = NULL;
	// ft_strlcpy(var->cmd[var->cod]->pip->left->exe->args[0], "-la", 4);
	// ft_bzero(var->cmd[var->cod]->pip->left->exe->args[1], 1);

	var->cmd[var->cod]->pip->right = (t_cmd*)malloc(sizeof(t_cmd));
	
	var->cmd[var->cod]->pip->right->type = EXEC;
	
	var->cmd[var->cod]->pip->right->exe = (t_execcmd*)malloc(sizeof(t_execcmd));

	var->cmd[var->cod]->pip->right->exe->type = EXEC;

	ft_strlcpy(var->cmd[var->cod]->pip->right->exe->name, "wc", 3);

	var->cmd[var->cod]->pip->right->exe->args[0] = ft_strdup("wc");
	var->cmd[var->cod]->pip->right->exe->args[1] = ft_strdup("-l");
	var->cmd[var->cod]->pip->right->exe->args[2] = NULL;
	// ft_strlcpy(var->cmd[var->cod]->pip->right->pip->right->exe->args[0], "-l", 3);
	// ft_bzero(var->cmd[var->cod]->pip->right->pip->right->exe->args[1], 1);
	// printf("%s\n", var->cmd[var->cod]->pip->right->pip->right->exe->args[0]);
}

void	one_pipe_fill_in_test0test(t_vars *var)
{
	/*ls -la | wc -l*/
	
	var->cmd[var->cod] = (t_cmd*)malloc(sizeof(t_cmd));
	
	var->cmd[var->cod]->type = PIPE;
	
	var->cmd[var->cod]->pip = (t_pipecmd*)malloc(sizeof(t_pipecmd));
	
	var->cmd[var->cod]->pip->type = PIPE;
	var->cmd[var->cod]->pip->left = (t_cmd*)malloc(sizeof(t_cmd));

	var->cmd[var->cod]->pip->left->type = EXEC;

	var->cmd[var->cod]->pip->left->exe = (t_execcmd*)malloc(sizeof(t_execcmd));

	var->cmd[var->cod]->pip->left->exe->type = EXEC;

	ft_strlcpy(var->cmd[var->cod]->pip->left->exe->name, "wc", 3);

	var->cmd[var->cod]->pip->left->exe->args[0] = ft_strdup("wc");
	var->cmd[var->cod]->pip->left->exe->args[1] = ft_strdup("-l");
	var->cmd[var->cod]->pip->left->exe->args[2] = NULL;
	// ft_strlcpy(var->cmd[var->cod]->pip->left->exe->args[0], "-la", 4);
	// ft_bzero(var->cmd[var->cod]->pip->left->exe->args[1], 1);

	var->cmd[var->cod]->pip->right = (t_cmd*)malloc(sizeof(t_cmd));
	
	var->cmd[var->cod]->pip->right->type = EXEC;
	
	var->cmd[var->cod]->pip->right->exe = (t_execcmd*)malloc(sizeof(t_execcmd));

	var->cmd[var->cod]->pip->right->exe->type = EXEC;

	ft_strlcpy(var->cmd[var->cod]->pip->right->exe->name, "ls", 3);

	var->cmd[var->cod]->pip->right->exe->args[0] = ft_strdup("ls");
	var->cmd[var->cod]->pip->right->exe->args[1] = ft_strdup("-la");
	var->cmd[var->cod]->pip->right->exe->args[2] = NULL;
	// ft_strlcpy(var->cmd[var->cod]->pip->right->pip->right->exe->args[0], "-l", 3);
	// ft_bzero(var->cmd[var->cod]->pip->right->pip->right->exe->args[1], 1);
	// printf("%s\n", var->cmd[var->cod]->pip->right->pip->right->exe->args[0]);
}

void	one_pipe_fill_in_test1(t_vars *var)
{
	/*export abc=123 | ls -l*/
	
	var->cmd[var->cod] = (t_cmd*)malloc(sizeof(t_cmd));
	
	var->cmd[var->cod]->type = PIPE;
	
	var->cmd[var->cod]->pip = (t_pipecmd*)malloc(sizeof(t_pipecmd));
	
	var->cmd[var->cod]->pip->type = PIPE;
	var->cmd[var->cod]->pip->left = (t_cmd*)malloc(sizeof(t_cmd));

	var->cmd[var->cod]->pip->left->type = EXEC;

	var->cmd[var->cod]->pip->left->exe = (t_execcmd*)malloc(sizeof(t_execcmd));

	var->cmd[var->cod]->pip->left->exe->type = EXEC;

	ft_strlcpy(var->cmd[var->cod]->pip->left->exe->name, "export", 7);

	var->cmd[var->cod]->pip->left->exe->args[0] = ft_strdup(ft_strjoin(ft_strjoin("a", ft_itoa(var->cod)), "c=1$XDG_SESSION_TYPE:23$USER"));
	var->cmd[var->cod]->pip->left->exe->args[1] = NULL;
	// ft_strlcpy(var->cmd[var->cod]->pip->left->exe->args[0], "-la", 4);
	// ft_bzero(var->cmd[var->cod]->pip->left->exe->args[1], 1);

	var->cmd[var->cod]->pip->right = (t_cmd*)malloc(sizeof(t_cmd));
	
	var->cmd[var->cod]->pip->right->type = EXEC;
	
	var->cmd[var->cod]->pip->right->exe = (t_execcmd*)malloc(sizeof(t_execcmd));

	var->cmd[var->cod]->pip->right->exe->type = EXEC;

	ft_strlcpy(var->cmd[var->cod]->pip->right->exe->name, "ls", 3);

	var->cmd[var->cod]->pip->right->exe->args[0] = ft_strdup("-l");
	var->cmd[var->cod]->pip->right->exe->args[1] = NULL;
	// ft_strlcpy(var->cmd[var->cod]->pip->right->pip->right->exe->args[0], "-l", 3);
	// ft_bzero(var->cmd[var->cod]->pip->right->pip->right->exe->args[1], 1);
	// printf("%s\n", var->cmd[var->cod]->pip->right->pip->right->exe->args[0]);
}

void	two_pipes_fill_in_test0(t_vars *var)
{
	/*ls -la | grep -r "mini" | wc -l*/
	
	var->cmd[var->cod] = (t_cmd*)malloc(sizeof(t_cmd));
	
	var->cmd[var->cod]->type = PIPE;
	
	var->cmd[var->cod]->pip = (t_pipecmd*)malloc(sizeof(t_pipecmd));
	
	var->cmd[var->cod]->pip->type = PIPE;
	var->cmd[var->cod]->pip->left = (t_cmd*)malloc(sizeof(t_cmd));

	var->cmd[var->cod]->pip->left->type = EXEC;

	var->cmd[var->cod]->pip->left->exe = (t_execcmd*)malloc(sizeof(t_execcmd));

	var->cmd[var->cod]->pip->left->exe->type = EXEC;

	ft_strlcpy(var->cmd[var->cod]->pip->left->exe->name, "grep", 3);

	var->cmd[var->cod]->pip->left->exe->args[0] = ft_strdup("grep");
	var->cmd[var->cod]->pip->left->exe->args[1] = ft_strdup("mini");
	var->cmd[var->cod]->pip->left->exe->args[2] = NULL;

	var->cmd[var->cod]->pip->right = (t_cmd*)malloc(sizeof(t_cmd));
	
	var->cmd[var->cod]->pip->right->type = PIPE;
	
	var->cmd[var->cod]->pip->right->pip = (t_pipecmd*)malloc(sizeof(t_pipecmd));

	var->cmd[var->cod]->pip->right->pip->type = PIPE;
	
	var->cmd[var->cod]->pip->right->pip->left = (t_cmd*)malloc(sizeof(t_cmd));
	
	var->cmd[var->cod]->pip->right->pip->left->type = EXEC;
	var->cmd[var->cod]->pip->right->pip->left->exe = (t_execcmd*)malloc(sizeof(t_execcmd));

	var->cmd[var->cod]->pip->right->pip->left->exe->type = EXEC;

	ft_strlcpy(var->cmd[var->cod]->pip->right->pip->left->exe->name, "ls", 5);

	var->cmd[var->cod]->pip->right->pip->left->exe->args[0] = ft_strdup("ls");
	var->cmd[var->cod]->pip->right->pip->left->exe->args[0] = ft_strdup("-l");
	var->cmd[var->cod]->pip->right->pip->left->exe->args[1] = NULL;
	
	var->cmd[var->cod]->pip->right->pip->right = (t_cmd*)malloc(sizeof(t_cmd));
	
	var->cmd[var->cod]->pip->right->pip->right->type = EXEC;
	
	var->cmd[var->cod]->pip->right->pip->right->exe = (t_execcmd*)malloc(sizeof(t_execcmd));

	var->cmd[var->cod]->pip->right->pip->right->exe->type = EXEC;

	ft_strlcpy(var->cmd[var->cod]->pip->right->pip->right->exe->name, "wc", 3);

	var->cmd[var->cod]->pip->right->pip->right->exe->args[0] = ft_strdup("wc");
	var->cmd[var->cod]->pip->right->pip->right->exe->args[0] = ft_strdup("-l");
	var->cmd[var->cod]->pip->right->pip->right->exe->args[1] = NULL;
	// ft_strlcpy(var->cmd[var->cod]->pip->right->pip->right->exe->args[0], "-l", 3);
	// ft_bzero(var->cmd[var->cod]->pip->right->pip->right->exe->args[1], 1);
	// printf("%s\n", var->cmd[var->cod]->pip->right->pip->right->exe->args[0]);
}

void	two_pipes_fill_in_test0test(t_vars *var)
{
	/*ls -l | grep mini | wc -l*/
	
	var->cmd[var->cod] = (t_cmd*)malloc(sizeof(t_cmd));
	
	var->cmd[var->cod]->type = PIPE;
	
	var->cmd[var->cod]->pip = (t_pipecmd*)malloc(sizeof(t_pipecmd));
	
	var->cmd[var->cod]->pip->type = PIPE;

	var->cmd[var->cod]->pip->left = (t_cmd*)malloc(sizeof(t_cmd));
	
	var->cmd[var->cod]->pip->left->type = PIPE;
	
	var->cmd[var->cod]->pip->left->pip = (t_pipecmd*)malloc(sizeof(t_pipecmd));

	var->cmd[var->cod]->pip->left->pip->type = PIPE;
	
	var->cmd[var->cod]->pip->left->pip->left = (t_cmd*)malloc(sizeof(t_cmd));
	
	var->cmd[var->cod]->pip->left->pip->left->type = EXEC;
	var->cmd[var->cod]->pip->left->pip->left->exe = (t_execcmd*)malloc(sizeof(t_execcmd));

	var->cmd[var->cod]->pip->left->pip->left->exe->type = EXEC;

	ft_strlcpy(var->cmd[var->cod]->pip->left->pip->left->exe->name, "ls", 5);

	var->cmd[var->cod]->pip->left->pip->left->exe->args[0] = ft_strdup("ls");
	var->cmd[var->cod]->pip->left->pip->left->exe->args[0] = ft_strdup("-l");
	var->cmd[var->cod]->pip->left->pip->left->exe->args[1] = NULL;
	
	var->cmd[var->cod]->pip->left->pip->right = (t_cmd*)malloc(sizeof(t_cmd));
	
	var->cmd[var->cod]->pip->left->pip->right->type = EXEC;
	
	var->cmd[var->cod]->pip->left->pip->right->exe = (t_execcmd*)malloc(sizeof(t_execcmd));

	var->cmd[var->cod]->pip->left->pip->right->exe->type = EXEC;

	ft_strlcpy(var->cmd[var->cod]->pip->left->pip->right->exe->name, "grep", 3);

	var->cmd[var->cod]->pip->left->pip->right->exe->args[0] = ft_strdup("grep");
	var->cmd[var->cod]->pip->left->pip->right->exe->args[0] = ft_strdup("mini");
	var->cmd[var->cod]->pip->left->pip->right->exe->args[1] = NULL;


	var->cmd[var->cod]->pip->right = (t_cmd*)malloc(sizeof(t_cmd));

	var->cmd[var->cod]->pip->right->type = EXEC;

	var->cmd[var->cod]->pip->right->exe = (t_execcmd*)malloc(sizeof(t_execcmd));

	var->cmd[var->cod]->pip->right->exe->type = EXEC;

	ft_strlcpy(var->cmd[var->cod]->pip->right->exe->name, "wc", 3);

	var->cmd[var->cod]->pip->right->exe->args[0] = ft_strdup("wc");
	var->cmd[var->cod]->pip->right->exe->args[1] = ft_strdup("-l");
	var->cmd[var->cod]->pip->right->exe->args[2] = NULL;
}


/*********************/
/* BUILTIN FUNCTIONS */
/*********************/

void	trouble(char *s)
{
	printf("trouble in %s.\n", s);
	exit(0);
}

int	fork1(void)
{
	int pid;

	pid = fork();
	if (pid == -1)
		trouble("fork");
	return pid;
}

char	*dir()
{
	// char	cwd[FILENAME_MAX];
	char	*cwd;

	cwd = (char *)malloc(sizeof(char) * FILENAME_MAX);
	getcwd(cwd, sizeof(cwd));
	return (cwd);
}

int	echo_check(char *args)
{
	t_allways aws;

	aws.j = 1;
	while (args[aws.j])
	{
		if (args[aws.j] != 'n')
			return (0);
		aws.j++;
	}
	return (1);
}

int	echo(t_vars *var, t_execcmd *ecmd)
{
	t_allways aws;

	aws.i = 0;
	aws.k = 1;
	if (ecmd->args[aws.i][0] == '-' && ecmd->args[aws.i][1])
	{
		while (ecmd->args[aws.i])
		{
			if (!echo_check(ecmd->args[aws.i]))
				break;
			aws.k = 0;
			aws.i++;
		}
	}
	while (ecmd->args[aws.i])
	{
		printf("%s ", ecmd->args[aws.i]);
		aws.i++;
	}
	printf("\b");
	if (aws.k)
		printf("\n");
	return (1);
}

int	cd(t_vars *var, t_execcmd *ecmd)
{
	if (check_env_var(var, "HOME"))
	{
		if (ft_lstlen(ecmd->args) == 0)
		{
			ecmd->args[0] = ft_strdup(get_env_var(var, "HOME"));
			ecmd->args[1] = NULL;
		}
		else if (!ft_strcmp(ecmd->args[0], "~"))
		{
			free(ecmd->args[0]);
			ecmd->args[0] = ft_strdup(get_env_var(var, "HOME"));
		}
	}
	else
		trouble("cd $HOME");

	if (ft_lstlen(ecmd->args) > 1 && ecmd->args[0][0] != '-')
	{
		printf("minishell: cd: too many arguments\n");
		return (0);
	}
	else if (ecmd->args[0][0] == '-')
	{
		printf("minishell: cd: %s: invalid option\n", ecmd->args[0]);
		return (0);
	}
	else if (check_env_var(var, "OLDPWD") && check_env_var(var, "PWD"))
	{
		free(var->tmp3);
		var->tmp3 = ft_strdup(get_env_var(var, "OLDPWD"));
		ft_export(var, ft_strjoin("OLDPWD=", dir()), 0);
		if (chdir(ecmd->args[0]))
		{
			ft_export(var, ft_strjoin("OLDPWD=", var->tmp3), 0);
			printf("minishell: cd: %s: No such file or directory\n", ecmd->args[0]);
			return (0);
		}
		pwd(var);
		ft_export(var, ft_strjoin("PWD=", dir()), 0);
	}
	else
		trouble("cd $PWD");
	return (1);
}

int	pwd(t_vars *var)
{
	printf("%s\n", get_env_var(var, "PWD"));
	return (1);
}

int	export(t_vars *var, t_execcmd *ecmd)
{
	t_allways aws;

	if (!ecmd->args[0])
		show_exp(var);
	else
	{
		aws.i = 0;
		while (ecmd->args[aws.i])
		{
			// if (ft_isalpha(ecmd->args[aws.i][0]) || ecmd->args[aws.i][0] == '_' || ecmd->args[aws.i][0] == '$')
				ft_export(var, ecmd->args[aws.i], 0);
			// else
			// 	printf("bash: export: `%s': not a valid identifier\n", ecmd->args[aws.i]);
			aws.i++;
		}
	}
	return (1);
}

int	unset(t_vars *var, t_execcmd *ecmd)
{
	t_allways aws;

	aws.i = 0;
	while (ecmd->args[aws.i])
	{
		ft_unset(var, ecmd->args[aws.i]);
		aws.i++;
	}
	show_exp(var);
	return (1);
}

int	environment(t_vars *var, t_execcmd *ecmd)
{
	if (!ecmd->args[0])
		show_env(var);
	else
		printf("env: ‘%s’: No such file or directory\n", ecmd->args[0]);
	return (1);
}


int	builtincheck(char *name)
{
	if (!ft_strcmp(name, "echo") || !ft_strcmp(name, "cd")
		|| !ft_strcmp(name, "pwd") || !ft_strcmp(name, "export")
		|| !ft_strcmp(name, "unset") || !ft_strcmp(name, "env")
		|| !ft_strcmp(name, "exit"))
		return (1);
	return (0);
}

int	builtin(t_vars *var, t_execcmd *ecmd)
{
/*	◦ exit with no options */
	if (!ft_strcmp(ecmd->name , "echo"))
		return (echo(var, ecmd));
	else if (!ft_strcmp(ecmd->name , "cd"))
		return (cd(var, ecmd));
	else if (!ft_strcmp(ecmd->name , "pwd"))
		return (pwd(var));
	else if (!ft_strcmp(ecmd->name , "export"))
		return (export(var, ecmd));
	else if (!ft_strcmp(ecmd->name , "unset"))
		return (unset(var, ecmd));
	else if (!ft_strcmp(ecmd->name , "env"))
		return (environment(var, ecmd));
	// else if (!ft_strcmp(ecmd->name , "exit"))
	// 	return (exit(EXIT_SUCCESS));
	return (0);
}

char	*exe_path_set(t_vars *var, char *exe)
{
	t_allways aws;

	aws.i = 0;
	while (var->exepath[aws.i])
	{
		if (!access(ft_strjoin(var->exepath[aws.i], exe), F_OK))
			return (ft_strjoin(var->exepath[aws.i], exe));
		aws.i++;
	}
	return (NULL);
}

void	runcmd(t_cmd *cmd, t_vars *var)
{
	t_execcmd	*ecmd;
	t_redircmd	*rcmd;
	t_pipecmd	*pcmd;

	// if (cmd == 0)
	// 	exit(0);

	if (cmd->type == EXEC)
	{
		ecmd = cmd->exe;
		size_t i = 0;
		if (ecmd->name[0] == 0)
			exit(0);
		if (builtincheck(ecmd->name))
		{
			builtin(var, ecmd);
			return ;
		}
		else
		{
			// execve(exe_path_set(var, ecmd->name), ecmd->args, var->env.newenv);
			execvp(exe_path_set(var, ecmd->name), ecmd->args);
			// execv(ft_strjoin("/usr/bin/", ecmd->name), ecmd->args);
			// perror("");
			printf("exec %s failed\n", ecmd->name);
		}
	}
	// else if (cmd->type == REDIR)
	// {
	// 	rcmd = cmd->red;
	// 	close(rcmd->fd);
	// 	if (open(rcmd->file, rcmd->mode) < 0){
	// 		printf("open %s failed\n", rcmd->file);
	// 		exit(0);
	// 	}
	// 	runcmd(rcmd->cmd, var);
	// }
	else if (cmd->type == PIPE)
	{
		pcmd = cmd->pip;
		// if (var->idx_fd > 0)
		// {
		// 	if (pipe(var->fd[var->idx_fd]) < 0)
		// 		trouble("pipe");
		// }
		if (fork1() == 0){
			// close(0);
			dup2(var->fd[var->idx_fd][1], 1);
			// close(p[0]);
			runcmd(pcmd->left, var);
			// close(p[1]);
		}
		if (fork1() == 0){
			// close(1);
			dup2(var->fd[var->idx_fd][0], 0);
			// close(p[1]);
			runcmd(pcmd->right, var);
			// close(p[0]);
		}
		// close(p[1]);
		// close(p[0]);
		wait(NULL);
		wait(NULL);
		// while (waitpid(-1, NULL, 0) < 0)
		// {}
		// exit(0);
	}
	else
		trouble("runcmd");
	// exit(0);
}

void	fill_path(t_vars *var)
{
	t_allways aws;

	if (!check_env_var(var, "PATH"))
		trouble("fill_path");
	free1(var->temp);
	var->temp = ft_split(get_env_var(var, "PATH"), ':');
	var->exepath = malloc(sizeof(char *) * (ft_lstlen(var->temp) + 1));
	aws.i = 0;
	while (var->temp[aws.i])
	{
		var->exepath[aws.i] = ft_strjoin(var->temp[aws.i], "/");
		aws.i++;
	}
	var->exepath[aws.i] = NULL;
}

void	initialisation(t_vars *var, char **env)
{
	var->tmp = malloc(sizeof(char));
	var->tmp1 = malloc(sizeof(char));
	var->tmp2 = malloc(sizeof(char));
	var->tmp3 = malloc(sizeof(char));
	var->temp = malloc(sizeof(char *));
	var->temp[0] = NULL;
	var->temp1 = malloc(sizeof(char *));
	var->temp2 = malloc(sizeof(char *));
	var->buff = malloc(sizeof(char));
	var->env.env = env;
	var->cmd = (t_cmd **)malloc(sizeof(t_cmd *) * FILENAME_MAX);
	var->cod = 0;
	init_environment(var);
	init_export(var);
	fill_path(var);
	// hostname(var);
	var->idx_fd = 1;
	for (int i = 0; i <= var->idx_fd; i++)
	{
		pipe(var->fd[var->idx_fd]);
	}
}

void	hostname(t_vars *var)
{
	int	fd;

	fd = open("/proc/sys/kernel/hostname", O_RDONLY);
	ft_export(var, ft_strjoin("HOSTNAME=", 
	ft_split(get_next_line(fd), '\n')[0]), 0);
}

int	main(int ac, char *av[], char **env)
{
	t_vars	*var;
	char	cwd[1024];

	var = malloc(sizeof(t_vars));
	initialisation(var, env);

	/* ft_export(var, "TEST_MINISHELL=0", 1);
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
	printf("%s\n", get_env_var(var, "PATH")); */
	


	/* execv(ecmd->name, ecmd->args);

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
	++var->cod; */
	
	while (1)
	{
		// chdir("..");
		getcwd(cwd, sizeof(cwd));
		free(var->temp);
		var->temp = ft_split(cwd, '/');
		if (ft_lstlen(var->temp) > 0)
			printf("%s$ %s%s@%s %s%s %s|%s", C_GREEN, C_YELOW, get_env_var(var, "USERNAME"), get_env_var(var, "HOSTNAME"), C_CYAN, var->temp[ft_lstlen(var->temp) - 1], C_RED, C_RES);
		else
			printf("%s$ %s%s@%s %s%s %s|%s", C_GREEN, C_YELOW, get_env_var(var, "USERNAME"), get_env_var(var, "HOSTNAME"), C_CYAN, cwd, C_RED, C_RES);
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
}



