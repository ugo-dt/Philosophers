/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:55:01 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/03/03 11:03:11 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	no_friends_no_forks(t_philo *p)
{
	while (1)
	{
		pthread_mutex_lock(&p->rules->mutex_dead);
		if (p->rules->dead)
		{
			pthread_mutex_unlock(&p->rules->mutex_dead);
			pthread_mutex_unlock(&p->rules->mutex_right_fork);
			return (1);
		}
		pthread_mutex_unlock(&p->rules->mutex_dead);
	}
	return (0);
}

void	eat(t_philo *p)
{
	t_rules	*r;

	r = p->rules;
	pthread_mutex_lock(&r->forks[p->left_fork]);
	print_log(p, "has taken a fork");
	pthread_mutex_lock(&r->mutex_right_fork);
	if (p->rules->nb_philo < 2 && no_friends_no_forks(p))
		return ;
	pthread_mutex_unlock(&r->mutex_right_fork);
	pthread_mutex_lock(&r->forks[p->right_fork]);
	print_log(p, "has taken a fork");
	pthread_mutex_lock(&p->eating);
	p->last_meal = get_time();
	print_log(p, "is eating");
	ft_sleep(p, r->time_to_eat);
	pthread_mutex_unlock(&p->eating);
	pthread_mutex_unlock(&r->forks[p->left_fork]);
	pthread_mutex_unlock(&r->forks[p->right_fork]);
}
