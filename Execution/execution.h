/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:12:21 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/11 16:42:12 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>

# define C_RES		"\033[0m"
# define C_RED		"\033[1;31m"
# define C_GREEN	"\033[1;32m"
# define C_YELOW	"\033[1;33m"
# define C_BLUE		"\033[1;34m"
# define C_CYAN		"\033[1;36m"

// # define EXEC	1
// # define REDIR	2
// # define PIPE	3

# define MAXARG	10


/* typedef struct s_cmd t_cmd;

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

struct s_cmd
{
	int type;
	t_execcmd	*exe;
	t_pipecmd	*pip;
	t_redircmd	*red;
}; */

typedef struct s_envp
{
	size_t	sizeofexp;
	size_t	sizeofenv;
	char	**env;
	char	**newenv;
	char	***newexp;
}	t_envp;

typedef struct	s_allways
{
	size_t	i;
	size_t	j;
	size_t	k;
	int		e;
}	t_allways;

typedef struct	s_vars
{
	int		exit_code;

	/* environment */
	t_envp	env;
	char	*tmp;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	**temp;
	char	**temp1;
	char	**temp2;
	char	***temp3;

	char	**exepath;
	char	*tilde;
	char	*buff;
	// t_cmd	**cmd;
	size_t	cod;
}	t_vars;

/* ************************************************************************** */
/*								MAIN FUNCTIONS								  */
/* ************************************************************************** */

void	trouble(char *s);
int		fork1(void);
void	free1(char **tofree);

void	fill_path(t_vars *var);
void	initialisation(t_vars *var, char **env);
void	hostname(t_vars *var);

/* ************************************************************************** */
/*								BUILTIN FUNCTIONS							  */
/* ************************************************************************** */

int		builtin(t_vars *var, t_final *final);

int		echo(t_vars *var, t_final *fianl);
int		cd(t_vars *var, t_final *fianl);
int		pwd(t_vars *var);
int		export(t_vars *var, t_final *fianl);
int		unset(t_vars *var, t_final *fianl);
int		environment(t_vars *var, t_final *fianl);

int		builtincheck(char *name);
int		builtin(t_vars *var, t_final *fianl);

char	*exe_path_set(t_vars *var, char *exe);
void	executor(t_vars *var, t_final **n);
int		list_size1(t_final *list);
int		iterate(t_final **node);

/* ******************** */
/*		DIRECTORY		*/
/* ******************** */

char	*dir();

/* ******************** */
/*		ENVIRONMENT		*/
/* ******************** */

void	free1(char **tofree);
int		replace_variable(t_vars *var, char *to_check, char *value);
int		var_into_var(t_vars *var, char **to_check, t_allways aws);
int		name_into_var(t_vars *var, char **to_check, t_allways aws);
int		outside_search_variable(t_vars *var, char *to_search, char *variable);
int		inside_search_variable(t_vars *var, char *to_search, int gen);
int		little_checker(char *to_check);
int		validate_variable(t_vars *var, char *to_check);

void	sort_export(t_vars *var);
void	init_environment(t_vars *var);
void	init_export(t_vars *var);
void	ft_export(t_vars *var, char *to_add, int pass);
void	export_add(t_vars *var, char *to_add);
void	ft_unset(t_vars *var, char *to_del);
void	show_env(t_vars *var);
void	show_exp(t_vars *var);
char	*get_env_var(t_vars *var, char *to_get);
int		check_env_var(t_vars *var, char *to_check);

#endif
