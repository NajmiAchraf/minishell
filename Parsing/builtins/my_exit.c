/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 10:27:04 by ohrete            #+#    #+#             */
/*   Updated: 2022/08/08 11:37:22 by ohrete           ###   ########.fr       */
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

int my_isdigit(char *str)
{
    int i;
    
    i = 0;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i] >= '0' && str[i] <= '9')
        i++;
    if (str[i] != '\0')
        return (1);
    return (0);
}

void    exit_errors(void)
{
    int rslt;
    int num;
    int check;
    
    if (check == 0 && rslt == 1)
    {
        printf("exit\n");
        exit(num);
    }
    else if (check == 0 && rslt >= 2)
    {
        printf("exit: too many arguments\n");
        //status code = 1;
    }
    else if (check == 1 && rslt >= 1)
    {
        printf ("exit: numeric argument required\n");
        exit(255);
    }
}

void    my_exit()
{
    int rslt;
    int num;
    int check;

    rslt = arg_counting();
    if (rslt == 0)
    {
        printf("exit\n");
        exit(0);
    }
    num = ft_atoi();
    check = my_isdigit();
    exit_errors();
}