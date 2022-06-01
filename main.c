/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:12:12 by anajmi            #+#    #+#             */
/*   Updated: 2022/06/01 10:34:18 by anajmi           ###   ########.fr       */
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

size_t	ft_lstlen(char **list)
{
	size_t	len;

	len = 0;
	while (list[len] != '\0')
		len++;
	return (len);
}

void	envirment(t_vars *var, char *to_add)
{
	var->i = 0;
	if (!var->newenv)
	{
		var->newenv = malloc(sizeof(char *) * ft_lstlen(var->env) + 1);
		while (var->env[var->i])
		{
			var->newenv[var->i] = ft_strdup(var->env[var->i]);
			var->i++;
		}
		var->newenv[var->i] = NULL;
	}
	var->tmp = malloc(sizeof(char *) * ft_lstlen(var->newenv) + 2);
	var->j = ft_lstlen(var->newenv);
	var->i = 0;
	while (var->i < var->j)
	{
		var->tmp[var->i] = ft_strdup(var->newenv[var->i]);
		var->i++;
	}
	var->tmp[var->i] = ft_strdup(to_add);
	var->tmp[var->i + 1] = NULL;
	var->i = 0;
	while (var->i < var->j)
	{
		free(var->newenv[var->i]);
		var->i++;
	}
	free(var->newenv);
	var->newenv = var->tmp;
	var->i = 0;
	while (var->i < (var->j + 1))
	{
		printf("%s\n", var->newenv[var->i]);
		var->i++;
	}
}

void	lex(t_vars *var)
{
	if (ft_strchr(var->buff, '|'))
	{
		var->piplist = ft_split(var->buff, '|');
	}
	else
	{
		var->slist = ft_split(var->buff, ' ');
	}
	if (var->piplist)
	{
		int t = 0;
		var->j = ft_lstlen(var->piplist);
		var->tmplist = malloc(sizeof(char ***) * var->j);
		var->i = 0;
		while (var->i < var->j)
		{
			var->tmplist[var->i] = ft_split(var->piplist[var->i], ' ');
			printf("\n---------------------------------------------------------------\n");
			while (t <= ft_lstlen(var->tmplist[var->i]))
			{
				printf("\n%s	i = %zu	j = %zu\n", var->tmplist[var->i][t], var->i, var->j);
				t++;
			}
			var->i++;
		}
	}
}

/*
ls 'ls -la' >a >>a > a
str = ls 'ls -la'"a"'t' | 'ls' >a >>>>a ..a 
str = 0010000000000000010100001201222201000

ls
'ls -la'"a"'t'
|
'ls'
>
a
>>>>
a 
..a

ls
'ls -la'"a"'t'
|
'ls'
>
a
>>>>
a
..a
*/

void	if_equiquot(t_vars *var, int index, char c)
{
	int	i;
	i = ft_strlen(var->buff);
	index++;
	while (var->buff[index])
	{
		if (var->buff[index] == c && var->buff[index + 1] == c)
			index += 2;
		if (var->buff[index] == '|')
			break ;
		else if (var->buff[index] == c)
		{
			while (var->i <= index)
			{
				var->bin[var->i] = TK_AZ09;
				var->i++;
			}
			var->i--;
			return ;
		}
		index++;
	}
	return ;
}

void	tekoniz(t_vars *var)
{
	var->i = 0;
	var->j = 0;
	if (!var->bin)
		free(var->bin);
	var->bin = malloc(sizeof(char) * ft_strlen(var->buff));
	while (var->buff[var->i])
	{
		if (var->buff[var->i] == 34 || var->buff[var->i] == 39) /* " */ /* ' */
			if_equiquot(var, var->i + 1, var->buff[var->i]);
		if (var->buff[var->i] == ' ')
			var->bin[var->i] = TK_SPACE;
		else if (ft_isalpha(var->buff[var->i]) || var->buff[var->i] == '-'
				|| var->buff[var->i] == 34 || var->buff[var->i] == 39)
			var->bin[var->i] = TK_AZ09;
		else if (var->buff[var->i] == '|')
			var->bin[var->i] = TK_PIP;
		else if (var->buff[var->i] == '>')
			var->bin[var->i] = TK_RDRT;
		else if (var->buff[var->i] == '<')
			var->bin[var->i] = TK_LDRT;
		var->i++;
	}
	printf("buff = %s\nbin  = %s\n", var->buff, var->bin);
}

int	main(int ac, char *av[], char **env)
{
	t_vars	*var;
	char	cwd[1024];

	var = malloc(sizeof(t_vars));
	var->buff = NULL;
	var->bin = NULL;
	var->env = env;
	var->newenv = NULL;
	var->piplist = NULL;
	TK_AZ09;
	while (1)
	{
		getcwd(cwd, sizeof(cwd));
		printf("-> %s", cwd);
		var->buff = readline("\n>> ");
		add_history(var->buff);
		printf("%s\n", var->buff);
		// lex(var);
		tekoniz(var);
		// system("leaks minishell");
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
