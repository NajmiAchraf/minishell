/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 11:15:08 by anajmi            #+#    #+#             */
/*   Updated: 2022/10/06 16:05:10 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_status = 0;

static void	panic(void)
{
	ft_putendl_fd("exit", 1);
	exit(0);
}

void	hostname(t_vars *var)
{
	int	fd;

	fd = open("/proc/sys/kernel/hostname", O_RDONLY);
	ft_export(var, ft_strjoin("HOSTNAME=",
			ft_split(get_next_line(fd), '\n')[0]), 0);
}

static void	prompt(t_vars *var)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	ft_free(var->tmpp);
	var->tmpp = ft_split(cwd, '/');
	if (ft_lstlen(var->tmpp) > 0)
	{
		printf("%s$ %s%s@%s %s%s %s|%s", C_GREEN, C_YELOW,
			get_env_var(var, "USER"), get_env_var(var, "HOSTNAME"),
			C_CYAN, var->tmpp[ft_lstlen(var->tmpp) - 1], C_RED, C_RES);
	}
	else
	{
		printf("%s$ %s%s@%s %s%s %s|%s", C_GREEN, C_YELOW,
			get_env_var(var, "USER"), get_env_var(var, "HOSTNAME"),
			C_CYAN, cwd, C_RED, C_RES);
	}
	var->line = readline("→ ");
}

static void	minishell(t_vars *var, t_save *save)
{
	t_token	*data;
	t_final	*final_data;

	prompt(var);
	ft_signals();
	if (!var->line)
		panic();
	if (var->line[0] != '\0')
	{
		add_history(var->line);
		if (syntax_error(var->line) == 1)
		{
			data = tokenizer(var->line, save);
			if (data && save->error == 0)
			{
				final_data = ft_parser(data, save);
				if (save->error == 0)
					executor(var, &final_data);
				free_parser(final_data);
			}
			free_tokens(data);
		}
		else
			trouble(NULL, NULL, "syntax error", 258);
	}
}

int	main(int ac, char **av, char **env)
{
	t_vars	*var;
	t_env	*fst_link;
	t_save	*save;

	if (ac > 1)
		return (0);
	var = malloc(sizeof(t_vars));
	initialisation(var, av, env);
	fst_link = setting_env(env);
	fst_link->env_var = var;
	save = (t_save *)malloc(sizeof(t_save));
	save->av = av;
	save->env = fst_link;
	save->error = 0;
	ft_signals();
	while (1)
	{
		minishell(var, save);
		free(var->line);
	}
}
