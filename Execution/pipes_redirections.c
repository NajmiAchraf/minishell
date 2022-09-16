/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:52:36 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/12 13:52:37 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
bash-3.2$ << lim |
> hqw
> hqwq
> hqwhqwhqwh
> lim
> |
bash: syntax error near unexpected token `|'
bash-3.2$ << lim >
> hqw
> hqwwq
> lim
bash: syntax error near unexpected token `newline'
bash-3.2$ cat <<a<<b<<c
> hqw
> hqw
> hqwh
> a
> hqwh
> qwhqwh
> b
> hqw
> hqwhwq
> c
hqw
hqwhwq
bash-3.2$ cat <<a << b | <<salam | echo haha << lbs
> hw
> hqw
> hqwhqw
> a
> hqwh
> qw
> hqwhqw
> hqw
> hqwh
> b
> hwq
> qwhq
> whqwh
> salam
> hwqh
> qhwqhqwh
> lbs
haha
bash-3.2$ cat <<a <<b echo << c
> hqw
> hqwhqwh
> a
> hqwh
> qwhqw
> b
> hqwh
> qhwqwhqwh
> c
cat: echo: No such file or directory
bash-3.2$ 
*/

int	heredoc(t_vars *var, t_final *final)
{
	free(var->end);
	var->end = ft_strdup(var->line);
	while (1)
	{
		free(var->line);
		var->line = readline("> ");
		add_history(var->line);
	}
	
}

int	list_size1(t_final *list)
{
	t_final	*tmp;
	int	i;
	
	if (!list)
		return (0);
	i = 1;
	tmp = list;
	while(tmp->next)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	iterate(t_final **node)
{
	int		i;
	int		len;
	t_final	*n;

	i = 1;
	n = *node;
	len = list_size1(n);
	while (n)
	{
		int	p[2];

		pipe(p);
		if (i == 1)
			(n)->infile = 0;

		if ((n)->outfile == -1)
			(n)->outfile = p[1];

		if (i < len)
		{
			if ((n)->next->infile == -1)
				(n)->next->infile = p[0];
		}
		if (i == len)
			(n)->outfile = 1;
		n = n->next;
		i++;
	}
	return (len);
}

void	iterate_file(t_final **node)
{
	t_file		*file;
	t_final		*n;

	n = *node;
	while (n)
	{
		file = n->file;
		while (file)
		{
			if (file->id == 1) /* < */
			{
				if (n->infile != -1) // to close and dup before
					close(n->infile);
				n->infile = open(file->str, O_RDONLY);
				if (n->infile == -1)
					return ;
			}
			if (file->id == 2) /* > */
			{
				if (n->outfile != -1) // to close and dup before
					close(n->outfile);
				n->outfile = open(file->str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
				if (n->outfile == -1)
				{
					printf("minishell: can't open %s file\n", file->str); // Fix later
					return ;
				}
			}
			if (file->id == 3) /* >> */
			{
				if (n->outfile != -1) // to close and dup before
					close(n->outfile);
				n->outfile = open(file->str, O_WRONLY | O_CREAT | O_APPEND, 0666);
				if (n->outfile == -1)
				{
					printf("minishell: can't open %s file\n", file->str); // Fix later
					return ;
				}
			}
			file = file->next;
		}
		n = n->next;
	}
}

void	executor(t_vars *var, t_final **n)
{
	int		len;
	t_final	*node;
	t_final	*start;
	int		i;

	i = 0;
	node = *n;
	len = iterate(n);
	iterate_file(n);
	while (node)
	{
		if (node->cmd[0])
		{
			if (len == 1 && !builtincheck((node)->cmd[0]))
				g_status = builtin(var, node);
			else
			{
				if (fork1() == 0)
				{
					start = *n;
					dup2((node)->infile, 0);
					dup2((node)->outfile, 1);
					while (start)
					{
						if ((start)->infile != 0)
							close((start)->infile);
						if ((start)->outfile != 1)
							close((start)->outfile);
						start = start->next;
					}

					if (!builtincheck((node)->cmd[0]))
					{
						g_status = builtin(var, node);
						exit(0);
					}
					g_status = execve(exe_path_set(var, (node)->cmd[0]), (node)->cmd, var->env.newenv);
					printf("minishell: execve: %s failed\n", (node)->cmd[0]);
					exit(1);
				}
				if ((node)->infile != 0)
					close((node)->infile);
				if ((node)->outfile != 1)
					close((node)->outfile);
				if (i == len - 1)
					while (wait(NULL) > 0);
			}
		}
		else
			printf("minishell: execve: %s bash: ls: No such file or directory\n", (node)->cmd[0]);
		node = (node)->next;
		i++;
	}
}
