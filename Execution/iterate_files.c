/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterate_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:52:36 by anajmi            #+#    #+#             */
/*   Updated: 2022/10/04 11:27:29 by anajmi           ###   ########.fr       */
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

static int	heredoc_file(t_final **node)
{
	if ((*node)->infile != -1 && (*node)->infile != 0)
		close((*node)->infile);
	(*node)->infile = (*node)->herein;
	return (0);
}

int	iterate_files(t_final **node)
{
	t_allways	a;
	t_file		*file;
	t_final		*n;

	n = *node;
	while (n)
	{
		file = (n)->file;
		a.h = 0;
		while (file)
		{
			if (file->id == 1 && read_file(&n, file))
				return (1);
			if (file->id == 2 && trunc_file(&n, file))
				return (1);
			if (file->id == 3 && append_file(&n, file))
				return (1);
			if (file->id == 4 && ++a.h == n->h)
				heredoc_file(&n);
			file = file->next;
		}
		n = (n)->next;
	}
	return (0);
}
