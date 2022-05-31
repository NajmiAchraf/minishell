/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:12:21 by anajmi            #+#    #+#             */
/*   Updated: 2022/05/31 16:11:30 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include "Libft/libft.h"

# define TK_SPACE '0'
# define TK_AZ09 '1'
# define TK_PIP '2'
# define TK_RDRT '3'
# define TK_LDRT '4'

typedef struct	s_vars
{
	char	*buff;
	char	*bin;
	size_t	i;
	size_t	j;
	char	**tmp;
	char	**env;
	char	**newenv;
	char	***tmplist;
	char	**piplist;
	char	**cmdlist;
	char	**argslist;
	char	**slist;
}	t_vars;

size_t	ft_lstlen(char **list);

#endif
