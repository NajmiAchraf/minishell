/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:12:12 by anajmi            #+#    #+#             */
/*   Updated: 2022/07/01 02:15:29 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_in_test(t_vars *var)
{
	/*ls -la | wc -l*/
	
	t_cmd		*cmd;


	var->cmd = (t_cmd*)malloc(sizeof(t_cmd));

	var->cmd->type = EXEC;

	var->cmd->exe = (t_execcmd*)malloc(sizeof(t_execcmd));

	var->cmd->exe->type = EXEC;

	ft_strlcpy(var->cmd->exe->name, "export", 7);

	var->cmd->exe->args[0] = ft_strdup("$USER$USER$USER=trynottry1$USER");
	// var->cmd->exe->args[0] = ft_strdup("ZLL=1$ZLL23$USER");
	var->cmd->exe->args[1] = NULL;
	// ft_strlcpy(var->cmd->pip->left->exe->args[0], "-la", 4);
	// ft_bzero(var->cmd->pip->left->exe->args[1], 1);
}

void	one_pipe_fill_in_test(t_vars *var)
{
	/*ls -la | wc -l*/
	
	t_cmd		*cmd;


	var->cmd = (t_cmd*)malloc(sizeof(t_cmd));
	
	var->cmd->type = PIPE;
	
	var->cmd->pip = (t_pipecmd*)malloc(sizeof(t_pipecmd));
	
	var->cmd->pip->type = PIPE;
	var->cmd->pip->left = (t_cmd*)malloc(sizeof(t_cmd));

	var->cmd->pip->left->type = EXEC;

	var->cmd->pip->left->exe = (t_execcmd*)malloc(sizeof(t_execcmd));

	var->cmd->pip->left->exe->type = EXEC;

	ft_strlcpy(var->cmd->pip->left->exe->name, "ls", 3);

	var->cmd->pip->left->exe->args[0] = ft_strdup("-l");
	var->cmd->pip->left->exe->args[1] = ft_strdup("-s");
	var->cmd->pip->left->exe->args[2] = ft_strdup("-a");
	var->cmd->pip->left->exe->args[3] = NULL;
	// ft_strlcpy(var->cmd->pip->left->exe->args[0], "-la", 4);
	// ft_bzero(var->cmd->pip->left->exe->args[1], 1);

	var->cmd->pip->right = (t_cmd*)malloc(sizeof(t_cmd));
	
	var->cmd->pip->right->type = EXEC;
	
	var->cmd->pip->right->exe = (t_execcmd*)malloc(sizeof(t_execcmd));

	var->cmd->pip->right->exe->type = EXEC;

	ft_strlcpy(var->cmd->pip->right->exe->name, "wc", 3);

	var->cmd->pip->right->exe->args[0] = ft_strdup("-l");
	var->cmd->pip->right->exe->args[1] = NULL;
	// ft_strlcpy(var->cmd->pip->right->pip->right->exe->args[0], "-l", 3);
	// ft_bzero(var->cmd->pip->right->pip->right->exe->args[1], 1);
	// printf("%s\n", var->cmd->pip->right->pip->right->exe->args[0]);
}

void	two_pipes_fill_in_test(t_vars *var)
{
	/*ls -la | grep -r "mini" | wc -l*/
	
	t_cmd		*cmd;


	var->cmd = (t_cmd*)malloc(sizeof(t_cmd));
	
	var->cmd->type = PIPE;
	
	var->cmd->pip = (t_pipecmd*)malloc(sizeof(t_pipecmd));
	
	var->cmd->pip->type = PIPE;
	var->cmd->pip->left = (t_cmd*)malloc(sizeof(t_cmd));

	var->cmd->pip->left->type = EXEC;

	var->cmd->pip->left->exe = (t_execcmd*)malloc(sizeof(t_execcmd));

	var->cmd->pip->left->exe->type = EXEC;

	ft_strlcpy(var->cmd->pip->left->exe->name, "ls", 3);

	var->cmd->pip->left->exe->args[0] = ft_strdup("-la");
	var->cmd->pip->left->exe->args[1] = NULL;
	// ft_strlcpy(var->cmd->pip->left->exe->args[0], "-la", 4);
	// ft_bzero(var->cmd->pip->left->exe->args[1], 1);

	var->cmd->pip->right = (t_cmd*)malloc(sizeof(t_cmd));
	
	var->cmd->pip->right->type = PIPE;
	
	var->cmd->pip->right->pip = (t_pipecmd*)malloc(sizeof(t_pipecmd));

	var->cmd->pip->right->pip->type = PIPE;
	
	var->cmd->pip->right->pip->left = (t_cmd*)malloc(sizeof(t_cmd));
	
	var->cmd->pip->right->pip->left->type = EXEC;
	var->cmd->pip->right->pip->left->exe = (t_execcmd*)malloc(sizeof(t_execcmd));

	var->cmd->pip->right->pip->left->exe->type = EXEC;

	ft_strlcpy(var->cmd->pip->right->pip->left->exe->name, "grep", 5);
	var->cmd->pip->right->pip->left->exe->args[0] = ft_strdup("-r");
	var->cmd->pip->right->pip->left->exe->args[1] = ft_strdup("min");
	var->cmd->pip->right->pip->left->exe->args[2] = NULL;
	// ft_strlcpy(var->cmd->pip->right->pip->left->exe->args[0], "-r", 3);
	// ft_strlcpy(var->cmd->pip->right->pip->left->exe->args[1], "mini", 5);
	// ft_bzero(var->cmd->pip->right->pip->left->exe->args[2], 1);
	
	var->cmd->pip->right->pip->right = (t_cmd*)malloc(sizeof(t_cmd));
	
	var->cmd->pip->right->pip->right->type = EXEC;
	
	var->cmd->pip->right->pip->right->exe = (t_execcmd*)malloc(sizeof(t_execcmd));

	var->cmd->pip->right->pip->right->exe->type = EXEC;

	ft_strlcpy(var->cmd->pip->right->pip->right->exe->name, "wc", 3);

	var->cmd->pip->right->pip->right->exe->args[0] = ft_strdup("-l");
	var->cmd->pip->right->pip->right->exe->args[1] = NULL;
	// ft_strlcpy(var->cmd->pip->right->pip->right->exe->args[0], "-l", 3);
	// ft_bzero(var->cmd->pip->right->pip->right->exe->args[1], 1);
	// printf("%s\n", var->cmd->pip->right->pip->right->exe->args[0]);
}

