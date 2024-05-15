/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 07:10:13 by aperron           #+#    #+#             */
/*   Updated: 2024/05/15 17:56:48 by aperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char *argv[])
{
	t_world	*philosopher_land;
	t_list	*philosophers;
	int		status;
	char	*exit_msg;

	exit_msg = NULL;
	if (!valid_args(argc, argv))
	{
		printf("Error\nArgument format: NB_PHILO, TIME_DIE, TIME_EAT, "
			"TIME_SLEEP, [NB_MEALS]  (( Values above 0 ))\n");
		return (EXIT_FAILURE);
	}
	philosopher_land = create_world(argc, argv);
	philosophers = summon_philosophers(philosopher_land);
	status = 1;
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
