/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 14:48:10 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/02/23 15:03:24 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

uint64_t	get_time(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) == -1)
		exit(1);
	return ((t.tv_sec * (uint64_t)1000) + (t.tv_usec / (uint64_t)1000));
}

/* Suspend thread execution for t milliseconds */
void	ft_sleep(uint64_t t)
{
	uint64_t	end;
	uint64_t	wait;

	end = get_time() + t;
	wait = end - t;
	while (get_time() < end)
		usleep(t / wait);
}
