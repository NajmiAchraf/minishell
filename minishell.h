/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 22:11:06 by ohrete            #+#    #+#             */
/*   Updated: 2022/09/28 19:17:14 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "Libft/libft.h"
# include "LibftPlus/libftplus.h"

# define OUTPUT '>'
# define INPUT '<'
# define PIPE "¶"
# define APPEND 'A'
# define EXPAND '$'
# define SQ '\''
# define DQ '\"'
# define HERE_DOC 'H'
# define WORD 'W'

typedef struct s_final	t_final;
typedef struct s_vars	t_vars;
int						g_status;
//env
typedef struct s_env
{
	char			*name;
	char			*value;
	t_vars			*env_var;
	struct s_env	*next;
}	t_env;

//tokenizer
typedef struct s_token
{
	int				start;
	char			*ptr;
	char			*new;
	char			*str;
	int				id;
	char			**av;
	t_env			*fst_link;
	struct s_token	*next;
}	t_token;

//save last value of envp and argv
typedef struct s_save
{
	t_env	*env;
	char	**av;
	int		error;
}	t_save;

/*** strcut for parser ***/
typedef struct s_cmd
{
	char			*str;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_file
{
	char			*str;
	int				id;
	struct s_file	*next;
}	t_file;

typedef struct s_final
{
	int				type;
	int				infile;
	int				outfile;
	t_file			*file;
	t_cmd			*name;
	char			**cmd;
	struct s_final	*next;
}	t_final;
/*** end struct of parser ***/

/*** strcut for execution ***/
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
	int		h;
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

	int		h;
	int		infile;
	char	*main_name;
	char	**exepath;
	int		*pid;
	char	*line;
	char	*gnl;
}	t_vars;
/*** end struct of execution ***/

int		syntax_error(char *str);
char	*search_name(char *name, int i);
char	*search_value(char *value, int i);
t_env	*fill_struct(char *name, char *value);
void	add_first(t_env **fst_link, t_env *new);
void	add_last(t_env **head, t_env *new);
char	*getting_env(t_env *env, char *name);
t_env	*setting_env(char **env);
int		space(char c);
t_token	*new_node(char *str, int id);
void	add_token_last(t_token **head, t_token *new);
char	*single_quote(char *line, int *i);
char	*ft_expand(char *str, t_env *env, char **av);
char	*double_quote(t_save *save, char *line, int *i);
int		skip_char(char c);
int		setting_word(t_save *save, t_token **temp, char *line, int *i);
void	redirection(t_token **head, char *str, int *i);
int		other_char(char c);
char	*dollar(t_save *save, t_token **temp, char *line, int *i);
void	pipe_sign(t_token **head, int *i);
char	*convert_char_str(char c);
void	tokens(char *line, t_token **temp, t_save *save, int *i);
t_token	*tokenizer(char *line, t_save *save);
t_final	*ft_parser(t_token *data);
void	ft_output(t_final *cmd);
int		check_dollar(char *str);
void	free_tokens(t_token *data);
void	free_parser(t_final *cmd);
void	ft_signals(void);
void	rl_replace_line(const char *text, int clear_undo);
void	to_array(t_final *node);
int		list_size(t_cmd *list);
int		redirect(char *str);
t_file	*file_node(char *str, int type);
t_final	*create_node(void);
t_final	*link_nodes(t_final *head, t_final **link, t_final *tmp);
t_token	*ft_lstlast1(t_token *lst);
void	check_last_word(t_token **temp, t_save *save);
int		allspaces(char *line);

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

void	node_close(t_final *node);
void	full_close(t_final **node);
void	duping(t_final **node);
void	wait_status(t_vars *var, t_allways w);
void	waiting(t_vars *var, t_final **node);

/* ************************************************************************** */
/*								EXECUTOR1.C									  */
/* ************************************************************************** */

void	execute_builtin(t_vars *var, t_final **node);
void	execute_builtin_fork(t_vars *var, t_final **node);
void	execute_execve_fork(t_vars *var, t_final **node, t_final **n);

/* ************************************************************************** */
/*								EXECUTOR2.C									  */
/* ************************************************************************** */

int		terminate(t_final **node, int rtn);
int		execute_fork(t_vars *var, t_final **node, t_final **n, t_allways w);
int		executor_core(t_vars *var, t_final **node, t_allways w);
int		executor(t_vars *var, t_final **node);

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

int		iterate_files(t_vars *var, t_final **node);

/* ************************************************************************** */
/*								ITERATE_HEREDOC.C							  */
/* ************************************************************************** */

int		iterate_heredoc(t_vars *var, t_final **node);

/* ************************************************************************** */
/*								ITERATE_PIPES.C								  */
/* ************************************************************************** */

int		iterate_pipes(t_final **node);

#endif