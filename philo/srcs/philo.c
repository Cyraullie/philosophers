/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:40:29 by cgoldens          #+#    #+#             */
/*   Updated: 2025/03/05 12:16:59 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * @brief process of thinking
 * 
 * @param philo get a philo
 */
void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->m_eat));
	pthread_mutex_lock(&philo->data->m_stop);
	if (!philo->data->stop)
		print(philo, " is thinking");
	pthread_mutex_unlock(&(philo->data->m_eat));
	pthread_mutex_unlock(&philo->data->m_stop);
}

/**
 * @brief process to check if a philo is dead
 * 
 * @param philo get a philo
 * @param nb get a number to say that philo is dead
 * @return int return true or false
 */
int	is_dead(t_philo *philo, int nb)
{
	pthread_mutex_lock(&philo->data->dead);
	if (nb)
		philo->data->stop = 1;
	if (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead);
	return (0);
}

/**
 * @brief process of sleeping
 * 
 * @param philo get a philo
 */
void	philo_sleep(t_philo *philo)
{
	print(philo, " is sleeping");
	ft_usleep(philo->data->t_sleep);
}
