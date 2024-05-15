/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:16:14 by aperron           #+#    #+#             */
/*   Updated: 2024/05/15 17:22:56 by aperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	put_forks_in_philosophers_hands(t_world *world, t_philo *philo)
{
	philo->adjacent_forks = malloc(sizeof(t_fork) * 2);

	philo->adjacent_forks[0] = world->forks[philo->nb - 1];
	if (philo->nb == 1 && world->nb_philos > 1)
		philo->adjacent_forks[1] = world->forks[world->nb_philos - 1];
	else if (philo->nb == 1)
		philo->adjacent_forks[1] = NULL;
	else
		philo->adjacent_forks[1] = world->forks[philo->nb - 2];
}

t_philo	*spawn_philo(t_world *world, int index)
{
	t_philo		*new_philo;

	new_philo = malloc(sizeof(t_philo));
	new_philo->alive = 1;
	new_philo->nb = index + 1;
	new_philo->world = world;
	new_philo->holding_foks[0] = 0;
	new_philo->holding_foks[1] = 0;
	cpy_timer(&(new_philo->time_state_started), world->time_of_creation);
	cpy_timer(&(new_philo->time_last_meal), world->time_of_creation);
	new_philo->meal_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(new_philo->meal_mutex, NULL);
	new_philo->meals_had = 0;
	new_philo->state = thinking;
	new_philo->print_color = get_color(index);
	put_forks_in_philosophers_hands(world, new_philo);
	pthread_create(&(new_philo->thread), NULL, update_philo, new_philo);
	return (new_philo);
}

t_list	*summon_philosophers(t_world *world)
{
	t_list	*philosophers;
	int		index;

	index = 0;
	philosophers = NULL;
	while (index < world->nb_philos)
	{
		list_add(&philosophers, spawn_philo(world, index));
		index++;
	}
	return (philosophers);
}

void	set_the_table(t_world *world)
{
	int		fork_index;
	t_fork	*new_fork;

	world->forks = malloc(world->nb_philos * sizeof(t_fork *));
	fork_index = 0;
	while (fork_index < world->nb_philos)
	{
		new_fork = malloc(sizeof(t_fork));
		new_fork->is_used = 0;
		new_fork->next_user = (((fork_index) % 2) + fork_index + 1);
		if (fork_index + 1 == world->nb_philos)
			new_fork->next_user = 1;
		// printf("CREATED FORK FOR PHILO %d\n", new_fork->next_user);
		new_fork->update_mutex = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(new_fork->update_mutex, NULL);
		world->forks[fork_index] = new_fork;
		fork_index++;
	}	
}

t_world	*create_world(int argc, char *argv[])
{
	t_world			*world;

	world = malloc(sizeof(t_world));
	world->nb_philos = my_atoi(argv[1]);
	gettimeofday(&(world->time_of_creation.start_time), NULL);
	world->print_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(world->print_mutex, NULL);
	world->end_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(world->end_mutex, NULL);
	world->the_show_must_go_on = 1;
	world->time_to_die = my_atoi(argv[2]);
	world->time_to_eat = my_atoi(argv[3]);
	world->time_to_sleep = my_atoi(argv[4]);
	world->nb_meals = -1;
	set_the_table(world);
	if (argc == 6)
		world->nb_meals = my_atoi(argv[5]);
	return (world);
}
