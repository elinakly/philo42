/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:58:43 by eklymova          #+#    #+#             */
/*   Updated: 2025/06/19 12:40:26 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	time_now(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

bool	init_philo_thread(t_parse *parse, t_philo *philo, int i)
{
	philo->id = i + 1;
	philo->params = parse;
	philo->left_fork = &parse->forks[i];
	philo->right_fork = &parse->forks[(i + 1) % parse->nbr_of_philo];
	philo->last_meal = parse->start_time;
	philo->have_eaten = 0;
	if (pthread_mutex_init(&philo->last_meal_mutex, NULL))
		return (false);
	if (pthread_mutex_init(&philo->have_eaten_mutex, NULL))
		return (false);
	if (pthread_create(&philo->thread, NULL, philo_does, philo))
		return (false);
	return (true);
}

void	philo_take_forks(t_philo *philo_struct)
{
	if (philo_struct->id % 2 == 0)
	{
		pthread_mutex_lock(philo_struct->right_fork);
		print_routine(philo_struct, "has taken a fork");
		pthread_mutex_lock(philo_struct->left_fork);
		print_routine(philo_struct, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo_struct->left_fork);
		print_routine(philo_struct, "has taken a fork");
		pthread_mutex_lock(philo_struct->right_fork);
		print_routine(philo_struct, "has taken a fork");
	}
	pthread_mutex_lock(&philo_struct->last_meal_mutex);
	philo_struct->last_meal = time_now();
	pthread_mutex_unlock(&philo_struct->last_meal_mutex);
	print_routine(philo_struct, "is eating");
	safe_usleep(philo_struct->params, philo_struct->params->time_to_eat);
	pthread_mutex_lock(&philo_struct->have_eaten_mutex);
	philo_struct->have_eaten++;
	pthread_mutex_unlock(&philo_struct->have_eaten_mutex);
	pthread_mutex_unlock(philo_struct->right_fork);
	pthread_mutex_unlock(philo_struct->left_fork);
}

bool	if_one(t_philo	*philo_struct)
{
	if (philo_struct->params->nbr_of_philo == 1)
	{
		pthread_mutex_lock(philo_struct->left_fork);
		print_routine(philo_struct, "has taken a fork");
		safe_usleep(philo_struct->params,
			philo_struct->params->time_to_die + 5);
		pthread_mutex_unlock(philo_struct->left_fork);
		return (true);
	}
	return (false);
}
