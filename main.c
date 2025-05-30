/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:15:55 by eklymova          #+#    #+#             */
/*   Updated: 2025/05/30 19:35:33 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	main(int argc, char **argv)
{
	t_parse	parse;

	if (!ft_parse(&parse, argc, argv))
		return (printf("Something wrong with arguments\n"), 1);

}
