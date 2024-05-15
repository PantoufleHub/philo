/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:33:40 by aperron           #+#    #+#             */
/*   Updated: 2024/05/15 19:33:56 by aperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// Get value of world state and replace it
// If state given is -1, the state is not replaced
int	get_set_world_state(t_world *world, int state)
{
	int	old_state;

	pthread_mutex_lock(world->end_mutex);
	old_state = world->the_show_must_go_on;
	if (state != -1)
		world->the_show_must_go_on = state;
	pthread_mutex_unlock(world->end_mutex);
	return (old_state);
}

int	get_set_nb_meals(t_philo *philo, int increment)
{
	int	old_nb;

	pthread_mutex_lock(philo->meal_mutex);
	old_nb = philo->meals_had;
	if (increment)
		philo->meals_had = philo->meals_had + 1;
	pthread_mutex_unlock(philo->meal_mutex);
	return (old_nb);
}

void	change_philo_state(t_philo *philo, t_state state)
{
	philo->state = state;
	if (state == eating)
	{
		display_philo(philo, MSG_EET, 0);
	}
	if (state == sleeping)
	{
		display_philo(philo, MSG_SLIP, 0);
	}
	if (state == thinking)
	{
		display_philo(philo, MSG_THONK, 0);
	}
}

void	release_dem_foks(t_philo *philo)
{
	if (philo->world->nb_philos == 1)
		return ;
	philo->holding_foks[0] = 0;
	philo->holding_foks[1] = 0;
	pthread_mutex_lock(philo->adjacent_forks[0]->update_mutex);
		philo->adjacent_forks[0]->is_used = 0;
	pthread_mutex_unlock(philo->adjacent_forks[0]->update_mutex);
	pthread_mutex_lock(philo->adjacent_forks[1]->update_mutex);
		philo->adjacent_forks[1]->is_used = 0;
	pthread_mutex_unlock(philo->adjacent_forks[1]->update_mutex);
}

void	left_prout(t_philo *philo)
{
	pthread_mutex_lock(philo->adjacent_forks[0]->update_mutex);
	if (!philo->adjacent_forks[0]->is_used
		&& philo->adjacent_forks[0]->next_user == philo->nb)
	{
		philo->holding_foks[0] = 1;
		philo->adjacent_forks[0]->is_used = 1;
		display_philo(philo, MSG_FOK, 0);
		if (philo->nb == philo->world->nb_philos)
			philo->adjacent_forks[0]->next_user = 1;
		else
			philo->adjacent_forks[0]->next_user = philo->nb + 1;
	}
	pthread_mutex_unlock(philo->adjacent_forks[0]->update_mutex);
}
