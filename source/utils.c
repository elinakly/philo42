/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
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

bool	malloc_philo(t_parse	*parse, t_philo	**philo_struct)
{
	*philo_struct = malloc(sizeof(t_philo) * parse->nbr_of_philo);
	if (!*philo_struct)
		return (false);
	return (true);
}

bool	is_everyone_alive(t_parse *params)
{
	bool	running;

	pthread_mutex_lock(params->death_mutex);
	running = !params->terminate;
	pthread_mutex_unlock(params->death_mutex);
	return (running);
}

void	safe_usleep(t_parse *params, long long duration_ms)
{
	long long	start;

	start = time_now();
	while (is_everyone_alive(params) && (time_now() - start < duration_ms))
		usleep(100);
}

void	print_routine(t_philo *philo_struct, const char *message)
{
	pthread_mutex_lock(philo_struct->params->death_mutex);
	if (philo_struct->params->terminate && ft_strncmp(message, "died", 4)
		&& ft_strncmp(message, "Eats Limit", 10))
	{
		pthread_mutex_unlock(philo_struct->params->death_mutex);
		return ;
	}
	pthread_mutex_lock(philo_struct->params->print_mutex);
	if (!ft_strncmp(message, "Eats Limit", 10))
		printf("%lld %s\n", time_now() - philo_struct->params->start_time,
			message);
	else
		printf("%lld %d %s\n", time_now() - philo_struct->params->start_time,
			philo_struct->id, message);
	pthread_mutex_unlock(philo_struct->params->print_mutex);
	pthread_mutex_unlock(philo_struct->params->death_mutex);
}
