/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:05:03 by cgoldens          #+#    #+#             */
/*   Updated: 2024/12/16 11:57:24 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*data_init(char **ag)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	data->nb_philo = ft_atoi(ag[1]);
	data->t_die = ft_atoi(ag[2]);
	data->t_eat = ft_atoi(ag[3]);
	data->t_sleep = ft_atoi(ag[4]);
	data->t_start = timestamp();
	if (ag[5])
		data->n_eat = ft_atoi(ag[5]);
	else
		data->n_eat = -1;
	return (data);
}