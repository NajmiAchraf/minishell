/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterate_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:52:36 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/23 20:37:42 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	read_file(t_final **node, t_file *file)
{
	if ((*node)->infile != -1 && (*node)->infile != 0)
		close((*node)->infile);
	(*node)->infile = open(file->str, O_RDONLY);
	if ((*node)->infile == -1)
		return (trouble("open", file->str, "can't open file", 1));
	return (0);
}

static int	trunc_file(t_final **node, t_file *file)
{
	if ((*node)->outfile != -1 && (*node)->outfile != 1)
		close((*node)->outfile);
	(*node)->outfile = open(file->str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if ((*node)->outfile == -1)
		return (trouble("open", file->str, "can't open file", 1));
	return (0);
}

static int	append_file(t_final **node, t_file *file)
{
	if ((*node)->outfile != -1 && (*node)->outfile != 1)
		close((*node)->outfile);
	(*node)->outfile = open(file->str, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if ((*node)->outfile == -1)
		return (trouble("open", file->str, "can't open file", 1));
	return (0);
}

static int	heredoc_pipe(t_vars *var, t_final **node, t_file *file)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (trouble("pipe", NULL, "can't open heredoc", 1));
	if ((*node)->infile != -1 && (*node)->infile != 0)
		close((*node)->infile);
	heredoc(var, file->str, fd);
	close(fd[1]);
	(*node)->infile = fd[0];
	if (g_status == 1)
		return (1);
	return (0);
}

void	iterate_files(t_vars *var, t_final **n)
{
	t_file		*file;

	while (*n)
	{
		file = (*n)->file;
		while (file)
		{
			if (file->id == 1 && read_file(n, file))
				return ;
			if (file->id == 2 && trunc_file(n, file))
				return ;
			if (file->id == 3 && append_file(n, file))
				return ;
			if (file->id == 4 && heredoc_pipe(var, n, file))
				return ;
			file = file->next;
		}
		n = &(*n)->next;
	}
}
