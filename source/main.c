/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:15:55 by eklymova          #+#    #+#             */
/*   Updated: 2025/06/04 20:42:46 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	*philo_struct = NULL;
	t_parse	parse;

	if (!ft_parse(&parse, argc, argv))
		return (printf("Something wrong with arguments\n"), 1);
	if (!malloc_philo(&parse, &philo_struct))
		return (printf("Something wrong with allocation\n"), 1);
	if (!create_threads(&parse, philo_struct))
		return (printf("Something wrong with threads\n"), 1);
	return (0);
}
