/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:32:06 by aperron           #+#    #+#             */
/*   Updated: 2024/05/15 17:54:40 by aperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	exit_with_message(char *message)
{
	printf("Error: \n%s\n", message);
	exit(0);
}

int	is_num(char *num)
{
	int	index;

	index = 0;
	while (num[index])
	{
		if (!(num[index] >= 48 && num[index] <= 57))
			return (0);
		index++;
	}
	return (1);
}

int	valid_args(int argc, char *argv[])
{
	int	index;

	index = 1;
	if (argc < 5 || argc > 6)
		return (0);
	while (index < argc)
	{
		if (!is_num(argv[index]) || my_atoi(argv[index]) <= 0)
			return (0);
		index++;
	}
	return (1);
}
