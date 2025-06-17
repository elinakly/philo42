/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:58:43 by eklymova          #+#    #+#             */
/*   Updated: 2025/06/06 14:01:54 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	time_now(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

bool	died(t_philo	*philo_struct, int *done_eating, int i)
{
	pthread_mutex_lock(&philo_struct[i].have_eaten_mutex);
	if (philo_struct[i].have_eaten >= philo_struct[i].params->eats_time)
		(*done_eating)++;
	pthread_mutex_unlock(&philo_struct[i].have_eaten_mutex);
	pthread_mutex_lock(&philo_struct[i].last_meal_mutex);
	if (time_now() - philo_struct[i].last_meal
		> philo_struct[i].params->time_to_die)
	{
		pthread_mutex_unlock(&philo_struct[i].last_meal_mutex);
		pthread_mutex_lock(philo_struct->params->death_mutex);
		philo_struct->params->terminate = true;
		pthread_mutex_unlock(philo_struct->params->death_mutex);
		print_routine(&philo_struct[i], "died");
		return (false);
	}
	else
		pthread_mutex_unlock(&philo_struct[i].last_meal_mutex);
	return (true);
}
