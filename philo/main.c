/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:45:50 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/13 15:04:45 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	freeall(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		//TODO toujours un putain de destroy failed
		//TODO tester le code si dessous
		if (pthread_mutex_unlock(&data->philo[i].fork_l))
			printf("test unlock n°%d\n", i);
		//pthread_mutex_unlock(data->philo[i].fork_r);
		pthread_mutex_destroy(&data->philo[i].fork_l);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
			
		free(&data->philo[i].fork_r);
		i++;
	}
	pthread_mutex_unlock(&data->m_stop);
	pthread_mutex_unlock(&data->m_eat);
	pthread_mutex_unlock(&data->dead);
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
