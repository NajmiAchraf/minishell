/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:46:39 by ohrete            #+#    #+#             */
/*   Updated: 2021/11/24 00:48:39 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	beg;
	unsigned int	end;
	char			*reslt;

	beg = 0;
	end = 0;
	if (!s1)
		return (NULL);
	while (s1[end])
		end++;
	while (s1[beg] && ft_strchr(set, s1[beg]))
		beg++;
	while (end > beg && ft_strchr(set, s1[end]))
		end--;
	reslt = ft_substr(s1, beg, end - beg + 1);
	return (reslt);
}

// #include <stdio.h>
// int main()
// {
// 	char *s1 = "do baby shark do";
// 	char *a = ft_strtrim(s1, "do");
// 	printf("%s", a);
// }