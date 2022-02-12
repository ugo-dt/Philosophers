/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 10:55:30 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/02/12 21:02:27 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clear_mutexes(t_rules *r, int32_t max)
{
	int32_t	i;

	if (r->forks)
	{
		i = 0;
		while (i < max)
			pthread_mutex_destroy(&r->forks[i++]);
		free(r->forks);
	}
}

void	clear_philo(t_rules *r)
{
	if (!r->philo)
		return ;
	free(r->philo);
}
