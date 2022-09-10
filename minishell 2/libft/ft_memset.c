/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 20:11:54 by ohrete            #+#    #+#             */
/*   Updated: 2021/11/24 00:32:02 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*tb;

	i = 0;
	tb = (unsigned char *)b;
	while (i < len)
	{
		tb[i] = c;
		i++;
	}
	return (b);
}

// #include<stdio.h>
// int main()
// {
// 	char x[]="oumaima";
// 	char y = 'g';
// 	ft_memset(x, y,2);
// 	printf("%s\n", x);
// }