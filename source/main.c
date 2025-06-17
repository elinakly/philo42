/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:15:55 by eklymova          #+#    #+#             */
/*   Updated: 2025/06/17 16:39:36 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_struct(t_philo	*philo_struct, t_parse	parse)
{
	int	i;

	if (philo_struct)
	{
		i = 0;
		while (i < parse.nbr_of_philo)
		{
			pthread_mutex_destroy(&philo_struct[i].last_meal_mutex);
			pthread_mutex_destroy(&philo_struct[i].have_eaten_mutex);
			i++;
		}
		free(philo_struct);
	}
}


void	cleanup(t_philo	*philo_struct, t_parse	parse)
{
	int	i;

	i = 0;
	if (parse.forks)
	{
		while (i < parse.nbr_of_philo)
		{
			pthread_mutex_destroy(&parse.forks[i]);
			i++;
		}
		free(parse.forks);
	}
	if (parse.print_mutex)
	{
		pthread_mutex_destroy(parse.print_mutex);
		free(parse.print_mutex);
	}
	if (parse.death_mutex)
	{
		pthread_mutex_destroy(parse.death_mutex);
		free(parse.death_mutex);
	}
	cleanup_struct(philo_struct, parse);
}

int	main(int argc, char **argv)
{
	t_philo	*philo_struct;
	t_parse	parse;

	philo_struct = NULL;
	if (!ft_parse(&parse, argc, argv))
		return (printf("Something wrong with arguments\n"), cleanup(philo_struct, parse), 1);
	if (!malloc_philo(&parse, &philo_struct))
		return (printf("Something wrong with allocation\n"), cleanup(philo_struct, parse), 1);
	if (!create_threads(&parse, philo_struct))
		return (printf("Something wrong with threads\n"), cleanup(philo_struct, parse), 1);
	cleanup(philo_struct, parse);
	return (0);
}
