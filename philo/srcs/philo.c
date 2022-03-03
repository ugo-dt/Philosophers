/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:01:43 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/03/03 10:32:36 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_loop(t_philo *p)
{
	int32_t		count;
	int32_t		max;

	count = 0;
	max = p->rules->nb_must_eat;
	while (1)
	{
		eat(p);
		count++;
		pthread_mutex_lock(&p->rules->mutex_dead);
		if ((max && count >= max) || p->rules->dead)
		{
			pthread_mutex_unlock(&p->rules->mutex_dead);
			break ;
		}
		pthread_mutex_unlock(&p->rules->mutex_dead);
		print_log(p, "is sleeping");
		ft_sleep(p, p->rules->time_to_sleep);
		print_log(p, "is thinking");
	}
}

void	*phi(void *philo)
{
	t_philo		*p;

	p = (t_philo *)philo;
	if (p->nb % 2)
		usleep(100);
	p->last_meal = get_time();
	if ((pthread_create(&p->check_death, NULL, &check_death, p)) != 0)
	{
		p->rules->dead = 1;
		ft_putendl_fd(ERROR_THREADS, STDERR_FILENO);
		return (NULL);
	}
	pthread_detach(p->check_death);
	philo_loop(p);
	return (NULL);
}

int	start(t_rules *r)
{
	int32_t	i;

	r->start_time = get_time();
	i = 0;
	while (i < r->nb_philo)
	{
		if (pthread_create(&r->philo[i].thread_id, NULL, &phi, &r->philo[i]))
		{
			r->dead = 1;
			return (5);
		}
		i++;
	}
	i = 0;
	while (i < r->nb_philo)
		pthread_join(r->philo[i++].thread_id, NULL);
	if (r->nb_must_eat && !r->dead)
	{
		pthread_mutex_lock(&r->mutex_dead);
		r->dead = 1;
		printf("%llu\tAll philosophers have eaten ",
			get_time() - r->start_time);
		done_eating(r->nb_must_eat);
	}
	return (EXIT_SUCCESS);
}
