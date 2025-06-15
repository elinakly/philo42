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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	print_routine(t_philo *philo_struct, const char *message)
{
	pthread_mutex_lock(philo_struct->params->death_mutex);
	if (philo_struct->params->someone_died && ft_strncmp(message, "died", 4) != 0)
	{
		pthread_mutex_unlock(philo_struct->params->death_mutex);
		return;
	}
	pthread_mutex_lock(philo_struct->params->print_mutex);
	printf("%lld %d %s\n", time_now() - philo_struct->params->start_time,
		philo_struct->id, message);
	pthread_mutex_unlock(philo_struct->params->print_mutex);
	pthread_mutex_unlock(philo_struct->params->death_mutex);
}

void	*death(void *args)
{
	int i;
	i = 0;
	t_philo	*philo_struct;

	philo_struct = (t_philo *)args;
	while (1)
	{
		while (i < (&philo_struct[0])->params->nbr_of_philo)
		{
			pthread_mutex_lock(philo_struct[i].last_meal_mutex);
			if ((time_now() - (&philo_struct[i])->last_meal > ((&philo_struct[i])->params->time_to_die)))
			{
				pthread_mutex_unlock(philo_struct[i].last_meal_mutex);
				pthread_mutex_lock(philo_struct->params->death_mutex);
				philo_struct->params->someone_died = true;
				pthread_mutex_unlock(philo_struct->params->death_mutex);
				print_routine(&philo_struct[i], "died");
				return (NULL);
			}
			else
				pthread_mutex_unlock(philo_struct[i].last_meal_mutex);
			i++;
		}
		usleep(1000);
		i = 0;
	}
}

bool	is_everyone_alive(t_parse *params)
{
	bool	running;

	pthread_mutex_lock(params->death_mutex);
	running = !params->someone_died;
	pthread_mutex_unlock(params->death_mutex);
	return (running);
}

void	safe_usleep(t_parse *params, long long duration_ms)
{
	long long	start;

	start = time_now();
	while (is_everyone_alive(params) && (time_now() - start < duration_ms))
		usleep(100); // Sleep in small intervals to stay responsive
}

void	*philo_does(void *args)
{
	t_philo	*philo_struct;

	philo_struct = (t_philo *)args;
	// if (philo_struct->id % 2 == 0)
	// 	usleep(philo_struct->params->time_to_eat * 1000 / 2);
	usleep((philo_struct->id % 2) * (philo_struct->params->time_to_eat * 1000 / 10));

	while (is_everyone_alive(philo_struct->params))
	{
		//if (!is_everyone_alive(philo_struct->params))
       // 	break;
		print_routine(philo_struct, "is thinking");
/*		if (philo_struct->id % 2 == 0)
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
		}*/
		pthread_mutex_lock(philo_struct->left_fork);
		print_routine(philo_struct, "has taken a fork");
		pthread_mutex_lock(philo_struct->right_fork);
		print_routine(philo_struct, "has taken a fork");
		pthread_mutex_lock(philo_struct->last_meal_mutex);
		philo_struct->last_meal = time_now();
		pthread_mutex_unlock(philo_struct->last_meal_mutex);
		print_routine(philo_struct, "is eating");
		safe_usleep(philo_struct->params, philo_struct->params->time_to_eat); 
		pthread_mutex_unlock(philo_struct->right_fork);
		pthread_mutex_unlock(philo_struct->left_fork);
		print_routine(philo_struct, "is sleeping");
		safe_usleep(philo_struct->params, philo_struct->params->time_to_sleep);
	}
	return (NULL);
}

bool	create_threads(t_parse	*parse, t_philo *philo_struct)
{
	int	i;

	i = 0;
	parse->start_time = time_now();
	//if (pthread_mutex_init(parse->print_mutex, NULL))
	//	return (false);
	while (i < parse->nbr_of_philo)
	{
		philo_struct[i].id = i + 1;
		philo_struct[i].params = parse;
		philo_struct[i].left_fork = &parse->forks[i];
		philo_struct[i].last_meal = parse->start_time;
		philo_struct[i].right_fork = &parse->forks[(i + 1) % parse->nbr_of_philo];
		philo_struct[i].last_meal_mutex = malloc(sizeof(pthread_mutex_t));
		if (!philo_struct[i].last_meal_mutex ||
			pthread_mutex_init(philo_struct[i].last_meal_mutex, NULL))
			return (false);
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
