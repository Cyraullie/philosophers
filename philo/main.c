/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:45:50 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/14 13:39:59 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	freeall(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo - 1)
	{
		pthread_mutex_destroy(&data->philo[i].fork_l);
		i++;
	}
	pthread_mutex_destroy(&data->m_stop);
	pthread_mutex_destroy(&data->m_eat);
	pthread_mutex_destroy(&data->dead);
	pthread_mutex_destroy(&data->print);
	free(data->philo);
}

int	main(int ac, char **ag)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (0);
	if (data_init(&data, ag) == 1)
	{
		free(data.philo);
		return (0);
	}
	philo_init(&data);
	freeall(&data);
	return (0);
}
