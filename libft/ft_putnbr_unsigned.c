/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:08:29 by slambert          #+#    #+#             */
/*   Updated: 2025/12/03 14:13:07 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd_unsigned(unsigned int n, int fd)
{
	int	i;

	i = 0;
	if (n > 9)
	{
		i += ft_putnbr_fd_unsigned(n / 10, fd);
	}
	i += ft_putchar_fd(n % 10 + '0', fd);
	return (i);
}
