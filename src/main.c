/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 07:10:13 by aperron           #+#    #+#             */
/*   Updated: 2024/03/06 22:35:44 by aperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char *argv[])
{
	t_world	*philosopher_land;
	t_list	*philosophers;

	if (!valid_args(argc, argv))
		return (EXIT_FAILURE);
	if (argc == 6 && my_atoi(argv[5]) == 0)
		return (EXIT_SUCCESS);
	if (my_atoi(argv[1]) == 0)
		return (EXIT_SUCCESS);
	philosopher_land = create_world(argc, argv);
	philosophers = summon_philosophers(philosopher_land);
	while (philosophers)
	{
		pthread_join(((t_philo *)philosophers->content)->thread, NULL);
		philosophers = philosophers->next;
	}
	return (0);
}
