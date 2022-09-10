/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:40:29 by ohrete            #+#    #+#             */
/*   Updated: 2021/11/24 00:46:03 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len_d;
	size_t	len_s;

	i = 0;
	j = 0;
	len_d = ft_strlen(dest);
	len_s = ft_strlen(src);
	if (size == 0 || size <= len_d)
		return (size + len_s);
	while (dest[i])
		i++;
	while (src[j] != '\0' && j < size - len_d -1)
	{
		dest[i] = src [j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (len_d + len_s);
}

// #include <stdio.h>
// int main()
// {
// 	char x[] = "hello";
// 	char y[] = "universe";
// 	printf("%zu",ft_strlcat(x,y, 15));
// 	return(0);
// }