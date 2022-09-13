/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 22:11:06 by ohrete            #+#    #+#             */
/*   Updated: 2022/09/12 03:16:27 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# define OUTPUT '>'
# define INPUT '<'
# define PIPE '|'
# define APPEND 'A' // >>
# define EXPAND '$'
# define SQ '\''
# define DQ '\"'
# define HERE_DOC 'H' // <<
# define WORD 'W'

// int g_status;
// //env
// typedef struct s_env
// {
// 	char			*name;
// 	char			*value;
// 	t_vars			*env_var;
// 	struct s_env	*next;
// }	t_env;

// //tokenizer
// typedef struct s_token
// {
// 	int				start;
// 	char			*ptr;
// 	char			*new;
// 	char			*str;
// 	int				id;
// 	char			**av;
// 	t_env			*fst_link;
// 	struct s_token	*next;
// }	t_token;

// //save last value of envp and argv
// typedef struct s_save
// {
// 	t_env *env;
// 	char **av;
// }	t_save;

// /*** strcut for parser ***/
// typedef struct s_cmd
// {
// 	char *str;
// 	struct s_cmd *next;
// }	t_cmd;

// typedef struct s_file
// {
// 	char *str;
// 	int id;
// 	struct s_file *next;
// }	t_file;
// typedef struct s_final
// {
// 	int		type;
// 	int		infile;
// 	int		outfile;
// 	t_file	*file;
// 	t_cmd	*name;
// 	char	**cmd;
// 	struct s_final *next;
// }	t_final;
// /*** end struct of parser ***/

// int syntax_error(char *str);
// char	*search_name(char *name, int i);
// char	*search_value(char *value, int i);
// t_env	*fill_struct(char *name, char *value);
// void	add_first(t_env **fst_link, t_env *new);
// void	add_last(t_env **head, t_env *new);
// char	*getting_env(t_env *env, char *name);
// t_env	*setting_env(char **env);
// int		space(char c);
// t_token	*new_node(char *str, int id);
// void	add_token_last(t_token **head, t_token *new);
// void	single_quote(t_token **head, char *line, int *i);
// char	*ft_expand(char *str, t_env *env, char **av);
// void	double_quote(t_save *save, t_token **temp, char *line, int *i);
// int		skip_char(char c);
// void	setting_word(t_save *save, t_token **temp, char *line, int *i);
// void	redirection(t_token **head, char *str, int *i);
// int		other_char(char c);
// void	dollar(t_save *save, t_token **temp, char *line, int *i);
// void	pipe_sign(t_token **head, int *i);
// void	tokens(char *line, t_token **temp, t_save *save, int *i);
// t_token *	tokenizer(char *line, char **av, t_env *env);
// t_final	*ft_parser(t_token *data);
// void ft_output(t_final *cmd);
// void	free_parser(t_final *cmd);
// int check_dollar(char *str);

// void free_tokens(t_token *data);
// // t_token	*create_node(void);
// //void	add_last_list(t_token **head, t_token *new);
// //int		 list_size(t_token *list);
// //void	clear_list(t_token **list);
// //int		my_errors(int e);
// void	ft_signals(void);
// void	rl_replace_line (const char *text, int clear_undo);
// void	to_array(t_final *node);

#endif
