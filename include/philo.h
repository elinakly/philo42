/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:57:01 by eklymova          #+#    #+#             */
/*   Updated: 2025/06/13 17:05:32 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_parse
{
	ssize_t			nbr_of_philo;
	ssize_t			time_to_die;
	ssize_t			time_to_eat;
	ssize_t			time_to_sleep;
	ssize_t			eats_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_mutex;
	long long		start_time;
	pthread_t		death;
	pthread_mutex_t	*death_mutex;
	bool			someone_died;
}	t_parse;

typedef struct s_philo
{
	int				id;
	long long		last_meal;
	pthread_t		thread;
	t_parse			*params;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t *last_meal_mutex;
}	t_philo;


int			ft_atoi(const char *str);
bool		ft_parse(t_parse *parse, int argc, char **argv);
bool		malloc_philo(t_parse	*parse, t_philo	**philo_struct);
bool		create_threads(t_parse	*parse, t_philo *philo_struct);
void		*philo_does(void *args);
long int	time_now(void);
void		print_routine(t_philo *philo_struct, const char *message);

#endif