#include "minishell.h"

void	iterate(t_final **node)
{
	int	i;
	int	len;
	t_final *n;

	i = 1;
	n = *node;
	len = list_size1(n);
	while (i <= len)
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
}

void	executor(t_vars *var, t_final **node)
{
	iterate(node);
	if (fork1() == 0)
	{
		dup2((*node)->infile, 1);
		execvp(exe_path_set(var, ecmd->name), ecmd->args);
	}
}