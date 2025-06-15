/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:15:55 by eklymova          #+#    #+#             */
/*   Updated: 2025/06/13 17:03:01 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	cleanup(t_philo	*philo_struct, t_parse	parse)
{
	int	i;

	i = 0;
	if (parse.forks)
	{
		while (i < parse.nbr_of_philo)
		{
			if (pthread_mutex_destroy(&parse.forks[i]))
				return (false);
			i++;
		}
		free(parse.forks);
	}
	if (philo_struct)
		free(philo_struct);
	return (true);
}

int	main(int argc, char **argv)
{
	t_philo	*philo_struct;
	t_parse	parse;

	philo_struct = NULL;
	if (!ft_parse(&parse, argc, argv))
		return (printf("Something wrong with arguments\n"), 1);
	if (!malloc_philo(&parse, &philo_struct))
		return (printf("Something wrong with allocation\n"), cleanup(philo_struct, parse), 1);
	if (!create_threads(&parse, philo_struct))
			return (printf("Something wrong with threads\n"), cleanup(philo_struct, parse), 1);
	cleanup(philo_struct, parse);
	return (0);
}
