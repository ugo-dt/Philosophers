/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 13:15:39 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/02/23 14:18:52 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define PHILO_USAGE 	"./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]"
# define NO_PHILOSOPHERS "philo: error: expected at least 1 philosopher"
# define ERROR_MUTEXES	"philo: error: could not create mutexes"
# define ERROR_MEMORY	"philo: unexpected memory error: aborting"
# define ERROR_THREADS	"philo: error: could not create threads"

struct	s_rules;

typedef struct s_philosopher
{
	uint8_t			is_eating;
	uint32_t		nb;
	uint32_t		left_fork;
	uint32_t		right_fork;
	uint64_t		last_meal;
	pthread_t		thread_id;
	pthread_t		reaper;
	pthread_mutex_t	hunger;
	pthread_mutex_t	is_done;
	struct s_rules	*rules;
}t_philo;

/*
 * @param number_of_philosophers Le nombre de philosophes, mais aussi le nombre
 * de fourchettes.
 * @param time_to_die (en ms) Si un philosophe n’a pas commencé à manger
 * time_to_die millisecondes après le début de son précédent repas ou depuis le
 * début de la simulation, il meurt.
 * @param time_to_eat (en ms) Le temps qu’un philosophe prend à manger.
 * Pendant ce temps, un philosophe doit garder ses deux fourchettes.
 * @param time_to_sleep (en ms) Le temps qu’un philosophe passe à dormir.
 * @param number_of_times_each_philosopher_must_eat (argument optionnel) Si tous
 * les philosophes ont mangé au moins 'number_of_times_each_philosopher_must_eat'
 * fois, la simulation prend fin. Si cet argument n’est pas spécifié, alors
 * la simulation prend fin à la mort d’un philosophe.
*/
typedef struct s_rules
{
	int8_t			all_ate;
	int32_t			nb_philo;
	int32_t			time_to_die;
	int32_t			time_to_eat;
	int32_t			time_to_sleep;
	int32_t			nb_must_eat;
	uint64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	logs;
	pthread_mutex_t	dead;
	t_philo			*philo;
}t_rules;

/* clear */
void				clear_mutexes(t_rules *r, int max);
void				clear_philo(t_rules *r);

/* init */
int					init_rules(t_rules *rules, int ac, const char **av);

/* libft */
int					ft_atoi(const char *s);
void				ft_putstr_fd(const char *s, int fd);
void				ft_putendl_fd(const char *s, int fd);

/* log.c */
void				print_log(t_philo *p, char *log);

/* philo */
int					start(t_rules *r);

static inline void	done_eating(int32_t n)
{
	if (n == 1)
		printf("once\n");
	else if (n == 2)
		printf("twice\n");
	else
		printf("%d times\n", n);
}

/* time */
uint64_t			get_time(void);
void				ft_sleep(uint64_t t);

void				exit_error(t_rules *r, int e);
void				exit_philo(t_rules *r, int status);

// DEBUG
void				debug(t_rules *r);

/* PHILO_H */
#endif
