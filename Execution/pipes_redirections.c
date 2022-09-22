/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:52:36 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/21 23:36:27 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	int			fd[2];

	n = *node;
	while (n)
	{
		file = n->file;
		while (file)
		{
			if (file->id == 1) /* < */
			{
				if (n->infile != -1 && n->infile != 0)
					close(n->infile);
				n->infile = open(file->str, O_RDONLY);
				if (n->infile == -1)
				{
					trouble("open", file->str, "can't open file", 1);
					return ;
				}
			}
			if (file->id == 2) /* > */
			{
				if (n->outfile != -1 && n->outfile != 1)
					close(n->outfile);
				n->outfile = open(file->str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
				if (n->outfile == -1)
				{
					trouble("open", file->str, "can't open file", 1);
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
					trouble("open", file->str, "can't open file", 1);
					return ;
				}
			}
			if (file->id == 4) /* << */
			{
				if (pipe(fd) == -1)
				{
					trouble("pipe", NULL, "can't open heredoc", 1);
					return ;
				}
				if (n->infile != -1 && n->infile != 0)
					close(n->infile);
				n->infile = fd[1];
				ft_putstr_fd(heredoc(var, file->str), n->infile);
				close(n->infile);
				n->infile = fd[0];
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

int	node_close(t_final *node)
{
	if (node->infile != 0)
		return (close(node->infile));
	if (node->outfile != 1)
		return (close(node->outfile));
	return (1);
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

void    duping(t_final *node)
{
    if (node->infile != 0)
    {
        if (dup2(node->infile, 0) == -1)
            trouble_exit("dup2", NULL, "failed", 1);
        close(node->infile);
    }
    if (node->outfile != 1)
    {
        if (dup2(node->outfile, 1) == -1)
            trouble_exit("dup2", NULL, "failed", 1);
        close(node->outfile);
    }
}

/*
void    exec_cmd(t_cmdfinal **cmd_final)
{
    t_var    exec;
    int        i;
    int        status;

    exec.flag = 0;
    exec.child_pids = malloc(sizeof(int) * (*cmd_final)->number_node);
    signal(SIGINT, SIG_IGN);
    ft_cmd(cmd_final, &exec);
    i = 0;
    while (i < (*cmd_final)->number_node)
    {
        waitpid(exec.child_pids[i], &status, 0);
        if (WIFEXITED(status))
            t_global.state = WEXITSTATUS(status);
        if (status == 2)
            t_global.state = 128 + status;
        else if (status == 3)
        {
            printf("Quit: %d\n", status);
            t_global.state = 128 + status;
        }
        i++;
    }
    ret_fork(&exec);
    return ;
}
*/

void	executor(t_vars *var, t_final **node)
{
	t_allways	w;
	t_final		*n;

	w.i = 0;
	w.j = 0;
	w.k = 1;
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
				if (g_status == 1)
					trouble("builtin", n->cmd[0], "failed", 1);
				full_close(node);
			}
			else
			{
    			signal(SIGINT, SIG_IGN);
				var->pid[w.j] = ft_fork();
				if (var->pid[w.j] == 0)
				{
					signal(SIGINT, sig_handler0);
					signal(SIGQUIT, sig_handler0);

					duping(n);
					full_close(node);
					if (!builtincheck(n->cmd[0]))
					{
						n->infile = 0;
						n->outfile = 1;
						g_status = builtin(var, n);
						if (g_status == 1)
							trouble_exit("builtin", n->cmd[0], "failed", 1);
						exit(0);
					}
					execve(exe_path_set(var, n->cmd[0]), n->cmd, var->env.newenv);
					trouble_exit("execve", n->cmd[0], "failed", 1);
				}
				node_close(n);
				w.k = 0;
			}
		}
		// else
		// 	printf("minishell: %s No such file or directory\n", n->cmd[0]);
		n = n->next;
		w.i++;
		w.j++;
	}
				
	if (w.k == 0)
	{
		w.j = 0;
		n = *node;
		while (n)
		{
			waitpid(var->pid[w.j], &w.status, 0);
			if (WIFEXITED(w.status))
				g_status = WEXITSTATUS(w.status);
			if (w.status == 2)
				g_status = 128 + w.status;
			else if (w.status == 3)
			{
				// trouble("Quit: %d\n", w.status);
				printf("Quit: %d\n", w.status);
				g_status = 128 + w.status;
			}
			n = n->next;
			w.j++;
		}
		ft_signals();
	}
}
