/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:22:35 by ohrete            #+#    #+#             */
/*   Updated: 2021/11/24 01:09:12 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	n;
	int		*ptr;

	n = count * size;
	ptr = malloc(sizeof(char) * n);
	if (ptr == NULL)
		return (NULL);
	ft_bzero (ptr, n);
	return (ptr);
}
// #include<stdio.h>
// int main()
// {
// 	char *a = "sunshine";
// 	a = ft_strdup(a);
// 	printf("%s\n",a);
// 	a = ft_calloc(8,1);
// }