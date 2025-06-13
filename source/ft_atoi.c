/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 19:21:55 by eklymova          #+#    #+#             */
/*   Updated: 2025/06/13 16:34:33 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// int	ft_atoi(const char *str)
// {
// 	int		i;
// 	long	result;

// 	i = 0;
// 	result = 0;
// 	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
// 		i++;
// 	if (str[i] == '+')
// 		i++;
// 	while (str[i] != '\0' && (str[i] >= '1' && str[i] <= '9'))
// 	{
// 		result = result * 10 + (str[i] - '0');
// 		if (result > INT_MAX || result < INT_MIN)
// 			return (-2);
// 		i++;
// 	}
// 	if (str[i])
// 		return (-2);
// 	return (result);
// }

int	ft_atoi(const char *nptr)
{
	long	sig;
	long	res;

	res = 0;
	sig = 1;
	while ((*nptr > 8 && *nptr < 14) || *nptr == ' ')
		sig = (*nptr++ || res == 0);
	if (*nptr == 43 || *nptr == 45)
		sig = (*nptr++ - 44) * -1;
	while (*nptr >= '0' && *nptr <= '9')
		res = res * 10 + (*nptr++ - 48);
	return ((int)(sig * res));
}
