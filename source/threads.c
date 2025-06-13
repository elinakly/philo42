/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:29:26 by eklymova          #+#    #+#             */
/*   Updated: 2025/06/13 18:04:16 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_routine(t_philo *philo_struct, const char *message)
{
	pthread_mutex_lock(philo_struct->params->print_mutex);
	printf("%lld %d %s\n", time_now()
		- philo_struct->params->start_time, philo_struct->id, message);
	pthread_mutex_unlock(philo_struct->params->print_mutex);
}
void	*death(void *args)
{
	int i = 0;
	t_philo	*philo_struct;

	philo_struct = (t_philo *)args;
	while (1)
	{
		while (i < (&philo_struct[0])->params->nbr_of_philo)
		{
			if ((time_now() - (&philo_struct[i])->last_meal > ((&philo_struct[i])->params->time_to_die)))
			{
				print_routine(&philo_struct[i], "died");
				return NULL; // set something to false so the philos stop but for now we just stop printing deaths
			}
			i++;
		}
		usleep(1000);
		i = 0;
	}
}


void	*philo_does(void *args)
{
	t_philo	*philo_struct;

	philo_struct = (t_philo *)args;
	while (1)
	{
		print_routine(philo_struct, "is thinking");
		pthread_mutex_lock(philo_struct->left_fork);
		print_routine(philo_struct, "has taken a fork");
		pthread_mutex_lock(philo_struct->right_fork);
		print_routine(philo_struct, "has taken a fork");
		philo_struct->last_meal = time_now();
		print_routine(philo_struct, "is eating");
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
	parse->start_time = time_now();
	while (i < parse->nbr_of_philo)
	{
		philo_struct[i].id = i + 1;
		philo_struct[i].params = parse;
		philo_struct[i].left_fork = &parse->forks[i];
		philo_struct[i].last_meal = parse->start_time;
		philo_struct[i].right_fork = &parse->forks[(i + 1) % parse->nbr_of_philo];
		if (pthread_create(&philo_struct[i].thread, NULL, philo_does, &philo_struct[i]))
			return (false);
		i++;
	}
	i = 0;
	if (pthread_create(&parse->death, NULL, death, philo_struct))
		return (false);
	while (i < parse->nbr_of_philo)
	{
		if (pthread_join(philo_struct[i].thread, NULL))
			return (false);
		i++;
	}
	if (pthread_join(parse->death, NULL))
		return (false);
	return (true);
}

bool	malloc_philo(t_parse	*parse, t_philo	**philo_struct)
{
	*philo_struct = malloc(sizeof(t_philo) * parse->nbr_of_philo);
	if (!*philo_struct)
		return (false);
	return (true);
}
