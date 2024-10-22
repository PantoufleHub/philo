/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 07:11:26 by aperron           #+#    #+#             */
/*   Updated: 2024/05/15 19:35:13 by aperron          ###   ########.fr       */
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

void					display_philo(void *philo, char *msg, int override);

int						elapsed_time_ms(t_timer timer);

void					foreach(t_list *list, void (*f) (void *));

void					list_add(t_list **list, void *content);

long					my_atoi(char *str);

t_list					*summon_philosophers(t_world *world);

void					*update_philo(void *args);

int						valid_args(int argc, char *argv[]);

int						monitor(t_world *world, t_list *philos_arg,
							char **exit_msg);

int						get_world_state(t_world *world);

int						get_set_world_state(t_world *world, int state);

char					*get_color(int num);

void					cpy_timer(t_timer *t1, t_timer t2);

int						get_set_nb_meals(t_philo *philo, int nb_meals);

void					get_dem_foks(t_philo *philo);

int						check_ded(t_philo *philo);

void					think_prout(t_philo *philo);

void					state_machine(t_philo *philo);

void					*update_philo(void *args);

void					display_philo(void *philo_arg, char *msg, int end);

int						get_set_world_state(t_world *world, int state);

int						get_set_nb_meals(t_philo *philo, int increment);

void					change_philo_state(t_philo *philo, t_state state);

void					release_dem_foks(t_philo *philo);

void					left_prout(t_philo *philo);

#endif
