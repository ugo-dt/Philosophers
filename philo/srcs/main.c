/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 13:12:54 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/02/12 15:23:38 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		ft_putendl_fd(ERROR_THREADS, STDERR_FILENO);
	clear_philo(r);
	clear_mutexes(r, r->nb_philo);
	return (EXIT_FAILURE);
}

int	main(int ac, const char **av)
{
	int		done;
	t_rules	rules;

	rules.philo = NULL;
	rules.forks = NULL;
	if (ac < 5 || ac > 6)
		return (exit_error(&rules, 1));
	done = init_rules(&rules, ac, av);
	if (done != EXIT_SUCCESS)
		return (exit_error(&rules, done));
	done = start(&rules);
	if (done != EXIT_SUCCESS)
		return (exit_error(&rules, done));
	return (EXIT_SUCCESS);
}
