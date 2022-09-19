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
void	clear_fd(char *to_clear, int fd)
{
	size_t	i;

	i = 0;
	// if (!to_clear[i])
	// 	return ;
	while (to_clear[i])
	{
		ft_putchar_fd('\b', fd);
		i++;
	}
	
}
char	*heredoc(t_vars *var, char *delimiter)
{
	int	i;

	i = 0;
	while (1)
	{
		var->line = readline("> ");
		if (!ft_strcmp(var->line, delimiter))
			break ;
		free(var->tmp);
		var->tmp = var->hdocs;
		if (i == 0)
			var->hdocs = ft_strjoin(var->line, "\n");
		else
			var->hdocs = ft_strjoin(var->hdocs, ft_strjoin(var->line, "\n"));
		free(var->line);
		i++;
	}
	return (ft_strdup(var->hdocs));


/* 	char *fd = ".vscode";
	struct stat *buf;

	buf = malloc(sizeof(struct stat));

	stat(fd, buf);
	stat(fd, ENOTDIR);
	// int size = buf->st_size;
	int size = buf->st_flags;
	
	printf("\n\n\n\nsize ==> %d\n\n\n\n",size);

	free(buf); */
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

int	iterate_pipes(t_final **node)
{
	t_allways	w;
	t_final		*n;

	w.i = 1;
	n = *node;
	w.len = list_size1(n);
	while (n)
	{
		int	p[2];

		pipe(p);
		if (w.i == 1)
			n->infile = 0;

		if (n->outfile == -1)
			n->outfile = p[1];

		if (w.i < w.len)
		{
			if (n->next->infile == -1)
				n->next->infile = p[0];
		}

		if (w.i == w.len)
			n->outfile = 1;
		n = n->next;
		w.i++;
	}
	return (w.len);
}

void	iterate_files(t_vars *var, t_final **node)
{
	t_file		*file;
	t_final		*n;
	t_allways	aws;

	n = *node;
	while (n)
	{
		file = n->file;
		aws.save_in = n->infile;
		while (file)
		{
			if (file->id == 1) /* < */
			{
				if (n->infile != -1 && n->infile != 0) // redirection to folder
					close(n->infile);
				n->infile = open(file->str, O_RDONLY);
				if (n->infile == -1)
					return ;
			}
			if (file->id == 2) /* > */
			{
				if (n->outfile != -1 && n->outfile != 1)
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
				if (n->outfile != -1 && n->outfile != 1)
					close(n->outfile);
				n->outfile = open(file->str, O_WRONLY | O_CREAT | O_APPEND, 0666);
				if (n->outfile == -1)
				{
					printf("minishell: can't open %s file\n", file->str); // Fix later
					return ;
				}
			}
			if (file->id == 4) /* << */
			{
				int fd[2];
				pipe(fd);
				if (n->infile != -1 && n->infile != 0) // redirection to folder
					close(n->infile);
				n->infile = fd[0];
				// clear_fd(var->hdocs, n->infile);
				ft_putstr_fd(heredoc(var, file->str), n->infile);
				close(n->infile);
				n->infile = fd[1];
			}
			file = file->next;
		}
		n = n->next;
	}
}

void	sig_handler0(int sig){
	if (sig == SIGQUIT)
	{
		g_status = 131;
		printf("QUIT : 3\n");
		exit(EXIT_SUCCESS);
	}
	else if (sig == SIGINT)
		printf("FORK\n");
}

void	sig_handler1(int sig)
{
	if (sig == SIGQUIT || sig == SIGINT)
	{
		printf("QUIT : FORK\n");
		exit(EXIT_SUCCESS);
	}
}

void	node_close(t_final *node)
{
	if (node->infile != 0)
		close(node->infile);
	if (node->outfile != 1)
		close(node->outfile);
}

void	full_close(t_final **node)
{
	t_final		*n;

	n = *node;
	while (n)
	{
		node_close(n);
		n = n->next;
	}
}

int    duping(t_final *node)
{
    if (node->infile != 0)
    {
        if (dup2(node->infile, 0) == -1)
            return (1);
        close(node->infile);
    }
    if (node->outfile != 1)
    {
        if (dup2(node->outfile, 1) == -1)
            return (1);
        close(node->outfile);
    }
    return (0);
}

void	executor(t_vars *var, t_final **node)
{
	t_allways	w;
	t_final		*n;
	// t_final		*start;

	w.i = 0;
	n = *node;
	w.len = iterate_pipes(node);
	iterate_files(var, node);
	while (n)
	{
		if (n->cmd[0])
		{
			if (w.len == 1 && !builtincheck(n->cmd[0]))
			{
				g_status = builtin(var, n);
				full_close(node);
			}
			else
			{
				// signal(SIGQUIT, SIG_DFL);
				// signal(SIGINT, SIG_DFL);
				// signal(SIGQUIT, sig_handler0);
				// signal(SIGINT, sig_handler1);
				if (fork1() == 0)
				{
					signal(SIGINT, SIG_DFL);
					signal(SIGQUIT, SIG_DFL);
					signal(SIGINT, sig_handler0);
					signal(SIGQUIT, sig_handler0);

					if (duping(n))
						return ;
					full_close(node);
					if (!builtincheck(n->cmd[0]))
					{
						n->infile = 0;
						n->outfile = 1;
						g_status = builtin(var, n);
						exit(0);
					}
					g_status = execve(exe_path_set(var, n->cmd[0]), n->cmd, var->env.newenv);
					printf("minishell: execve: %s failed\n", n->cmd[0]);
					exit(1);
				}
				// signal(SIGINT, SIG_DFL);
				// ft_signals();
				node_close(n);
				if (w.i == w.len - 1)
					while (wait(NULL) > 0);
			}
		}
		else
			printf("minishell: execve: %s No such file or directory\n", n->cmd[0]);
		n = n->next;
		w.i++;
	}
}
