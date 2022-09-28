/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 11:15:08 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/28 19:24:26 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	panic(void)
{
	ft_putendl_fd("exit", 1);
	exit(0);
}

static void	minishell(t_vars *var, t_save *save)
{
	t_token	*data;
	t_final	*final_data;

	var->line = readline("minishell→ ");
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
				final_data = ft_parser(data);
				executor(var, &final_data);
				free_parser(final_data);
			}
			free_tokens(data);
		}
		else
			trouble(NULL, NULL, "syntax error", 258);	
	}
	free(var->line);
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
	ft_signals();
	while (1)
	{
		minishell(var, save);
		// var->line = readline("minishell→ ");
		// ft_signals();
		// if (!var->line) 
		// {
		// 	ft_putendl_fd("exit", 1);
		// 	exit(0);
		// }
		// if (var->line[0] != '\0')
		// {
		// 	add_history(var->line);
		// 	if (syntax_error(var->line) == 1)
		// 	{
		// 		data = tokenizer(var->line, save);
		// 		if (data && save->error == 0)
		// 		{
		// 			final_data = ft_parser(data);
		// 			executor(var, &final_data);
		// 			free_parser(final_data);
		// 		}
		// 		free_tokens(data);
		// 	}
		// 	else
		// 		trouble(NULL, NULL, "syntax error", 258);	
		// }
		// free(var->line);
	}
}

