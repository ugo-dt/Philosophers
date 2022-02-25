/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 13:12:54 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/02/25 12:01:33 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

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

void	exit_error(t_rules *r, int e)
{
	if (e == 1)
	{
		ft_putstr_fd("philo: bad arguments\nusage: ", STDERR_FILENO);
		ft_putendl_fd(PHILO_USAGE, STDERR_FILENO);
	}
	if (e == 2)
		ft_putendl_fd(NO_PHILOSOPHERS, STDERR_FILENO);
	if (e == 3)
		ft_putendl_fd(ERROR_MUTEXES, STDERR_FILENO);
	if (e == 4)
		ft_putendl_fd(ERROR_MEMORY, STDERR_FILENO);
	if (e == 5)
	{
		pthread_mutex_lock(&r->logs);
		ft_putendl_fd(ERROR_THREADS, STDERR_FILENO);
	}
	exit_philo(r, EXIT_FAILURE);
}

void	exit_philo(t_rules *r, int status)
{
	clear_philo(r);
	clear_mutexes(r, r->nb_philo);
	exit(status);
}

int	main(int ac, const char **av)
{
	int		done;
	t_rules	rules;

	memset(&rules, 0, sizeof(t_rules));
	if (ac < 5 || ac > 6)
		exit_error(&rules, 1);
	done = init_rules(&rules, ac, av);
	if (done != EXIT_SUCCESS)
		exit_error(&rules, done);
	done = start(&rules);
	if (done != EXIT_SUCCESS)
		exit_error(&rules, done);
	pthread_mutex_destroy(&rules.logs);
	pthread_mutex_destroy(&rules.dead);
	clear_philo(&rules);
	clear_mutexes(&rules, rules.nb_philo);
	return (EXIT_SUCCESS);
}
