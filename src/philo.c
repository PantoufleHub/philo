/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:33:40 by aperron           #+#    #+#             */
/*   Updated: 2024/05/15 17:47:26 by aperron          ###   ########.fr       */
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
		// usleep();
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

void	get_dem_foks(t_philo *philo)
{
	if (philo->world->nb_philos == 1)
		return ;
	if (!philo->holding_foks[0])
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
		// pthread_detach(philo->thread);
		philo->alive = 0;
		return (1);
	}
	if (elapsed_time_ms(philo->time_last_meal) > philo->world->time_to_die)
	{
		if (get_set_world_state(philo->world, 0) == 1)
		{
			philo->alive = 0;
			display_philo(philo, RED MSG_DED NRM, 1);
			// pthread_detach(philo->thread);
			return (1);
		}
	}
	return (0);
}

void	state_machine(t_philo *philo)
{
	if (philo->state == thinking)
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
		// display_philo(philo, "HELLO");
		if (check_ded(philo))
			break ;
		state_machine(philo);
		usleep(PHILO_UPDATE_DELTA);
	}
	return (NULL);
}

void	display_philo(void *philo_arg, char *msg, int end)
{
	struct timeval	current_time;
	t_philo			*philo;
	static int		has_ended = 0;

	philo = (t_philo *)philo_arg;
	pthread_mutex_lock(philo->world->print_mutex);
	if (get_set_world_state(philo->world, -1) == 1 || end)
	{
		if (has_ended)
			return ;
		if (end)
			has_ended++;
		gettimeofday(&current_time, NULL);
		printf("%d%s %d"NRM" %s\n",
			elapsed_time_ms(philo->world->time_of_creation),
			philo->print_color,
			philo->nb,
			msg);
	}
	pthread_mutex_unlock(philo->world->print_mutex);
}
