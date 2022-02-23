/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 16:17:51 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/02/23 14:17:54 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#define INT_MAX	2147483647
#define INT_MIN	-2147483648

int	ft_atoi(const char *s)
{
	int		digit;
	int		sign;
	int		result;

	if (!s)
		return (0);
	while (*s == ' ')
		s++;
	sign = 1;
	if (*s == '-' || *s == '+')
		if (*s++ == '-')
			sign = -1;
	result = 0;
	while (*s >= '0' && *s <= '9')
	{
		digit = *s++ - 48;
		if (result * sign > INT_MAX / 10
			|| ((sign == 1 && result >= 214748364 && digit >= 7)))
			return (INT_MAX);
		if (result * sign < INT_MIN / 10
			|| ((sign == -1 && result >= 214748364 && digit >= 8)))
			return (INT_MIN);
		result = result * 10 + digit;
	}
	return (result * sign);
}

void	ft_putstr_fd(const char *s, int fd)
{
	uint32_t	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		write(fd, &s[i++], 1);
}

void	ft_putendl_fd(const char *s, int fd)
{
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}
