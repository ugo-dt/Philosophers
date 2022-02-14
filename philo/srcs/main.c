/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 13:12:54 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/02/14 12:19:32 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

int	exit_error(t_rules *r, int e)
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
		pthread_mutex_unlock(&r->logs);
	}
	clear_philo(r);
	clear_mutexes(r, r->nb_philo);
	return (EXIT_FAILURE);
}

int	main(int ac, const char **av)
{
	int		done;
	t_rules	rules;

	memset(&rules, 0, sizeof(t_rules));
	if (ac < 5 || ac > 6)
		return (exit_error(&rules, 1));
	done = init_rules(&rules, ac, av);
	if (done != EXIT_SUCCESS)
		return (exit_error(&rules, done));
	done = start(&rules);
	if (done != EXIT_SUCCESS)
		return (exit_error(&rules, done));
	pthread_mutex_lock(&rules.dead);
	pthread_mutex_unlock(&rules.dead);
	pthread_mutex_destroy(&rules.logs);
	pthread_mutex_destroy(&rules.dead);
	clear_philo(&rules);
	clear_mutexes(&rules, rules.nb_philo);
	return (EXIT_SUCCESS);
}
