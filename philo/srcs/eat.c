/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:55:01 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/03/03 10:33:26 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *p)
{
	t_rules	*r;

	r = p->rules;
	pthread_mutex_lock(&r->forks[p->left_fork]);
	print_log(p, "has taken a fork");
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
