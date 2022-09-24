/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:12:21 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/24 11:50:09 by anajmi           ###   ########.fr       */
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
/*								EXPORT_ENV.C								  */
/* ************************************************************************** */

int		replace_variable(t_vars *var, char *to_check, char *value);
int		little_checker(char *to_check);
int		validate_variable(t_vars *var, char *to_check);
int		ft_export(t_vars *var, char *to_add, int pass);
void	export_add(t_vars *var, char *to_add);

/* ************************************************************************** */
/*								INIT.C										  */
/* ************************************************************************** */

void	init_environment(t_vars *var);
void	init_export(t_vars *var);

/* ************************************************************************** */
/*								SHOW.C										  */
/* ************************************************************************** */

void	show_env(t_vars *var, t_final *node);
void	show_exp(t_vars *var, t_final *node);

/* ************************************************************************** */
/*								TOOLS.C										  */
/* ************************************************************************** */

void	sort_export(t_vars *var);
char	*get_env_var(t_vars *var, char *to_get);
int		check_env_var(t_vars *var, char *to_check);

/* ************************************************************************** */
/*								UNSET.C										  */
/* ************************************************************************** */

void	ft_unset(t_vars *var, char *to_del);

/* ************************************************************************** */
/*								BUILTIN.C									  */
/* ************************************************************************** */

int		builtincheck(char *name);
int		builtin(t_vars *var, t_final *node);

/* ************************************************************************** */
/*								BREAKING.C									  */
/* ************************************************************************** */

int		exiting(t_final *node);
int		trouble(char *cmd, char *arg, char *msg, int error_status);
void	trouble_exit(char *cmd, char *arg, char *msg, int exit_status);

/* ************************************************************************** */
/*								DIRECTORY.C									  */
/* ************************************************************************** */

char	*dir(void);
int		cd(t_vars *var, t_final *node);
int		pwd(t_final *node);

/* ************************************************************************** */
/*								ECHO.C										  */
/* ************************************************************************** */

int		echo(t_final *node);

/* ************************************************************************** */
/*								ENVIRONMENT.C								  */
/* ************************************************************************** */

int		export(t_vars *var, t_final *node);
int		unset(t_vars *var, t_final *node);
int		environment(t_vars *var, t_final *node);

/* ************************************************************************** */
/*								EXECUTION.C									  */
/* ************************************************************************** */

int		ft_fork(void);
void	fill_path(t_vars *var);
char	*exe_path_set(t_vars *var, char *exe);
void	initialisation(t_vars *var, char **av, char **env);

/* ************************************************************************** */
/*								EXECUTOR_TOOLS.C							  */
/* ************************************************************************** */

int		node_close(t_final *node);
void	full_close(t_final **node);
void	duping(t_final *node);
void	wait_status(t_vars *var, t_allways w);

/* ************************************************************************** */
/*								EXECUTOR.C									  */
/* ************************************************************************** */

void	executor(t_vars *var, t_final **node);

/* ************************************************************************** */
/*								HEREDOC.C									  */
/* ************************************************************************** */

char	*var_into_heredoc(t_vars *var, char *to_check, t_allways aws);
char	*heredoc_expand(t_vars *var, char *to_search);
char	*heredoc_core(t_vars *var, char *delimiter);
void	wait_exit(t_allways w);
void	heredoc(t_vars *var, char *delimiter, int *fd);

/* ************************************************************************** */
/*								ITERATE_FILES.C								  */
/* ************************************************************************** */

void	iterate_files(t_vars *var, t_final **node);

/* ************************************************************************** */
/*								ITERATE_PIPES.C								  */
/* ************************************************************************** */

int		iterate_pipes(t_final **node);

#endif
