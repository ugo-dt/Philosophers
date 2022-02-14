/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:22:24 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/02/14 18:00:25 by ugdaniel         ###   ########.fr       */
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
	p->last_meal = get_time();
	print_log(r, p->nb, "is eating");
	usleep(r->time_to_eat * 1000);
	pthread_mutex_unlock(&p->hunger);
	pthread_mutex_unlock(&r->forks[p->left_fork]);
	pthread_mutex_unlock(&r->forks[p->right_fork]);
	pthread_mutex_unlock(&p->is_done);
}

static void	*phi(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	p->last_meal = get_time();
	if (p->nb % 2)
		usleep(100);
	while (1)
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

static void	*count_meals(void *rules)
{
	int32_t	i;
	int32_t	meals;
	t_rules	*r;

	r = (t_rules *)rules;
	meals = 0;
	while (meals < r->nb_must_eat)
	{
		i = 0;
		while (i < r->nb_philo)
			pthread_mutex_lock(&r->philo[i++].is_done);
		meals++;
	}
	pthread_mutex_unlock(&r->dead);
	pthread_mutex_lock(&r->logs);
	printf("%llu\tAll philosophers have eaten %d time(s)\n",
		get_time() - r->start_time, r->nb_must_eat);
	return (NULL);
}

static void	*reaper(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	while (1)
	{
		pthread_mutex_lock(&p->hunger);
		if (get_time() > p->last_meal + p->rules->time_to_die)
		{
			print_log(p->rules, p->nb, "died");
			pthread_mutex_lock(&p->rules->logs);
			pthread_mutex_unlock(&p->rules->dead);
			pthread_mutex_unlock(&p->hunger);
			return (NULL);
		}
		pthread_mutex_unlock(&p->hunger);
		usleep(1000);
	}
	return (NULL);
}

int	start(t_rules *r)
{
	int32_t		i;
	pthread_t	tid;

	r->start_time = get_time();
	if (r->nb_must_eat
		&& pthread_create(&tid, NULL, &count_meals, r)
		&& pthread_detach(tid))
		return (5);
	i = 0;
	while (i < r->nb_philo)
	{
		r->philo[i].last_meal = get_time();
		if (pthread_create(&r->philo[i].thread_id, NULL, &phi, &r->philo[i])
			|| (pthread_detach(r->philo[i].thread_id) != 0)
			|| (pthread_create(&r->philo[i].reaper,
					NULL, &reaper, &r->philo[i])))
			return (5);
		i++;
	}
	return (EXIT_SUCCESS);
}
