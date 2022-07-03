/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:12:21 by anajmi            #+#    #+#             */
/*   Updated: 2022/06/30 21:17:09 by anajmi           ###   ########.fr       */
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

# define C_RES		"\033[0m"
# define C_RED		"\033[1;31m"
# define C_GREEN	"\033[1;32m"
# define C_YELOW	"\033[1;33m"
# define C_BLUE		"\033[1;34m"
# define C_CYAN		"\033[1;36m"

# define EXEC	1
# define REDIR	2
# define PIPE	3
# define BACK	4

# define MAXARG	10


typedef struct s_cmd t_cmd;

typedef struct s_execcmd
{
	int type;
	char name[MAXARG];
	char *args[MAXARG];
}	t_execcmd;

typedef struct s_redircmd
{
	int type;
	t_cmd *cmd;
	char *file;
	char *efile;
	int mode;
	int fd;
}	t_redircmd;

typedef struct s_pipecmd
{
	int type;
	t_cmd *left;
	t_cmd *right;
}	t_pipecmd;

// typedef struct s_cmd
// {
// 	int type;
// 	// void *cmd;
// 	t_execcmd	*exe;
// 	t_pipecmd	*pip;
// 	t_redircmd	*red;
// }	t_cmd;


struct s_cmd
{
	int type;
	// void *cmd;
	t_execcmd	*exe;
	t_pipecmd	*pip;
	t_redircmd	*red;
};

typedef struct s_env
{
	size_t	sizeofexp;
	size_t	sizeofenv;
	char	**env;
	char	**newenv;
	char	***newexp;
}	t_env;

typedef struct	s_allways
{
	size_t	i;
	size_t	j;
	size_t	k;
}	t_allways;

typedef struct	s_vars
{
	int		exit_code;

	// environment
	t_env	env;
	char	*tmp;
	char	*tmp1;
	char	*tmp2;
	char	**temp;
	char	**temp1;
	char	**temp2;
	char	***temp3;

	char	*buff;

	t_cmd	*cmd;
}	t_vars;

void	sort_export(t_vars *var);
void	init_environment(t_vars *var);
void	init_export(t_vars *var);
void	ft_export(t_vars *var, char *to_add, int pass);
void	ft_unset(t_vars *var, char *to_del);
void	show_env(t_vars *var);
void	show_exp(t_vars *var);
char	*get_env_var(t_vars *var, char *to_get);
int		check_env_var(t_vars *var, char *to_check);

#endif
