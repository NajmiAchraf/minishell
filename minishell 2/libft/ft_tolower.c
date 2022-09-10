/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 19:30:45 by ohrete            #+#    #+#             */
/*   Updated: 2021/11/24 00:48:48 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	else
		return (c);
}
// #include<stdio.h>
// int main()
// {
// 	char s[]= "M BEAUTIFUL IN MY OWN WAY THIS IS WHAT MAKS ME SPECIAL";
// 	printf("%s",ft_tolower(s));
// }