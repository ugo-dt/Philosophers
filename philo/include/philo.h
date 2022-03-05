/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:59:38 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/03/05 09:34:45 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdint.h>
# include <unistd.h>

# define PHILO_USAGE 	"./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]"
# define NO_PHILOSOPHERS "philo: error: expected at least 1 philosopher"
# define ERROR_MUTEXES	"philo: error: could not create mutexes"
# define ERROR_MEMORY	"philo: unexpected memory error: aborting"
# define ERROR_THREADS	"philo: error: could not create threads"
# define ALL_HAVE_EATEN	"All philosophers have eaten"

typedef unsigned long long	t_ull;

struct						s_rules;

typedef struct s_philosopher
{
	uint32_t		nb;
	int8_t			done;
	int32_t			nb_philo;
	uint32_t		left_fork;
	uint32_t		right_fork;
	t_ull			last_meal;
	pthread_t		thread_id;
	pthread_t		check_death;
	pthread_mutex_t	eating;
	struct s_rules	*rules;
}t_philo;

typedef struct s_rules
{
	int8_t			dead;
	int32_t			nb_philo;
	int32_t			time_to_die;
	int32_t			time_to_eat;
	int32_t			time_to_sleep;
	int32_t			nb_must_eat;
	t_ull			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	logs;
	pthread_mutex_t	mutex_dead;
	t_philo			*philo;
}t_rules;

/* check_death */
void				*check_death(void *philo);

/* eat */
void				eat(t_philo *p);

/* init */
int					init_rules(t_rules *rules, int ac, const char **av);

/* libft */
int					ft_atoi(const char *s);
void				ft_putstr_fd(const char *s, int fd);
void				ft_putendl_fd(const char *s, int fd);
int					ft_isdigit(int c);

/* log.c */
void				print_log(t_philo *p, char *log);

/* philo */
int					start(t_rules *r);

void				clear_mutexes(t_rules *r, int32_t max);

static inline void	done_eating(int32_t n)
{
	if (n == 1)
		printf("once\n");
	else if (n == 2)
		printf("twice\n");
	else
		printf("%d times\n", n);
}

/* Get current time in milliseconds */
static inline t_ull	get_time(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) == -1)
		return (0);
	return ((t.tv_sec * (t_ull)1000) + (t.tv_usec / (t_ull)1000));
}

/* Suspend thread execution for t milliseconds */
static inline void	ft_sleep(t_philo *p, t_ull t)
{
	t_ull	end;

	end = get_time() + t;
	while (get_time() < end)
	{
		pthread_mutex_lock(&p->rules->mutex_dead);
		if (p->rules->dead)
		{
			pthread_mutex_unlock(&p->rules->mutex_dead);
			return ;
		}
		pthread_mutex_unlock(&p->rules->mutex_dead);
		usleep(1);
	}
}

/* PHILO_H */
#endif
