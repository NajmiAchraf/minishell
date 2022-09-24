/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 11:15:08 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/24 17:41:49 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_vars	*var;
	t_token	*data;
	t_env	*fst_link;
	t_final *final_data;
	
	int id ;
	id = 1;
	if (ac > 1)
		return (0);
	var = malloc(sizeof(t_vars));
	initialisation(var, av, env);
	fst_link = setting_env(env);
	fst_link->env_var = var;
	ft_signals();
	while (1)
	{
		var->line = readline("minishell→ ");
		ft_signals();
		if (!var->line) 
		{
			ft_putendl_fd("exit", 1);
			exit(0); //control_D
		}
		if (var->line[0] != '\0') //for skipping \n
		{
			/*
			cat <<'$p'
			echo "'$USER'"

			sleep 1 || ls
			sleep 1 | | ls
			
			*/
			if (syntax_error(var->line) != 0)
			{
				add_history(var->line);
				data = tokenizer(var->line, av, fst_link);
				// while (data != NULL)
				// {
				// 	printf("word1 = %s, id = %d\n", data->str, data->id);
				// 	data = data->next;
				// }
				final_data = ft_parser(data);
				//iterate(&final_data);
				// heredoc(var, final_data);
				executor(var, &final_data);
				// parser (&data);
				// // // printf("output %s\n", data->str);
				//@ft_output(final_data);
				//*printf("data ===== %s\n", data->str);
				free_tokens(data); //holaaa
				// ft_freeparser(final_data);
				free(var->line);
				// system("leaks minishell");
				// }
			}
			else
				trouble(NULL, NULL, "syntax error", 258);
		}
	}
}

