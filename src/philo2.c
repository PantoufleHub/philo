/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:33:31 by aperron           #+#    #+#             */
/*   Updated: 2024/05/15 19:35:24 by aperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	get_dem_foks(t_philo *philo)
{
	if (philo->world->nb_philos == 1)
		return ;
	if (!philo->holding_foks[0])
	{
		left_prout(philo);
	}
	if (!philo->holding_foks[1])
	{
		pthread_mutex_lock(philo->adjacent_forks[1]->update_mutex);
		if (!philo->adjacent_forks[1]->is_used
			&& philo->adjacent_forks[1]->next_user == philo->nb)
		{
			philo->holding_foks[1] = 1;
			philo->adjacent_forks[1]->is_used = 1;
			display_philo(philo, MSG_FOK, 0);
			if (philo->nb == 1)
				philo->adjacent_forks[1]->next_user = philo->world->nb_philos;
			else
				philo->adjacent_forks[1]->next_user = philo->nb - 1;
		}
		pthread_mutex_unlock(philo->adjacent_forks[1]->update_mutex);
	}
}

int	check_ded(t_philo *philo)
{
	if (get_set_world_state(philo->world, -1) == 0)
	{
		philo->alive = 0;
		return (1);
	}
	if (elapsed_time_ms(philo->time_last_meal) > philo->world->time_to_die)
	{
		if (get_set_world_state(philo->world, 0) == 1)
		{
			philo->alive = 0;
			display_philo(philo, RED MSG_DED NRM, 1);
			return (1);
		}
	}
	return (0);
}

void	think_prout(t_philo *philo)
{
	get_dem_foks(philo);
	if (philo->holding_foks[0] && philo->holding_foks[1])
	{
		gettimeofday(&(philo->time_last_meal.start_time), NULL);
		gettimeofday(&(philo->time_state_started.start_time), NULL);
		change_philo_state(philo, eating);
		get_set_nb_meals(philo, 1);
	}
}

void	state_machine(t_philo *philo)
{
	if (philo->state == thinking)
	{
		think_prout(philo);
	}
	else if (philo->state == eating)
	{
		if (elapsed_time_ms(philo->time_state_started)
			> philo->world->time_to_eat)
		{
			gettimeofday(&(philo->time_state_started.start_time), NULL);
			release_dem_foks(philo);
			change_philo_state(philo, sleeping);
		}
	}
	else if (philo->state == sleeping)
	{
		if (elapsed_time_ms(philo->time_state_started)
			> philo->world->time_to_sleep)
		{
			gettimeofday(&(philo->time_state_started.start_time), NULL);
			change_philo_state(philo, thinking);
		}
	}
}

void	*update_philo(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (1)
	{
		if (check_ded(philo))
			break ;
		state_machine(philo);
		usleep(PHILO_UPDATE_DELTA);
	}
	return (NULL);
}
