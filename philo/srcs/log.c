/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 15:13:17 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/02/22 18:04:50 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_log(t_philo *p, char *log)
{
	pthread_mutex_lock(&p->rules->logs);
	if (!p->rules->all_ate)
		printf("%llu\t%u %s\n",
			get_time() - p->rules->start_time, p->nb + 1, log);
	pthread_mutex_unlock(&p->rules->logs);
}
