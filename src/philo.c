/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:33:40 by aperron           #+#    #+#             */
/*   Updated: 2024/03/06 22:55:21 by aperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*update(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->world->the_show_must_go_on)
	{
		if (elapsed_time(philo->time_last_meal) > philo->world->time_to_die)
			philo->alive = 0;
		if (philo->alive)
		{
			display_philo(philo, "I'm alive!");
			usleep(1 * 1e6);
			update(philo);
		}
		else
		{
			display_philo(philo, "died");
			philo->world->the_show_must_go_on = 0;
		}
	}
	return (NULL);
}

t_philo	*spawn_philo(t_world *world, int nb)
{
	t_philo		*new_philo;

	new_philo = malloc(sizeof(t_philo));
	pthread_create(&(new_philo->thread), NULL, update, new_philo);
	new_philo->alive = 1;
	new_philo->nb = nb;
	new_philo->world = world;
	new_philo->time_state_started = world->time_of_creation;
	new_philo->time_last_meal = world->time_of_creation;
	new_philo->meals_had = 0;
	return (new_philo);
}

void	display_philo(t_philo *philo, char *message)
{
	struct timeval	current_time;

	pthread_mutex_lock(philo->world->display_mutex);
	gettimeofday(&current_time, NULL);
	printf("%.0f %d %s""\n",
		elapsed_time(philo->world->time_of_creation) * 1000,
		philo->nb,
		message);
	pthread_mutex_unlock(philo->world->display_mutex);
}

t_list	*summon_philosophers(t_world *world)
{
	t_list	*philosophers;
	int		index;

	index = 0;
	philosophers = NULL;
	while (index < world->nb_philosophers)
	{
		list_add(&philosophers, spawn_philo(world, index + 1));
		index++;
	}
	return (philosophers);
}
