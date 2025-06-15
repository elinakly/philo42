/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 19:35:34 by eklymova          #+#    #+#             */
/*   Updated: 2025/06/13 16:28:10 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	malloc_forks(t_parse *parse)
{
	int	i;

	parse->forks = malloc(sizeof(pthread_mutex_t) * parse->nbr_of_philo);
	parse->print_mutex = malloc(sizeof(pthread_mutex_t));
	parse->death_mutex = malloc(sizeof(pthread_mutex_t));
	if (!parse->forks || !parse->print_mutex || !parse->death_mutex)
		return (false);
	if (pthread_mutex_init(parse->print_mutex, NULL))
		return (false);
	if (pthread_mutex_init(parse->death_mutex, NULL))
		return (false);
	i = 0;
	while (i < parse->nbr_of_philo)
	{
		if (pthread_mutex_init(&parse->forks[i], NULL))
			return (false);
		i++;
	}
	return (true);
}

bool	ft_parse(t_parse *parse, int argc, char **argv)
{

	if (argc != 5 && argc != 6)
		return (false);
	parse->nbr_of_philo = ft_atoi(argv[1]);
	if (parse->nbr_of_philo == 1)
		return (false);
	parse->time_to_die = ft_atoi(argv[2]);
	parse->time_to_eat = ft_atoi(argv[3]);
	parse->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		parse->eats_time = ft_atoi(argv[5]);
	else
		parse->eats_time = -1;
	if (parse->nbr_of_philo == -2 || parse->time_to_die == -2
		|| parse->time_to_eat == -2 || parse->time_to_sleep == -2
		|| parse->eats_time == -2)
		return (false);
	if (!malloc_forks(parse))
		return (false);
	parse->someone_died = false;
	return (true);
}
