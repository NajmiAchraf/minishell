/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:12:12 by anajmi            #+#    #+#             */
/*   Updated: 2022/06/22 17:05:11 by anajmi           ###   ########.fr       */
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
	var->buff = NULL;
	var->bin = NULL;
	var->env = env;
	var->piplist = NULL;
	init_environment(var);
	init_export(var);
}

// void	executing(t_vars *var)
// {
	
// }

int	main(int ac, char *av[], char **env)
{
	t_vars	*var;
	char	cwd[1024];

	var = malloc(sizeof(t_vars));
	// initialisation(var, env);
	while (1)
	{
		chdir("/");

		getcwd(cwd, sizeof(cwd));
		printf("-> %s", cwd);
		var->buff = readline("\n>> ");
		add_history(var->buff);
		printf("%s\n", var->buff);
		system("leaks minishell");
		free(var->buff);
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
