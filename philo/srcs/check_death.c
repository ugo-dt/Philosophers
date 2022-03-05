/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:55:55 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/03/05 09:38:32 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_time(t_philo *p)
{
	pthread_mutex_lock(&p->eating);
	if (get_time() > p->last_meal + (t_ull)p->rules->time_to_die)
	{
		pthread_mutex_lock(&p->rules->mutex_dead);
		pthread_mutex_lock(&p->rules->logs);
		if (!p->rules->dead)
			printf("%llu\t%u died\n",
				get_time() - p->rules->start_time, p->nb + 1);
		p->rules->dead = 1;
		pthread_mutex_unlock(&p->eating);
		pthread_mutex_unlock(&p->rules->mutex_dead);
		pthread_mutex_unlock(&p->rules->logs);
		return (1);
	}
	pthread_mutex_unlock(&p->eating);
	return (0);
}

void	*check_death(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	while (1)
	{
		pthread_mutex_lock(&p->rules->mutex_dead);
		if (p->rules->dead)
		{
			pthread_mutex_unlock(&p->rules->mutex_dead);
			return (NULL);
		}
		pthread_mutex_unlock(&p->rules->mutex_dead);
		if (check_time(p))
			return (NULL);
		ft_sleep(p, 1);
	}
	return (NULL);
}
