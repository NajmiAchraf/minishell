/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:35:32 by ohrete            #+#    #+#             */
/*   Updated: 2021/11/24 00:26:32 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (!s && !d)
		return (NULL);
	if (d > s)
		while (len--)
			d[len] = s[len];
	else
		ft_memcpy (d, s, len);
	return (d);
}
// #include<stdio.h>
// int main()
// {
// 	char a[100] = "helloworld";
// 	char b[100] = "oumaima is nice";
// 	ft_memmove(a, b, 8);
// 	printf("%s\n", a);
// }