void	panic(char *s)
{
	printf("%s\n", s);
	exit(0);
}

int	fork1(void)
{
	int pid;

	pid = fork();
	if(pid == -1)
		panic("fork");
	return pid;
}


/*********************/
/* BUILTIN FUNCTIONS */
/*********************/
int	pwd();

char	*dir()
{
	char	cwd[FILENAME_MAX];

	getcwd(cwd, sizeof(cwd));
	return (cwd);
}

int	echo(t_vars *var, t_execcmd *ecmd)
{
	t_allways aws;

	aws.i = 0;
	while (ecmd->args[aws.i])
	{
		if (ecmd->args[aws.i][0] == '$')
		{
			++ecmd->args[aws.i];
			// if (ft_strcmp(get_env_var(var, ecmd->args[aws.i]), ""))
				printf("%s ", get_env_var(var, ecmd->args[aws.i]));
			--ecmd->args[aws.i];
		}
		else
			printf("%s ", ecmd->args[aws.i]);
		aws.i++;
	}
	printf("\n");
	return (1);
}

int	cd(t_vars *var, t_execcmd *ecmd)
{
	if (ft_lstlen(ecmd->args) > 1 && ecmd->args[0][0] != '-')
		printf("minishell: cd: too many arguments\n");
	else if (ecmd->args[0][0] == '-')
		printf("minishell: cd: %s: invalid option\n", ecmd->args[0]);
	else
	{
		if (chdir(ecmd->args[0]))
		{
			printf("minishell: cd: %s: No such file or directory\n", ecmd->args[0]);
			return (0);
		}
		pwd();
		ft_export(var, ft_strjoin("PWD=", dir()), 0);
	}
	return (1);
}

int	pwd()
{
	printf("%s\n", dir());
	return (1);
}

int	export(t_vars *var, t_execcmd *ecmd)
{
	t_allways aws;

	/* 
	export
	export a=1 b c=0
	 */
	if (!ecmd->args[0])
		show_exp(var);
	else
	{
		aws.i = 0;
		while (ecmd->args[aws.i])
		{
			if (ft_isalpha(ecmd->args[aws.i][0]) || ecmd->args[aws.i][0] == '_' || ecmd->args[aws.i][0] == '$')
				ft_export(var, ecmd->args[aws.i], 0);
			else
				printf("bash: export: `%s': not a valid identifier\n", ecmd->args[aws.i]);
			aws.i++;
		}
	}
	show_env(var);
	return (1);
}

int	unset(t_vars *var, t_execcmd *ecmd)
{
	t_allways aws;

	/* 
	unset
	unset a b c
	 */
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
	/* 
	env
	env a b c
	 */
	if (!ecmd->args[0])
		show_env(var);
	else
		printf("env: ‘%s’: No such file or directory\n", ecmd->args[0]);
	return (1);
}


int	builtin(t_vars *var, t_execcmd *ecmd)
{
/* 	◦ echo with option -n
	◦ cd with only a relative or absolute path
	◦ pwd with no options
	◦ export with no options
	◦ unset with no options
	◦ env with no options or arguments
	◦ exit with no options */
	if (!ft_strcmp(ecmd->name , "echo"))
		return (echo(var, ecmd));
	else if (!ft_strcmp(ecmd->name , "cd"))
		return (cd(var, ecmd));
	else if (!ft_strcmp(ecmd->name , "pwd"))
		return (pwd());
	else if (!ft_strcmp(ecmd->name , "export"))
		return (export(var, ecmd));
	else if (!ft_strcmp(ecmd->name , "unset"))
		return (unset(var, ecmd));
	else if (!ft_strcmp(ecmd->name , "env"))
		return (environment(var, ecmd));
	// else if (!ft_strcmp(ecmd->name , "exit"))
	return (0);
}

