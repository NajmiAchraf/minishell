/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 21:12:38 by ohrete            #+#    #+#             */
/*   Updated: 2022/09/10 21:45:09 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int syntax_error(char *str)  // still this case: > | l && empty node
{
    int i;
    //int q;

    i = 0;
    //q = 0;
    if (str[0] == '|')
        return (0);
    while (str[i] !='\0')
    {
        // if (q == '"' || q == '\'')
        //     q =
        if(str[i] == '|' && str[i + 1] == '|')
            return (0);
        //if ()
        i++;
    }
    if (str[ft_strlen(str) - 1] =='|')
        return (0);
    return (1);
}