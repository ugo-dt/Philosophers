/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:59:55 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/03/05 09:35:07 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_forks(t_rules *r)
{
	int32_t	i;

	r->forks = malloc(sizeof(pthread_mutex_t) * r->nb_philo);
	if (!r->forks)
		return (0);
	i = 0;
	while (i < r->nb_philo)
	{
		if (pthread_mutex_init(&(r->forks[i]), NULL) != EXIT_SUCCESS)
		{
			clear_mutexes(r, i);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	init_mutexes(t_rules *r)
{
	if (!init_forks(r))
		return (0);
	if (pthread_mutex_init(&r->logs, NULL) != EXIT_SUCCESS)
		return (0);
	if (pthread_mutex_init(&r->mutex_dead, NULL) != EXIT_SUCCESS)
		return (0);
	return (1);
}

static int	init_philosophers(t_rules *r)
{
	int32_t	i;

	r->philo = malloc(sizeof(t_philo) * r->nb_philo);
	if (!r->philo)
		return (0);
	i = 0;
	while (i < r->nb_philo)
	{
		r->philo[i].nb_philo = r->nb_philo;
		r->philo[i].last_meal = 0;
		r->philo[i].nb = i;
		r->philo[i].left_fork = i;
		if (i < r->nb_philo - 1)
			r->philo[i].right_fork = i + 1;
		else
			r->philo[i].right_fork = r->nb_philo - i - 1;
		r->philo[i].rules = r;
		if (pthread_mutex_init(&r->philo[i].eating, NULL) != 0)
			return (5);
		i++;
	}
	return (1);
}

int	digits_only(int ac, const char **av)
{
	int		i;
	int		j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	init_rules(t_rules *r, int ac, const char **av)
{
	if (!digits_only(ac, av))
		return (1);
	r->nb_philo = ft_atoi(av[1]);
	r->time_to_die = ft_atoi(av[2]);
	r->time_to_eat = ft_atoi(av[3]);
	r->time_to_sleep = ft_atoi(av[4]);
	if (r->nb_philo <= 0)
		return (2);
	if (r->time_to_die < 0 || r->time_to_eat < 0 || r->time_to_sleep < 0)
		return (1);
	if (ac == 6)
	{
		r->nb_must_eat = ft_atoi(av[5]);
		if (r->nb_must_eat <= 0)
			return (1);
	}
	if (!init_mutexes(r))
		return (3);
	if (!init_philosophers(r))
		return (4);
	return (EXIT_SUCCESS);
}
