/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:12:12 by anajmi            #+#    #+#             */
/*   Updated: 2022/06/26 14:10:11 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*********************/
/* BUILTIN FUNCTIONS */
/*********************/

void	pwd()
{
	char	cwd[FILENAME_MAX];

	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
}

void	initialisation(t_vars *var, char **env)
{
	var->temp = malloc(sizeof(char *));
	var->buff = malloc(sizeof(char));
	var->bin = NULL;
	var->env.env = env;
	var->piplist = NULL;
	init_environment(var);
	init_export(var);
}

void	executing(t_vars *var)
{
	if 
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

	int fd;

	// Ensure that three file descriptors are open.
	while((fd = open("console", O_RDWR)) >= 0){
		if(fd >= 3){
			close(fd);
			break;
		}
	}
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
		if(fork1() == 0)
			runcmd(parsecmd(var->buff));
		wait(NULL);
	}
	exit(0);
	return (0);
}
