/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterate_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:41:54 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/25 16:42:13 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	heredoc_pipe(t_vars *var, t_file *file)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (trouble("pipe", NULL, "can't open heredoc", 1));
	if (var->infile != -1 && var->infile != 0)
		close(var->infile);
	heredoc(var, file->str, fd);
	close(fd[1]);
	var->infile = fd[0];
	if (g_status == 1)
		return (1);
	return (0);
}

int	iterate_heredoc(t_vars *var, t_final **node)
{
	t_file		*file;
	t_final		*n;

	n = *node;
	var->h = 0;
	while (n)
	{
		file = (n)->file;
		while (file)
		{
			if (file->id == 4)
			{
				var->h++;
				if (heredoc_pipe(var, file))
					return (1);
			}
			file = file->next;
		}
		n = (n)->next;
	}
	return (0);
}
