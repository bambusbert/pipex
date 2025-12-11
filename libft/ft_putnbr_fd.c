/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:19:34 by slambert          #+#    #+#             */
/*   Updated: 2025/11/10 15:53:55 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	long	nl;
	int		i;

	nl = n;
	i = 0;
	if (nl < 0)
	{
		i += ft_putchar_fd('-', fd);
		nl *= -1;
	}
	if (nl > 9)
	{
		i += ft_putnbr_fd(nl / 10, fd);
	}
	i += ft_putchar_fd(nl % 10 + '0', fd);
	return (i);
}
/*
int	main(void)
{
	ft_putnbr_fd(-12345, 1);
} */