/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 19:35:34 by eklymova          #+#    #+#             */
/*   Updated: 2025/06/03 18:19:45 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	ft_parse(t_parse *parse, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (false);
	parse->nbr_of_philo = ft_atoi(argv[1]);
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
	return (true);
}
