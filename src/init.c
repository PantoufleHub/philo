/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:16:14 by aperron           #+#    #+#             */
/*   Updated: 2024/03/06 22:53:29 by aperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

char	*set_the_table(int people_at_the_table)
{
	char	*forks;
	int		index;

	index = 0;
	forks = malloc(sizeof(char) * people_at_the_table + 1);
	while (index < people_at_the_table)
	{
		forks[index] = '1';
		index++;
	}
	forks[index] = '\0';
	return (forks);
}

t_world	*create_world(int argc, char *argv[])
{
	t_world			*world;
	struct timeval	time;

	world = malloc(sizeof(t_world));
	gettimeofday(&(world->time_of_creation.start_time), NULL);
	world->display_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(world->display_mutex, NULL);
	world->fork_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(world->display_mutex, NULL);
	world->the_show_must_go_on = 1;
	world->nb_philosophers = my_atoi(argv[1]);
	world->forks = set_the_table(world->nb_philosophers);
	world->time_to_die = my_atoi(argv[2]);
	world->time_to_eat = my_atoi(argv[3]);
	world->time_to_sleep = my_atoi(argv[4]);
	world->nb_meals = 0;
	if (argc == 6)
		world->nb_meals = my_atoi(argv[5]);
	return (world);
}
