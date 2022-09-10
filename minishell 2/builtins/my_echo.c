/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 09:58:20 by ohrete            #+#    #+#             */
/*   Updated: 2022/08/08 11:40:25 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int arg_counting(char **arg)
{
    int i;
    int count;

    count = 0;
    i = 1;
    while (arg[i])
    {
        i++;
        count++;
    }
    return (count);
}

void    my_echo()