/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 11:15:08 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/11 16:45:01 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int	main(int ac, char *av[], char **env)
{
	t_vars	*var;
	char	cwd[1024];

	var = malloc(sizeof(t_vars));
	initialisation(var, env);
	
	while (1)
	{
		getcwd(cwd, sizeof(cwd));
		free(var->temp);
		var->temp = ft_split(cwd, '/');
		if (ft_lstlen(var->temp) > 0)
			printf("%s$ %s%s@%s %s%s %s|%s", C_GREEN, C_YELOW, get_env_var(var, "USER"), get_env_var(var, "HOSTNAME"), C_CYAN, var->temp[ft_lstlen(var->temp) - 1], C_RED, C_RES);
		else
			printf("%s$ %s%s@%s %s%s %s|%s", C_GREEN, C_YELOW, get_env_var(var, "USER"), get_env_var(var, "HOSTNAME"), C_CYAN, cwd, C_RED, C_RES);
		free(var->buff);
		var->buff = readline("→ ");
		add_history(var->buff);
		// printf("%s\n", var->buff);
	
		system("leaks minishell");
		
		runcmd(var->cmd[var->cod], var);
		++var->cod;
	}
	return (0);
} */


int	main(int ac, char **av, char **env)
{
	char	*line;
	t_vars	*var;
	t_token	*data;
	t_env	*fst_link;
	t_final *final_data;
	
	int id ;
	id = 1;
	if (ac > 1)
		return (0);
	var = malloc(sizeof(t_vars));
	initialisation(var, env);
	fst_link = setting_env(env);
	fst_link->env_var = var;
	while (1)
	{
		ft_signals();
		line = readline("minishell→ ");
		if (!line) 
		{
			printf("exit");
			exit(0); //control_D
		}
		if (line[0] != '\0') //for skipping \n
		{
			add_history(line);
			if (syntax_error(line) != 0)
			{
				/* echo "|" // | ls // ls | // syntax test directly // $USER segv // "./execution" //  */ 
				/*
					minishell→ export A
					minishell→ $A
					AddressSanitizer:DEADLYSIGNAL
				*/
				data = tokenizer(line, av, fst_link);
				// while (data != NULL)
				// {
				// 	printf("word1 = %s, id = %d\n", data->str, data->id);
				// 	data = data->next;

				// var->final = final_data;	
				final_data = ft_parser(data);
				//iterate(&final_data);
				executor(var, &final_data);
				//ft_output(final_data);
				//printf("len ==> \n\n\n");

				//printf("end output \n");
				// printf("before parser %s\n", data->str);
				//@final_data = ft_parser(data);
				// parser (&data);
				// // // printf("output %s\n", data->str);
				//@ft_output(final_data);
				//*printf("data ===== %s\n", data->str);
				free_tokens(data); //holaaa
				//data = NULL;
				// ft_freeparser(final_data);
				//execution;
				free(line);
				//system("leaks minishell");
					// }
			}
			else
				printf("minishell: syntax error\n");
		}
	}
}

