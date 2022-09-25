/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:46:31 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/25 15:39:24 by anajmi           ###   ########.fr       */
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
		var->gnl = readline("> ");
		if (var->gnl == NULL || !ft_strcmp(var->gnl, delimiter))
			break ;
		free(var->tmp0);
		var->tmp0 = var->hdocs;
		if (i == 0)
			var->hdocs = ft_strjoin(heredoc_expand(var, var->gnl), "\n");
		else
			var->hdocs = ft_strjoin(var->hdocs,
					ft_strjoin(heredoc_expand(var, var->gnl), "\n"));
		free(var->gnl);
		i++;
	}
	return (ft_strdup(var->hdocs));
}

void	wait_exit(t_allways w)
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
	wait_exit(w);
	ft_signals();
}
