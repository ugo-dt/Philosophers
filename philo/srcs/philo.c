/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:22:24 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/02/12 21:27:59 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *p)
{
	t_rules	*r;

	r = p->rules;
	pthread_mutex_lock(&r->forks[p->left_fork]);
	print_log(r, p->nb, "has taken a fork");
	pthread_mutex_lock(&r->forks[p->right_fork]);
	print_log(r, p->nb, "has taken a fork");
	pthread_mutex_lock(&p->hunger);
	p->is_eating = 1;
	p->last_meal = get_time();
	print_log(r, p->nb, "is eating");
	usleep(r->time_to_eat * 1000);
	p->is_eating = 0;
	pthread_mutex_unlock(&p->hunger);
	pthread_mutex_unlock(&r->forks[p->right_fork]);
	pthread_mutex_unlock(&r->forks[p->left_fork]);
	p->meals++;
}

static void	*philosophize(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	if (p->nb % 2)
		usleep(1000);
	p->last_meal = get_time();
	while (!p->rules->dead)
	{
		eat(p);
		if (p->rules->all_ate)
			break ;
		print_log(p->rules, p->nb, "is sleeping");
		usleep(p->rules->time_to_sleep * 1000);
		print_log(p->rules, p->nb, "is thinking");
	}
	return (NULL);
}

static int	finished_meals(t_rules *r)
{
	int32_t	i;
	t_philo	*p;

	if (!r->maxmeals)
		return (0);
	p = r->philo;
	i = 0;
	while (r->maxmeals != -1 && i < r->nb_philo && p[i].meals >= r->maxmeals)
	{
		pthread_mutex_lock(&r->logs);
		printf("%llu\t%u has eaten %u time(s)\n",
			get_time() - r->start_time, p->nb + 1, r->maxmeals);
		pthread_mutex_unlock(&r->logs);
		i++;
	}
	return (i == r->nb_philo);
}

static void	check_deaths(t_rules *r)
{
	int32_t	i;
	t_philo	*p;

	p = r->philo;
	while (!r->all_ate)
	{
		i = -1;
		while (++i < r->nb_philo && !r->dead)
		{
			pthread_mutex_lock(&p[i].hunger);
			if (!p[i].is_eating && get_time() > p[i].last_meal + r->time_to_die)
			{
				print_log(r, p[i].nb, "died");
				r->dead = 1;
			}
			pthread_mutex_unlock(&p[i].hunger);
			usleep(1000);
		}
		if (r->dead)
			break ;
		r->all_ate = finished_meals(r);
	}
}

int	start(t_rules *r)
{
	int32_t	i;

	debug(r);
	r->start_time = get_time();
	i = 0;
	while (i < r->nb_philo)
	{
		if (pthread_create(
				&r->philo[i].thread_id, // unique id for the new thread
				NULL, // attribute object, may be used to set thread attributes
				&philosophize, // function the thread will execute once created
				&r->philo[i]) // single argument passed to the function.
		)
			return (EXIT_FAILURE);
		pthread_detach(r->philo[i].thread_id);
		r->philo[i].last_meal = get_time();
		i++;
	}
	check_deaths(r);
	clear_philo(r);
	clear_mutexes(r, r->nb_philo);
	pthread_mutex_destroy(&r->logs);
	return (EXIT_SUCCESS);
}
