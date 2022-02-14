/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 15:13:17 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/02/14 17:07:33 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_log(t_rules *r, uint32_t nb, char *log)
{
	pthread_mutex_lock(&r->logs);
	if (!r->all_ate)
		printf("%llu\t%u %s\n", get_time() - r->start_time, nb + 1, log);
	pthread_mutex_unlock(&r->logs);
}
