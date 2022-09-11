#include "../minishell.h"

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

void	executor(char **env, t_final **n)
{
	int		len;
	t_final	*node;
	t_final	*start;
	int		i;

	i = 0;
	node = *n;
	len = iterate(n);
	while (node)
	{
		int pid = fork();
		if (pid == 0)
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
			execve((node)->cmd[0], (node)->cmd, env);
			exit(1);
		}
		if ((node)->infile != 0)
			close((node)->infile);
		if ((node)->outfile != 1)
			close((node)->outfile);
		if (i == len - 1)
			while (wait(NULL) > 0);
		node = (node)->next;
		i++;
	}
}
