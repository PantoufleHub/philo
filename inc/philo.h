/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 07:11:26 by aperron           #+#    #+#             */
/*   Updated: 2024/03/06 22:29:10 by aperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# include "structure.h"
# include "constants.h"

t_world					*create_world(int argc, char *argv[]);

void					display_philo(t_philo *philo, char *message);

double					elapsed_time(t_timer timer);

void					foreach(t_list *list, void(*f)(void *));

void					list_add(t_list **list, void *content);

long					my_atoi(char *str);

t_list					*summon_philosophers(t_world *world);

int						valid_args(int argc, char *argv[]);

#endif
