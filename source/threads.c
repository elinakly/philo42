/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:29:26 by eklymova          #+#    #+#             */
/*   Updated: 2025/06/06 17:26:42 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_routine(t_philo *philo_struct, const char *message)
{
	pthread_mutex_lock(philo_struct->params->print_mutex);
	printf("%lld Philosopher %d %s\n", time_now() - philo_struct->last_meal, philo_struct->id, message);
	pthread_mutex_unlock(philo_struct->params->print_mutex);
}

void	*philo_does(void *args)
{
	t_philo	*philo_struct;

	philo_struct = (t_philo *)args;
	while (1)
	{
		print_routine(philo_struct, "is thinking");
		philo_struct->last_meal = time_now();
		pthread_mutex_lock(philo_struct->left_fork);
		print_routine(philo_struct, "has taken a fork");
		pthread_mutex_lock(philo_struct->right_fork);
		print_routine(philo_struct, "has taken a fork");
		printf("Philosopher %d is eating\n", philo_struct->id);
		usleep(philo_struct->params->time_to_eat * 1000); 
		pthread_mutex_unlock(philo_struct->right_fork);
		pthread_mutex_unlock(philo_struct->left_fork);
		print_routine(philo_struct, "is sleeping");
		usleep(philo_struct->params->time_to_sleep * 1000);
	}
	return (NULL);
}

bool	create_threads(t_parse	*parse, t_philo *philo_struct)
{
	int	i;

	i = 0;
	while (i < parse->nbr_of_philo)
	{
		philo_struct[i].id = i + 1;
		philo_struct[i].params = parse;
		philo_struct[i].left_fork = &parse->forks[i];
		philo_struct[i].right_fork = &parse->forks[(i + 1) % parse->nbr_of_philo];
		if (pthread_create(&philo_struct[i].thread, NULL, philo_does, &philo_struct[i]))
			return (false);
		i++;
	}
	i = 0;
	while (i < parse->nbr_of_philo)
	{
		if (pthread_join(philo_struct[i].thread, NULL))
			return (false);
		i++;
	}
	return (true);
}

bool	malloc_philo(t_parse	*parse, t_philo	**philo_struct)
{
	*philo_struct = malloc(sizeof(t_philo) * parse->nbr_of_philo);
	if (!*philo_struct)
		return (false);
	return (true);
}
