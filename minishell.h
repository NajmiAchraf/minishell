/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:12:21 by anajmi            #+#    #+#             */
/*   Updated: 2022/06/26 16:35:27 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "Libft/libft.h"
# include "LibftPlus/libftplus.h"

# define TK_SPACE '0'
# define TK_AZ09 '1'
# define TK_PIP '2'
# define TK_RDRT '3'
# define TK_LDRT '4'

# define C_CYAN "\033[1;36m"
# define C_BLUE "\033[1;34m"
# define C_GREEN "\033[1;32m"
# define C_YELOW "\033[1;33m"
# define C_RED "\033[1;31m"
# define C_RES  "\033[0m"

# define EXEC	1
# define REDIR	2
# define PIPE	3
# define BACK	4

# define MAXARGS 10

typedef struct s_execcmd
{
	int type;
	char *argv[MAXARGS];
	char *eargv[MAXARGS];
}	t_cmd;

typedef struct s_env
{
	size_t	sizeofexp;
	size_t	sizeofenv;
	char	**env;
	char	**newenv;
	char	***newexp;
}	t_env;

typedef struct	s_vars
{
	size_t	i;
	size_t	j;
	int		exit_code;

	// environment
	t_env	env;
	char	**temp;

	char	*buff;
	char	*bin;
	char	**piplist;
	char	**cmdlist;
	char	**argslist;
	char	**slist;
}	t_vars;

void	sort_export(t_vars *var);
void	init_environment(t_vars *var);
void	init_export(t_vars *var);
void	ft_export(t_vars *var, char *to_add);
void	ft_unset(t_vars *var, char *to_del);
void	show_env(t_vars *var);
void	show_exp(t_vars *var);
char	*get_env_var(t_vars *var, char *to_get);

#endif
