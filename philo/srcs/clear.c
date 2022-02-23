/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 10:55:30 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/02/23 13:34:33 by ugdaniel         ###   ########.fr       */
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
	int32_t	i;

	if (!r->philo)
		return ;
	i = 0;
	while (i < r->nb_philo)
	{
		pthread_mutex_destroy(&r->philo[i].hunger);
		pthread_mutex_destroy(&r->philo[i].is_done);
		i++;
	}
	free(r->philo);
}
