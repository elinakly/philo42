/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:57:01 by eklymova          #+#    #+#             */
/*   Updated: 2025/06/04 20:40:22 by eklymova         ###   ########.fr       */
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

# define EAT "is eating"
# define SLEEP "is sleeping"
# define FORK "has taken a fork"
# define THINK "is thinking"
# define DIE "DIED"
# define LEFT 0
# define RIGHT 1


typedef struct s_parse
{
	ssize_t			nbr_of_philo;
	ssize_t			time_to_die;
	ssize_t			time_to_eat;
	ssize_t			time_to_sleep;
	ssize_t			eats_time;
	pthread_mutex_t	*forks;
}	t_parse;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	t_parse			*params;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;


int		ft_atoi(const char *str);
bool	ft_parse(t_parse *parse, int argc, char **argv);
bool	malloc_philo(t_parse	*parse, t_philo	**philo_struct);
bool	create_threads(t_parse	*parse, t_philo *philo_struct);
void	*philo_does(void *args);

#endif