/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:12:21 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/23 18:02:25 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>

# define C_RES		"\033[0m"
# define C_RED		"\033[1;31m"
# define C_GREEN	"\033[1;32m"
# define C_YELOW	"\033[1;33m"
# define C_BLUE		"\033[1;34m"
# define C_CYAN		"\033[1;36m"

typedef struct s_envp
{
	size_t	sizeofexp;
	size_t	sizeofenv;
	char	**env;
	char	**newenv;
	char	***newexp;
}	t_envp;

typedef struct s_allways
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	len;
	pid_t	pid;
	int		status;
}	t_allways;

typedef struct s_vars
{
	char	*hdocs;

	t_envp	env;
	char	*tmp;
	char	*tmp0;
	char	*tmp1;
	char	*tmp2;
	char	**tmpp;

	char	*main_name;
	char	**exepath;
	int		*pid;
	char	*line;
}	t_vars;

/* ************************************************************************** */
/*								MAIN FUNCTIONS								  */
/* ************************************************************************** */

int		trouble(char *cmd, char *arg, char *msg, int error_status);
void	trouble_exit(char *cmd, char *arg, char *msg, int exit_status);
int		ft_fork(void);

void	fill_path(t_vars *var);
void	initialisation(t_vars *var, char **av, char **env);

/* ************************************************************************** */
/*								BUILTIN FUNCTIONS							  */
/* ************************************************************************** */

int		builtin(t_vars *var, t_final *node);

int		echo(t_vars *var, t_final *node);
int		cd(t_vars *var, t_final *node);
int		pwd(t_vars *var, t_final *node);
int		export(t_vars *var, t_final *node);
int		unset(t_vars *var, t_final *node);
int		environment(t_vars *var, t_final *node);
int		exiting(t_vars *var, t_final *node);

int		builtincheck(char *name);
int		builtin(t_vars *var, t_final *node);

/* ******************** */
/*		DIRECTORY		*/
/* ******************** */

char	*dir(void);

/* ******************** */
/*		ENVIRONMENT		*/
/* ******************** */

int		replace_variable(t_vars *var, char *to_check, char *value);
int		little_checker(char *to_check);
int		validate_variable(t_vars *var, char *to_check);

void	sort_export(t_vars *var);
void	init_environment(t_vars *var);
void	init_export(t_vars *var);
int		ft_export(t_vars *var, char *to_add, int pass);
void	export_add(t_vars *var, char *to_add);
void	ft_unset(t_vars *var, char *to_del);
void	show_env(t_vars *var, t_final *node);
void	show_exp(t_vars *var, t_final *node);
char	*get_env_var(t_vars *var, char *to_get);
int		check_env_var(t_vars *var, char *to_check);

/* ******************** */
/*		HEREDOC			*/
/* ******************** */

char	*var_into_heredoc(t_vars *var, char *to_check, t_allways aws);
char	*heredoc_expand(t_vars *var, char *to_search);
char	*heredoc_core(t_vars *var, char *delimiter);
void	wait_exit(t_vars *var, t_allways w);
void	heredoc(t_vars *var, char *delimiter, int *fd);

/* ******************** */
/*		EXECUTION		*/
/* ******************** */

int		iterate_pipes(t_final **node);
void	iterate_files(t_vars *var, t_final **node);
int		node_close(t_final *node);
void	full_close(t_final **node);
void	duping(t_final *node);
void	wait_status(t_vars *var, t_allways w);
char	*exe_path_set(t_vars *var, char *exe);// too see
void	executor(t_vars *var, t_final **node);

#endif
