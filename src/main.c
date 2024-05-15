/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 07:10:13 by aperron           #+#    #+#             */
/*   Updated: 2024/05/15 19:35:37 by aperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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

void	tutu(t_world **philosopher_land, t_list **philosophers,
	int *status)
{
	*philosophers = summon_philosophers(*philosopher_land);
	*status = 1;
}

int	pouet_pouet(int argc, char **argv)
{
	if (!valid_args(argc, argv))
	{
		printf("Error\nArgument format: NB_PHILO, TIME_DIE, TIME_EAT, "
			"TIME_SLEEP, [NB_MEALS]  (( Values above 0 ))\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_world	*philosopher_land;
	t_list	*philosophers;
	int		status;
	char	*exit_msg;

	exit_msg = NULL;
	if (pouet_pouet(argc, argv))
		return (EXIT_FAILURE);
	philosopher_land = create_world(argc, argv);
	tutu(&philosopher_land, &philosophers, &status);
	while (status)
	{
		status = monitor(philosopher_land, philosophers, &exit_msg);
		if (status == 0)
			break ;
		usleep(MONITOR_DELTA);
	}
	while (philosophers)
	{
		pthread_detach(((t_philo *)philosophers->content)->thread);
		philosophers = philosophers->next;
	}
	if (exit_msg)
		printf("%s\n", exit_msg);
	return (0);
}
