/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:22:24 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/02/24 09:48:07 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *p)
{
	t_rules	*r;

	r = p->rules;
	pthread_mutex_lock(&r->forks[p->left_fork]);
	print_log(p, "has taken a fork");
	pthread_mutex_lock(&r->forks[p->right_fork]);
	print_log(p, "has taken a fork");
	pthread_mutex_lock(&p->hunger);
	p->last_meal = get_time();
	print_log(p, "is eating");
	ft_sleep(r->time_to_eat);
	pthread_mutex_unlock(&r->forks[p->left_fork]);
	pthread_mutex_unlock(&r->forks[p->right_fork]);
	pthread_mutex_unlock(&p->is_done);
	pthread_mutex_unlock(&p->hunger);
}

static void	*check_death(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	while (1)
	{
		pthread_mutex_lock(&p->hunger);
		if (get_time() > p->last_meal + p->rules->time_to_die)
		{
			print_log(p, "died");
			p->rules->all_ate = 1;
			exit_philo(p->rules, 0);
		}
		pthread_mutex_unlock(&p->hunger);
		ft_sleep(1);
	}
	return (NULL);
}

static void	*phi(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	p->last_meal = get_time();
	if (p->nb % 2)
		usleep(100);
	if ((pthread_create(&p->check_death, NULL, &check_death, philo)))
	{
		ft_putendl_fd(ERROR_THREADS, STDERR_FILENO);
		pthread_mutex_unlock(&p->rules->dead);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		eat(p);
		p->count++;
		if ((p->rules->nb_must_eat && p->count >= p->rules->nb_must_eat)
			|| p->rules->all_ate)
			while (1)
				ft_sleep(UINT32_MAX);
		print_log(p, "is sleeping");
		ft_sleep(p->rules->time_to_sleep);
		print_log(p, "is thinking");
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
	i = 0;
	while (i < r->nb_philo)
		pthread_mutex_lock(&r->forks[i++]);
	pthread_mutex_unlock(&r->dead);
	pthread_mutex_lock(&r->logs);
	printf("%llu\tAll philosophers have eaten ",
		get_time() - r->start_time);
	done_eating(r->nb_must_eat);
	return (NULL);
}

int	start(t_rules *r)
{
	int32_t		i;
	pthread_t	tid;

	r->start_time = get_time();
	if (r->nb_must_eat)
		if (pthread_create(&tid, NULL, &count_meals, r))
			return (5);
	i = 0;
	while (i < r->nb_philo)
	{
		if (pthread_create(&r->philo[i].thread_id, NULL, &phi, &r->philo[i]))
			return (5);
		i++;
	}
	pthread_mutex_lock(&r->dead);
	pthread_mutex_unlock(&r->dead);
	return (EXIT_SUCCESS);
}
