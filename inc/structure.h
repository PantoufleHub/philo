/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 07:11:36 by aperron           #+#    #+#             */
/*   Updated: 2024/05/15 19:13:51 by aperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef enum e_state
{
	sleeping,
	thinking,
	eating,
}	t_state;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_timer
{
	struct timeval	start_time;
}	t_timer;

typedef struct s_fork
{
	int				is_used;
	int				next_user;
	pthread_mutex_t	*update_mutex;
}	t_fork;

typedef struct s_world
{
	int				the_show_must_go_on;
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals;
	t_timer			time_of_creation;
	t_fork			**forks;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*end_mutex;
}	t_world;

typedef struct s_philo
{
	int				nb;
	int				alive;
	int				meals_had;
	char			*print_color;
	int				holding_foks[2];
	t_state			state;
	t_fork			**adjacent_forks;
	t_timer			time_state_started;
	t_world			*world;
	t_timer			time_last_meal;
	pthread_t		thread;
	pthread_mutex_t	*meal_mutex;
}	t_philo;

#endif