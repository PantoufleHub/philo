/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:26:50 by aperron           #+#    #+#             */
/*   Updated: 2024/04/26 15:29:18 by aperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	list_add(t_list **list, void *content)
{
	t_list	*tmp;
	t_list	*new;

	new = malloc(sizeof(t_list));
	new->content = content;
	new->next = NULL;
	if (!*list)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	foreach(t_list *list, void(*f)(void *))
{
	while (list)
	{
		f(list->content);
		list = list->next;
	}
}

// void	foreach(t_list *list, void(*f)(void *))
// {
// 	while (list)
// 	{
// 		f(list->content);
// 		list = list->next;
// 	}
// }

// void	clear_list(t_list *list, void (*del)(void *))
// {
// 	while (list)
// 	{
// 		free(list->content);

// 	}
// }
