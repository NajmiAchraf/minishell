/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:57:16 by ohrete            #+#    #+#             */
/*   Updated: 2021/11/23 23:35:05 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*result;

	i = 0;
	if (!s)
		return (0);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	result = (char *)malloc(sizeof(char) * len + 1);
	if (!result)
		return (NULL);
	while (s[start + i] != '\0' && i < len)
	{
		if (start + i < ft_strlen(s))
			result [i] = s[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
// #include<stdio.h>
// int main()
// {
// 	printf("%s\n",ft_substr("hello beautiful world", 4, 5));
// }
