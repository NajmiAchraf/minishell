/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:52:36 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/23 15:35:21 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*var_into_heredoc(t_vars *var, char *to_check, t_allways aws)
{
	free(var->tmp1);
	var->tmp1 = ft_substr(to_check, 0, aws.i);
	free(var->tmp);
	var->tmp = ft_substr(to_check, aws.i + 1, aws.k - aws.i - 1);
	free(var->tmp2);
	var->tmp2 = ft_substr(to_check, aws.k, ft_strlen(to_check));
	if (!get_env_var(var, var->tmp))
		return (ft_strjoin(var->tmp1, var->tmp2));
	return (heredoc_expand(var,
			ft_strjoin(ft_strjoin(var->tmp1,
					get_env_var(var, var->tmp)), var->tmp2)));
}

char	*heredoc_expand(t_vars *var, char *to_search)
{
	t_allways	aws;

	aws.i = -1;
	while (to_search[++aws.i])
	{
		if (to_search[aws.i] == '$')
		{
			aws.k = aws.i;
			while (to_search[++aws.k])
			{
				free(var->tmp);
				var->tmp = ft_substr(to_search, aws.i + 1, aws.k - aws.i - 1);
				if (!(check_env_var(var, var->tmp) || to_search[aws.k] == '_'
						|| ft_isalpha(to_search[aws.k])))
					break ;
			}
			return (var_into_heredoc(var, to_search, aws));
		}
	}
	return (to_search);
}

char	*heredoc_core(t_vars *var, char *delimiter)
{
	int	i;

	free(var->hdocs);
	var->hdocs = ft_strdup("");
	i = 0;
	while (1)
	{
		var->line = readline("> ");
		if (var->line == NULL || !ft_strcmp(var->line, delimiter))
			break ;
		free(var->tmp0);
		var->tmp0 = var->hdocs;
		if (i == 0)
			var->hdocs = ft_strjoin(heredoc_expand(var, var->line), "\n");
		else
			var->hdocs = ft_strjoin(var->hdocs,
					ft_strjoin(heredoc_expand(var, var->line), "\n"));
		free(var->line);
		i++;
	}
	return (ft_strdup(var->hdocs));
}

void	wait_exit(t_vars *var, t_allways w)
{
	if (w.status == 2)
		g_status = 1;
	else if (w.status == 0)
		g_status = 0;
}

void	heredoc(t_vars *var, char *delimiter, int *fd)
{
	t_allways	w;
	pid_t		pid;

	signal(SIGINT, SIG_IGN);
	pid = ft_fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(fd[0]);
		ft_putstr_fd(heredoc_core(var, delimiter), fd[1]);
		close(fd[1]);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &w.status, 0);
	wait_exit(var, w);
	ft_signals();
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
				heredoc(var, file->str, fd);
				close(fd[1]);
				n->infile = fd[0];
				if (g_status == 1)
					return ;
			}
			file = file->next;
		}
		n = n->next;
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

void	wait_status(t_vars *var, t_allways w)
{
	waitpid(var->pid[w.j], &w.status, 0);
	if (WIFEXITED(w.status))
		g_status = WEXITSTATUS(w.status);
	if (w.status == 2)
		g_status = 128 + w.status;
	else if (w.status == 3)
	{
		printf("Quit: %d\n", w.status);
		g_status = 128 + w.status;
	}
}

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
			else if (w.len <= 200)
			{
    			signal(SIGINT, SIG_IGN);
				var->pid[w.j] = ft_fork();
				if (var->pid[w.j] == 0)
				{
					signal(SIGINT, SIG_DFL);
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
				else if (var->pid[w.j] == -1)
					return ;
				node_close(n);
				w.k = 0;
			}
			else
			{
				trouble("fork", NULL, "Resource temporarily unavailable", 1);
				return ;
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
			wait_status(var, w);
			n = n->next;
			w.j++;
		}
		ft_signals();
	}
}
