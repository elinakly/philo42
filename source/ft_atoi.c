/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 19:21:55 by eklymova          #+#    #+#             */
/*   Updated: 2025/06/03 18:28:54 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] != '\0' && (str[i] >= '1' && str[i] <= '9'))
	{
		result = result * 10 + (str[i] - '0');
		if (result > INT_MAX || result < INT_MIN)
			return (-2);
		i++;
	}
	if (str[i])
		return (-2);
	return (result);
}
