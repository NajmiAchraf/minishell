/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 22:44:17 by ohrete            #+#    #+#             */
/*   Updated: 2021/11/23 04:48:16 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char s, int fd)
{
	write(fd, &s, 1);
}

// #include <fcntl.h>
// int main()
// {
// 	int fd;
// 	fd = open("file.txt", O_CREAT | O_RDWR);
// 	ft_putchar_fd('h',fd);
// }
