/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:45:50 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/14 12:01:16 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_mutex_state(pthread_mutex_t *mutex, const char *msg)
{
	if (pthread_mutex_unlock(mutex) == 0)
	{
		printf("[INFO] Mutex %s is not locked. No unlock was needed.\n", msg);
		//pthread_mutex_lock(mutex); // On restaure l'état verrouillé
	}
	else
	{
		printf("[WARNING] Mutex %s was locked.\n", msg);
	}
}

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
	printf("init %d\n",philo_init(&data));
	freeall(&data);
	return (0);
}
