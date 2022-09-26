/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftplus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:58:11 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/26 14:18:28 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPLUS_H
# define LIBFTPLUS_H
# include <stddef.h>
# include <stdlib.h>
# include "../Libft/libft.h"

void	ft_free(char **tofree);
int		ft_islower(int c);
int		ft_isupper(int c);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_lstlen(char **list);
size_t	ft_lstslen(char ***list);
void	ft_swap_dp(char **n1, char **n2);
void	ft_swap_tp(char ***n1, char ***n2);
int		my_isalnum(int c);
char	*my_strdup(char *s1);
char	*my_strjoin(char*s1, char *s2);

#endif
