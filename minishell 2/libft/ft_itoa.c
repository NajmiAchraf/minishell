/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:31:19 by ohrete            #+#    #+#             */
/*   Updated: 2021/11/23 23:51:11 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count(int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	if (n == 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*tab;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	tab = malloc(ft_count(n) + 1);
	if (!tab)
		return (NULL);
	i = ft_count(n);
	tab [i] = '\0';
		i--;
	if (n == 0)
		tab[i] = '0';
	if (n < 0)
	{
		tab[0] = '-';
		n = -n;
	}
	while (n != 0)
	{
		tab[i] = n % 10 + 48;
		n = n / 10;
		i--;
	}
	return (tab);
}
// #include<stdio.h>
//  int main()
//  {
// 	printf("%s\n",ft_itoa(-2147483648));
// 	//printf("%s\n",ft_itoa(0));
// 	//printf("%s\n",ft_itoa(10));
//  }
