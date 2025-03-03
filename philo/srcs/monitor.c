/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:38:32 by cgoldens          #+#    #+#             */
/*   Updated: 2025/03/03 15:10:54 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * @brief monitor for philosopher's life
 * 
 * @param phi get one philo
 * @return void* return nothing
 */
void	*philo_life(void *phi)
{
	t_philo		*philo;
	pthread_t	death_checker;

	philo = (t_philo *)phi;
	if (philo->id % 2 == 0)
		usleep(philo->data->t_eat / 10);
	pthread_create(&death_checker, NULL, check_death, philo);
	while (!is_dead(philo, 0))
	{
		philo_think(philo);
		take_fork(philo);
		philo_eat(philo);
	}
	pthread_join(death_checker, NULL);
	return (NULL);
}

/**
 * @brief monitor for the philosopher's death
 * 
 * @param phi get one philo
 * @return void* return nothing
 */
void	*check_death(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	while (!is_dead(philo, 0))
	{
		pthread_mutex_lock(&philo->data->m_eat);
		if ((!is_dead(philo, 0)
				&& actual_ms(timestamp(), philo->data->t_start) \
				- philo->last_eat >= philo->data->t_die) || enough_eat(philo))
		{
			if (!enough_eat(philo))
				print(philo, " died");
			is_dead(philo, 1);
		}
		pthread_mutex_unlock(&philo->data->m_eat);
		ft_usleep(philo->data->t_die);
	}
	return (NULL);
}

/**
 * @brief process to start the monitoring of philo's life
 * 
 * @param data get data struct
 * @return int return state of process
 */
int	monitor(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL,
				&philo_life, &(data->philo[i])) != 0)
			return (-1);
	}
	i = -1;
	while (++i < data->nb_philo)
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (-1);
	return (0);
}
