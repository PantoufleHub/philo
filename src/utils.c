/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:38:57 by aperron           #+#    #+#             */
/*   Updated: 2024/03/06 22:17:35 by aperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

long	my_atoi(char *str)
{
	long	value;
	long	index;
	int		neg;

	if (ft_strlen(str) == 0)
		return (0);
	index = 0;
	neg = 1;
	if (str[0] == '-')
	{
		neg = -1;
		index = 1;
	}
	value = 0;
	while (index < (long)ft_strlen(str))
	{
		value *= 10;
		value += str[index] - '0';
		index++;
	}
	if (value == 0)
		neg = 1;
	return (value * neg);
}

double	elapsed_time(t_timer timer)
{
    struct timeval	current_time;
	double			elapsed_seconds;
    double			elapsed_microseconds;

    gettimeofday(&current_time, NULL);
    elapsed_seconds = (double)(current_time.tv_sec - timer.start_time.tv_sec);
    elapsed_microseconds = (double)(current_time.tv_usec - timer.start_time.tv_usec);
    return (elapsed_seconds + elapsed_microseconds / 1e6);
}
