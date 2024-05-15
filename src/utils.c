/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:38:57 by aperron           #+#    #+#             */
/*   Updated: 2024/05/15 08:37:31 by aperron          ###   ########.fr       */
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

void	cpy_timer(t_timer *t1, t_timer t2)
{
	(*t1).start_time.tv_sec = t2.start_time.tv_sec;
	(*t1).start_time.tv_usec = t2.start_time.tv_usec;
}

int	elapsed_time_ms(t_timer timer)
{
	struct timeval	current_time;
	int				elapsed_milliseconds;
	long			elapsed_microseconds;

	gettimeofday(&current_time, NULL);
	elapsed_microseconds = (current_time.tv_sec - timer.start_time.tv_sec)
		* 1000000L + (current_time.tv_usec - timer.start_time.tv_usec);
	elapsed_milliseconds = elapsed_microseconds / 1000L;
	return (elapsed_milliseconds);
}

char	*get_color(int num)
{
	static char	*colors[6] = {RED, YEL, GRN, CYN, BLU, MAG};

	return (colors[num % 6]);
}
