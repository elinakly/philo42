/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:29:26 by eklymova          #+#    #+#             */
/*   Updated: 2025/06/19 12:37:58 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	*death(void *args)
{
	t_philo	*philo_struct;
	int		i;
	int		done_eating;

	philo_struct = (t_philo *)args;
	while (1)
	{
		i = 0;
		done_eating = 0;
		while (i < (&philo_struct[0])->params->nbr_of_philo)
		{
			if (!died(philo_struct, &done_eating, i++))
				return (NULL);
		}
		if (philo_struct[0].params->eats_time > 0
			&& done_eating == philo_struct[0].params->nbr_of_philo)
		{
			pthread_mutex_lock(philo_struct->params->death_mutex);
			philo_struct->params->terminate = true;
			pthread_mutex_unlock(philo_struct->params->death_mutex);
			print_routine(&philo_struct[0], "Eats Limit");
			return (NULL);
		}
		usleep(100);
	}
}

void	*philo_does(void *args)
{
	t_philo	*philo_struct;

	philo_struct = (t_philo *)args;
	usleep((philo_struct->id % 2) * (philo_struct->params->time_to_eat * 100));
	while (is_everyone_alive(philo_struct->params))
	{
		print_routine(philo_struct, "is thinking");
		if (if_one(philo_struct))
			return (NULL);
		if (philo_struct->params->nbr_of_philo % 2 == 1)
			safe_usleep(philo_struct->params, 200);
		philo_take_forks(philo_struct);
		print_routine(philo_struct, "is sleeping");
		safe_usleep(philo_struct->params, philo_struct->params->time_to_sleep);
	}
	return (NULL);
}

bool	create_threads(t_parse *parse, t_philo *philo_struct)
{
	int	i;

	i = 0;
	parse->start_time = time_now();
	while (i < parse->nbr_of_philo)
	{
		if (!init_philo_thread(parse, &philo_struct[i], i))
			return (false);
		i++;
	}
	if (pthread_create(&parse->death, NULL, death, philo_struct))
		return (false);
	i = 0;
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
