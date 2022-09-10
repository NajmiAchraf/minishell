/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 22:11:06 by ohrete            #+#    #+#             */
/*   Updated: 2022/09/06 18:14:58 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "./libft/libft.h"

# include "Libft/libft.h"
# include "LibftPlus/libftplus.h"
# include "get_next_line/get_next_line.h"

# define OUTPUT '>'
# define INPUT '<'
# define PIPE '|'
# define APPEND 'A' // >>
# define EXPAND '$'
# define SQ '\''
# define DQ '\"'
# define HERE_DOC 'H' // <<
# define WORD 'W'

# define FIL 1
# define NAM 2

# define C_RES		"\033[0m"
# define C_RED		"\033[1;31m"
# define C_GREEN	"\033[1;32m"
# define C_YELOW	"\033[1;33m"
# define C_BLUE		"\033[1;34m"
# define C_CYAN		"\033[1;36m"

# define EXEC	1
# define REDIR	2
# define PIPE	3

# define MAXARG	10

/* ************************************************************************** */
/*								STRUCT OF PARSER							  */
/* ************************************************************************** */

int g_status;
//env
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

//tokenizer
typedef struct s_token
{
	char			*str;
	int				id;
	char			**av;
	t_env			*fst_link;
	struct s_token	*next;
}	t_token;

//save last value of envp and argv
typedef struct s_save
{
	t_env *env;
	char **av;
}	t_save;

/*** strcut for parser ***/
typedef struct s_cmd
{
	char *str;
	struct s_cmd *next;
}	t_cmd;

typedef struct s_file
{
	char *str;
	int id;
	struct s_file *next;
}	t_file;
typedef struct s_final
{
	int		type;
	int		infile;
	int		outfile;
	t_file	*file;
	t_cmd	*name;
	char	**cmd;
	struct s_final *next;
}	t_final;

/* ************************************************************************** */
/*								STRUCT OF EXECUTION							  */
/* ************************************************************************** */

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

struct s_cmd
{
	int type;
	t_execcmd	*exe;
	t_redircmd	*red;
	t_pipecmd	*pip;
};

typedef struct s_env
{
	size_t	sizeofexp;
	size_t	sizeofenv;
	char	**env;
}	t_env;

typedef struct	s_allways
{
	size_t	i;
	size_t	j;
	size_t	k;
	int		p[2];
}	t_allways;

typedef struct	s_vars
{
	int		exit_code;

	/* environment */
	t_env	env;
	char	*tmp;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	**temp;
	char	**temp1;
	char	**temp2;
	char	***temp3;

	char	**exepath;

	char	*buff;

	t_cmd	**cmd;
	size_t	cod;
}	t_vars;


/* ************************************************************************** */
/*								PARSRER FUNCTIONS							  */
/* ************************************************************************** */

int syntax_error(char *str);
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
void	single_quote(t_token **head, char *line, int *i);
char	*ft_expand(char *str, t_env *env, char **av);
void	double_quote(t_save *save, t_token **temp, char *line, int *i);
int		skip_char(char c);
void	setting_word(t_save *save, t_token **temp, char *line, int *i);
void	redirection(t_token **head, char *str, int *i);
int		other_char(char c);
void	dollar(t_save *save, t_token **temp, char *line, int *i);
void	pipe_sign(t_token **head, int *i);
void	tokens(char *line, t_token **temp, t_save *save, int *i);
t_token *	tokenizer(char *line, char **av, t_env *env);
t_final	*ft_parser(t_token *data);
void ft_output(t_final *cmd);
void	ft_free(t_final *cmd);
int		check_dollar(char *str);
void	ft_freetokens(t_token *data);
void	ft_signals(void);
void	rl_replace_line (const char *text, int clear_undo);
void	to_array(t_final *node);
int		list_size(t_cmd *list);
int		list_size1(t_final *list);

/* ************************************************************************** */
/*								MAIN FILE									  */
/* ************************************************************************** */

void	trouble(char *s);
int		fork1(void);
void	free1(char **tofree);

void	runcmd(t_cmd *cmd, t_vars *var);
void	fill_path(t_vars *var);
void	initialisation(t_vars *var, char **env);
void	hostname(t_vars *var);

/* ************************************************************************** */
/*								BUILTIN FUNCTIONS							  */
/* ************************************************************************** */

int		builtin(t_vars *var, t_execcmd *ecmd);

int		echo_check(char *args);
int		echo(t_vars *var, t_execcmd *ecmd);
int		cd(t_vars *var, t_execcmd *ecmd);
int		pwd(t_vars *var);
int		export(t_vars *var, t_execcmd *ecmd);
int		unset(t_vars *var, t_execcmd *ecmd);
int		environment(t_vars *var, t_execcmd *ecmd);

int		builtin(t_vars *var, t_execcmd *ecmd);

/* ******************** */
/*		DIRECTORY		*/
/* ******************** */

char	*dir();

/* ******************** */
/*		ENVIRONMENT		*/
/* ******************** */

int		replace_variable(t_vars *var, char *to_check, char *value);
int		var_into_var(t_vars *var, char **to_check, t_allways aws);
int		name_into_var(t_vars *var, char **to_check, t_allways aws);
int		outside_search_variable(t_vars *var, char *to_search, char *variable);
int		inside_search_variable(t_vars *var, char *to_search, int gen);
int		little_checker(t_vars *var);
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
