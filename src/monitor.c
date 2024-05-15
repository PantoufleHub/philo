/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:21:18 by aperron           #+#    #+#             */
/*   Updated: 2024/05/15 19:29:29 by aperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	prout(t_philo *philo, t_world *world)
{
	display_philo(philo, RED MSG_DED NRM, 1);
	get_set_world_state(world, 0);
}

int	check_status(t_world *world, t_list *philos_arg,
	char **exit_msg)
{
	t_philo	*philo;
	int		eaten_enough;

	if (get_set_world_state(world, -1) == 0)
		return (0);
	eaten_enough = 0;
	while (philos_arg)
	{
		philo = (t_philo *)(philos_arg->content);
		if (world->nb_meals > -1 && get_set_nb_meals(philo, 0)
			>= world->nb_meals)
			eaten_enough++;
		if (elapsed_time_ms(philo->time_last_meal) >= world->time_to_die)
		{
			prout(philo, world);
			return (0);
		}
		philos_arg = philos_arg->next;
	}
	if (eaten_enough == world->nb_philos)
	{
		*exit_msg = CYN"The philosophers are full!"NRM;
		return (0);
	}
	return (1);
}

int	monitor(t_world *world, t_list *philos_arg, char **exit_msg)
{
	int	status;

	status = check_status(world, philos_arg, exit_msg);
	return (status);
}
