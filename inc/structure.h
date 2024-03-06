/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 07:11:36 by aperron           #+#    #+#             */
/*   Updated: 2024/03/06 22:53:02 by aperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_timer
{
	struct timeval	start_time;
}	t_timer;

typedef struct s_world
{
	int				the_show_must_go_on;
	int				nb_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals;
	char			*forks;
	t_timer			time_of_creation;
	pthread_mutex_t	*display_mutex;
	pthread_mutex_t	*fork_mutex;
}	t_world;

typedef struct s_philo
{
	int			nb;
	int			alive;
	int			meals_had;
	t_timer		time_state_started;
	t_timer		time_last_meal;
	t_world		*world;
	pthread_t	thread;
}	t_philo;

#endif