void	runcmd(t_cmd *cmd, t_vars *var)
{
	int p[2];
	t_execcmd	*ecmd;
	t_pipecmd	*pcmd;
	t_redircmd	*rcmd;

	if(cmd == 0)
		exit(0);
	

	switch(cmd->type){
	default:
		panic("runcmd");

	case EXEC:
		ecmd = cmd->exe;
		size_t i = 0;
		if(ecmd->name[0] == 0)
			exit(0);
		printf("%s ", ecmd->name);
		i = 0;
		while (ecmd->args[i]){
			printf("%s ", ecmd->args[i]);
			i++;
		}
		printf("\n");
		if (builtin(var, ecmd))
			break;
		execve(ft_strjoin("/usr/bin/", ecmd->name), ecmd->args, var->env.newenv);
		// execv(ft_strjoin("/usr/bin/", ecmd->name), ecmd->args);

		printf("exec %s failed\n", ecmd->name);
		break;

	// case REDIR:
	// 	rcmd = cmd->red;
	// 	close(rcmd->fd);
	// 	if(open(rcmd->file, rcmd->mode) < 0){
	// 		printf("open %s failed\n", rcmd->file);
	// 		exit(0);
	// 	}
	// 	runcmd(rcmd->cmd);
	// 	break;

	case PIPE:
		pcmd = cmd->pip;
		if(pipe(p) < 0)
			panic("pipe");
		if(fork1() == 0){
			close(1);
			dup(p[1]);
			close(p[0]);
			close(p[1]);
			runcmd(pcmd->left, var);
		}
		if(fork1() == 0){
			close(0);
			dup(p[0]);
			close(p[0]);
			close(p[1]);
			runcmd(pcmd->right, var);
		}
		close(p[0]);
		close(p[1]);
		wait(0);
		wait(0);
		break;
	}
	exit(0);
}

void	initialisation(t_vars *var, char **env)
{
	var->tmp = malloc(sizeof(char));
	var->tmp1 = malloc(sizeof(char));
	var->tmp2 = malloc(sizeof(char));
	var->temp = malloc(sizeof(char *));
	var->temp1 = malloc(sizeof(char *));
	var->temp2 = malloc(sizeof(char *));
	var->buff = malloc(sizeof(char));
	var->env.env = env;
	init_environment(var);
	init_export(var);
}

int	main(int ac, char *av[], char **env)
{
	t_vars	*var;
	char	cwd[1024];

	var = malloc(sizeof(t_vars));
	initialisation(var, env);


	/* ft_export(var, "TEST_MINISHELL=0");
	ft_export(var, "ENV_EXP_UNST=0");
	ft_export(var, "ENV_EXP_UNST1=0");
	ft_export(var, "ENV_EXP_UNST2=0");
	ft_export(var, "ENV_EXP_UNST3=0");
	ft_export(var, "ENV_EXP_UNST4=0");
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
	printf("--------------------------------------------------------------------4\n"); */


	// execv(ecmd->name, ecmd->args);
	
	fill_in_test(var);
	// one_pipe_fill_in_test(var);
	// two_pipes_fill_in_test(var);
	runcmd(var->cmd, var);
	while (1)
	{
		// chdir("..");

		getcwd(cwd, sizeof(cwd));
		free(var->temp);
		var->temp = ft_split(cwd, '/');
		if (ft_lstlen(var->temp) > 0)
			printf("%s$ %s%s@%s %s%s %s|%s", C_GREEN, C_YELOW, get_env_var(var, "USER"), get_env_var(var, "USERNAME"), C_CYAN, var->temp[ft_lstlen(var->temp) - 1], C_RED, C_RES);
		else
			printf("%s$ %s%s@%s %s%s %s|%s", C_GREEN, C_YELOW, get_env_var(var, "USER"), get_env_var(var, "USERNAME"), C_CYAN, cwd, C_RED, C_RES);
		free(var->buff);
		var->buff = readline("→ ");
		add_history(var->buff);
		printf("%s\n", var->buff);
	}
	return (0);
}

/*
|fgsfgdsf -la || >> asd| error
sdfg | sfgs  | dfgsd | dsaf

ssf -la "dsfsd" >>> a >b

>> << > <
 => ls "adsfsdf
 => ls ''' '
"ls ''' '
>> word
>> $dfgxdf
[ssf$tt, -la, "asdfsd", >>>, a, >, b]

ssf '-la' "asdfsd" >> a >b

synatx valid
[ssf$tt, -la, "asdfsd", >>, a, >, b]
[ssfvalue_of_tt, -la, "asdfsd", >>, a, >, b]
or
[>, e, ssf, -la, "asdfsd", >>, a, >, b, << t]

----------------------------
command ssf
list args [-la, "asdfasd"]
list files [e : output, a : append, b : output, t : herdoc]
----------------------------
command ssxcvf
list args [-la, "asdfasd"]
fd [0, b : 3]

--------------------
signals
--------------------
$sdfs -> sdf
<< not expand when encounter single quot or double quot
int main(int ac, char **av, char **env)
*/

