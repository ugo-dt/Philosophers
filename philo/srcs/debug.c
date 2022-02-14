/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 10:34:49 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/02/14 10:49:04 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	debug(t_rules *r)
{
	int32_t	i;

	printf(">>> DEBUG <<<\n");
	i = 0;
	while (i < r->nb_philo)
	{
		printf("-----------------\n");
		printf("> Philo %d:\n", i);
		printf("Left fork:\t%d\n", r->philo[i].left_fork);
		printf("Right fork:\t%d\n", r->philo[i].right_fork);
		i++;
	}
}
