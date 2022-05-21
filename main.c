/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:12:12 by anajmi            #+#    #+#             */
/*   Updated: 2022/05/21 16:01:10 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>

/*********************/
/* BUILTIN FUNCTIONS */
/*********************/

int	echo(char *str, int nl)
{
	if (nl)
		return (printf("%s", str));
	return (printf("%s\n", str));
}

void	pwd()
{
	char	cwd[FILENAME_MAX];

	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
}

void	envirment(char **env)
{
	int	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

int	main(int ac, char *av[], char **env)
{
	char	cwd[1024];
	char	*buf;

	envirment(env);
	while (1)
	{
		getcwd(cwd, sizeof(cwd));
		printf("-> %s", cwd);
		buf = readline("\n>> ");
		printf("%s\n", buf);
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
