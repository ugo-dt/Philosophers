/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:23:26 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/03/03 10:11:04 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_log(t_philo *p, char *log)
{
	pthread_mutex_lock(&p->rules->logs);
	pthread_mutex_lock(&p->rules->mutex_dead);
	if (!p->rules->dead)
		printf("%llu\t%u %s\n",
			get_time() - p->rules->start_time, p->nb + 1, log);
	pthread_mutex_unlock(&p->rules->mutex_dead);
	pthread_mutex_unlock(&p->rules->logs);
}
